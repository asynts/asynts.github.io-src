// mkstemp, ftruncate
#define _POSIX_C_SOURCE 200809L

/*
I've tried to create a minimal example, as a result the program leaks a huge amount
of memory and doesn't do any error checking.

Compile with:

    CFLAGS="-std=c17 -Wall -Wextra -Wpedantic -Wno-unused-parameter"

    WL=`pkg-config wayland-protocols --variable=pkgdatadir`
    wayland-scanner client-header "$WL/stable/xdg-shell/xdg-shell.xml" xdg-shell-client-protocol.h 
    wayland-scanner private-code  "$WL/stable/xdg-shell/xdg-shell.xml" xdg-shell-client-protocol.c

    clang $CFLAGS -c xdg-shell-client-protocol.c -o xdg-shell-client-protocol.c.o

    clang $FLAGS \
      simple.c \
      xdg-shell-client-protocol.c.o \
      -lwayland-client \
      -o simple.out
*/

#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

#include <wayland-client.h>

#include "xdg-shell-client-protocol.h"

struct ct_buffer {
  uint8_t *data;
  struct wl_buffer *buffer;
};

struct ct_window {
  struct wl_display *display;
  struct wl_registry *registry;
  struct wl_compositor *compositor;
  struct wl_surface *surface;
  struct wl_shm *shm;
  struct xdg_wm_base *wm_base;
  struct xdg_toplevel *toplevel;

  size_t width, height;
  struct ct_buffer buffer;
};

void ct_buffer_init(struct ct_window *window, const size_t width, const size_t height) {
  const size_t stride = width * 4,
               size = stride * height;

  // refer to https://stackoverflow.com/a/48648444/8746648
  char template[] = "/tmp/ct-XXXXXX";
  int fd = mkstemp(template);

  ftruncate(fd, size);

  void *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  struct wl_shm_pool *pool = wl_shm_create_pool(window->shm, fd, size);

  window->buffer.data = data;
  window->buffer.buffer = wl_shm_pool_create_buffer(pool, 0, width, height, stride, WL_SHM_FORMAT_XRGB8888);
}

void render(struct ct_window *window);

static
void handle_xdg_surface_configure(void *data, struct xdg_surface *surface, uint32_t serial) {
  xdg_surface_ack_configure(surface, serial);

  struct ct_window *window = data;

  render(window);
  wl_surface_attach(window->surface, window->buffer.buffer, 0, 0);
  wl_surface_commit(window->surface);
}

static const
struct xdg_surface_listener handler_xdg_surface = {
  .configure = handle_xdg_surface_configure
};

static
void handle_xdg_wm_base_ping(void *data, struct xdg_wm_base *wm_base, uint32_t serial) {
  xdg_wm_base_pong(wm_base, serial);
}

static const
struct xdg_wm_base_listener handler_xdg_wm_base = {
  .ping = handle_xdg_wm_base_ping
};

static
void handle_wl_registry_global(void *data, struct wl_registry *registry, uint32_t id, const char *interface, uint32_t version) {
  struct ct_window *window = data;

  if(strcmp(interface, "wl_compositor") == 0) {
    window->compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 1);
  }

  if(strcmp(interface, "wl_shm") == 0) {
    window->shm = wl_registry_bind(registry, id, &wl_shm_interface, 1);
  }

  if(strcmp(interface, "xdg_wm_base") == 0) {
    window->wm_base = wl_registry_bind(registry, id, &xdg_wm_base_interface, 1);
    xdg_wm_base_add_listener(window->wm_base, &handler_xdg_wm_base, NULL);
  }
}

static
void handle_wl_registry_global_remove(void *data, struct wl_registry *registry, uint32_t id) { }

static const
struct wl_registry_listener handler_wl_registry = {
  .global = handle_wl_registry_global,
  .global_remove = handle_wl_registry_global_remove
};

void ct_window_init(struct ct_window *window, size_t width, size_t height) {
  window->width = width;
  window->height = height;

  window->display = wl_display_connect(NULL);

  window->registry = wl_display_get_registry(window->display);
  wl_registry_add_listener(window->registry, &handler_wl_registry, window);
  wl_display_roundtrip(window->display);

  ct_buffer_init(window, width, height);

  window->surface = wl_compositor_create_surface(window->compositor);
  struct xdg_surface *surface = xdg_wm_base_get_xdg_surface(window->wm_base, window->surface);
  window->toplevel = xdg_surface_get_toplevel(surface);

  xdg_surface_add_listener(surface, &handler_xdg_surface, window);

  wl_surface_commit(window->surface);
}

void render(struct ct_window *window) {
  uint8_t *buf = window->buffer.data;
  for(size_t i=0; i<window->width * window->height; i++) {
    *buf++ = 0;   // X
    *buf++ = 255; // R
    *buf++ = 0;   // G
    *buf++ = 0;   // B
  }
}

int main() {
  struct ct_window window;

  ct_window_init(&window, 200, 200);

  wl_display_flush(window.display);
  while(wl_display_dispatch(window.display) != -1) {}
}

