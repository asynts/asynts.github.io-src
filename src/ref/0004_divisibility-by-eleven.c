#define _XOPEN_SOURCE
#define THREADS 4

#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <unistd.h>

#include <err.h>
#include <gmp.h>
#include <signal.h>

void altsum(char *buf, mpz_t result, mpz_t number) {
  mpz_get_str(buf, 10, number);

  mpz_set_ui(result, 0);

  bool neg = false;
  for (size_t i = 0; i < strlen(buf); i++) {
    if (neg) {
      mpz_sub_ui(result, result, buf[i] - '0');
    } else {
      mpz_add_ui(result, result, buf[i] - '0');
    }

    neg ^= true;
  }
}

volatile sig_atomic_t quit;
void sigint() { quit = 1; }

volatile atomic_flag stdout_lock;

void lock_stdout() {
  while (atomic_flag_test_and_set(&stdout_lock)) {
    sleep(10);
  }
}

void unlock_stdout() {
  atomic_flag_clear(&stdout_lock);
  fflush(stdout);
}

struct info {
  size_t threadid;
  mpz_t number;
};

int thread_main(void *info_) {
  struct info *info = info_;

  mpz_t number;
  mpz_init_set(number, info->number);

  char *buf = malloc(sizeof(2048));

  mpz_t result;
  mpz_init(result);

  do {
    altsum(buf, result, number);

    bool rdiv = mpz_divisible_ui_p(result, 11);
    bool ndiv = mpz_divisible_ui_p(number, 11);

    if ((rdiv && !ndiv) || (ndiv && !rdiv)) {
      lock_stdout();
      gmp_printf("(thread: %zu) failed: %Zd\n", info->threadid, number);
      unlock_stdout();
    }

    mpz_add_ui(number, number, THREADS);
  } while (!quit);

  // won't get negative, since the loop runs at least once
  mpz_sub_ui(number, number, THREADS);
  mpz_set(info->number, number);

  lock_stdout();
  gmp_printf("(thread: %zu) final: %Zd\n", info->threadid, number);
  unlock_stdout();

  mpz_clear(number);
  mpz_clear(result);

  free(buf);

  return thrd_success;
}

int main() {
  static struct sigaction act;
  act.sa_handler = sigint;
  sigfillset(&act.sa_mask);

  if (sigaction(SIGINT, &act, NULL)) {
    errx(EXIT_FAILURE, "error: sigaction() failed\n");
  }

  thrd_t idents[THREADS];
  struct info args[THREADS];

  // the threads are each offset by 1 and increment by the number of threads
  for (size_t i = 0; i < THREADS; i++) {
    args[i].threadid = i;
    mpz_init_set_ui(args[i].number, i);

    if (thrd_create(idents + i, thread_main, args + i) != thrd_success) {
      errx(EXIT_FAILURE, "error: thrd_create() failed\n");
    }
  }

  if (thrd_join(idents[0], NULL) != thrd_success) {
    errx(EXIT_FAILURE, "error: thrd_join() failed\n");
  }

  mpz_t min;
  mpz_init_set(min, args[0].number);

  for (size_t i = 1; i < THREADS; i++) {
    if (thrd_join(idents[i], NULL) != thrd_success) {
      errx(EXIT_FAILURE, "error: thrd_join() failed\n");
    }

    if (mpz_cmp(min, args[i].number) > 0) {
      mpz_set(min, args[i].number);
    }

    mpz_clear(args[i].number);
  }

  gmp_printf("computed until %Zd\n", min);
}

