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
      site.pages << Page.new(site, site.source, ".", ["a.html", "b.html"])
    end
  end
end
