require "uri"
require "net/http"
require "digest"

module Jekyll
  class DownloadTag < Liquid::Tag
    def initialize tag_name, url, tokens
      super

      @url = url
      download @url
    end

    @@downloaded = []
    def self.download url
      fname = filename url

      # don't download the file again
      if @@downloaded.include? fname
        return fname
      end

      uri = URI url
      file = open fname, "w"
      begin
        # download via http
        Net::HTTP.get_response uri do |resp|
          resp.read_body { |chunk| file.write chunk }
        end
      ensure
        file.close()
      end

      @@downloaded << fname
      fname
    end

    # generate a filename for the given url
    def self.filename url
      ext = ".js" # todo
      dir = "/dw/"
      name = Digest::SHA2.hexdigest url

      "#{dir}/#{name}#{ext}"
    end

    def render ctx
      return filename @url
    end
  end
end

