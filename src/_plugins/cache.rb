require "digest"
require "net/http"
require "uri"

module Jekyll::Cache
  class Tag < Liquid::Tag
    def initialize name, params, tokens
      @uri = URI params.strip
    end

    def folder
      if @folder
        @folder
      else
        config = Jekyll.configuration({})
        if config.key? "cache" and config["cache"].key? "folder"
          @folder = config["cache"]["folder"]
        else
          @folder = "cache"
        end
      end
    end

    def filename
      ext = File.extname @uri.path
      name = Digest::SHA2.hexdigest @uri.to_s

      File.join folder, name + ext
    end

    def render context
      site = context.registers[:site]

      FileUtils.mkdir_p File.join(site.dest, folder)

      fname = filename
      path = File.join site.dest, fname

      file = open path, "w"

      begin
        Net::HTTP.get_response @uri do |resp|
          resp.read_body { |chunk| file.write chunk }
        end
      ensure
        file.close
      end

      site.keep_files << fname

      if @uri.query
        "/#{fname}?#{@uri.query}"
      else
        "/" + fname
      end
    end
  end
end

Liquid::Template.register_tag "cache", Jekyll::Cache::Tag

