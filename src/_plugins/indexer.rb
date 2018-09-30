module Indexer
  class Page < Jekyll::Page
    def initialize(site, base, dir, items)
      @site = site
      @base = base
      @dir = Pathname.new(dir).relative_path_from(Pathname.new(site.dest)).to_s
      @name = "index.html"

      self.process(@name)
      self.read_yaml(File.join(base, "_layouts"), "index.html")

      self.data["items"] = items

      Jekyll::Hooks.trigger :pages, :post_init, self
    end
  end

  def self._run(site, dir)
    files = Dir.entries(dir)
    files.sort!
  
    if !files.to_set.intersect?(Set["index.html", "index.htm"])
      page = Page.new(site, site.source, dir, files)

      payload = site.site_payload

      Jekyll::Hooks.trigger :site, :pre_render, site, payload
      page.output = Jekyll::Renderer.new(site, page, payload).run
      Jekyll::Hooks.trigger :site, :post_render, site, payload

      page.write(site.dest)
      Jekyll::Hooks.trigger :site, :post_write, site

      site.pages << page
    end

    for file in files
      if [".", ".."].include?(file)
        next
      end

      if Dir.exist?(File.join(dir, file))
        _run(site, File.join(dir, file))
      end
    end
  end

  @has_indexed = false
  def self.run(site)
    return unless !@has_indexed
    has_indexed = true

    self._run(site, site.dest)
  end
end

Jekyll::Hooks.register :site, :post_write do |site|
  Indexer.run(site)
end
