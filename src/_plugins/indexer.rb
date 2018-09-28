require "set"

module Indexer
  class Page < Jekyll::Page
    def initialize(site, base, dir, items)
      @site = site
      @base = base
      @dir = dir
      @name = "index.html"

      self.process(@name)
      self.read_yaml(File.join(base, "_layouts"), "index.html")

      self.data["items"] = items
    end
  end

  def self.run(site, dir)
    files = Dir.entries(dir)
    files.sort!
  
    if !files.to_set.intersect?(Set["index.html", "index.htm"])
      page = Page.new(site, site.source, dir, files)

      payload = site.site_payload
      page.output = Jekyll::Renderer.new(site, page, payload).run
      page.write(site.dest)

      puts "rendering #{dir}/index.html"

      site.pages << page
    end

    for file in files
      if [".", ".."].include?(file)
        next
      end

      if Dir.exist?(File.join(dir, file))
        run(site, File.join(dir, file))
      end
    end
  end
end

Jekyll::Hooks.register :site, :post_write do |site|
  Indexer.run(site, site.dest)
end
