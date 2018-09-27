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
      files = []

      # TODO site.pages

      for p in site.static_files
        files << File.join(p.relative_path)
      end

      for file in files
        dirs = file.split(File::SEPARATOR)
        dirs = ["."] + dirs[1..-2]

        # TODO what now
      end

#      site.pages << Page.new(site, site.source, dir, items)
    end
  end
end
