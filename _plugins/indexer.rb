module Asynts
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

  class Generator < Jekyll::Generator
    def generate(site)
      dirs = {}

      for p in site.pages
        if dirs.has_key?(p.dir)
          dirs[p.dir] << p.name
        else
          dirs[p.dir] = [p.name]
        end
      end

      for p in site.static_files
        dir = File.dirname("." + p.relative_path)
        if dirs.has_key?(dir)
          dirs[dir] << p.name
        else
          dirs[dir] = [p.name]
        end
      end

      dirs.each do |dir, items|
        site.pages << Page.new(site, site.source, dir, items)
      end
    end
  end
end
