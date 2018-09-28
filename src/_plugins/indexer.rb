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
    if !Set[files].intersect?(Set["index.html", "index.htm"])
      # TODO files aren't created!
      site.pages << Page.new(site, site.source, dir, files)
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
