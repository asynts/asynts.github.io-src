require "digest"
require "net/http"

targetdir = "."

module Downloader
  @@downloaded = []
  def self.download url
    fname = filename url

    # don't download the file again
    if @@downloaded.include? fname
      return fname
    end

    uri = URI url

    file = open File.join(targetdir, fname), "w"
    begin
      # download via http
      Net::HTTP.get_response uri do |resp|
        resp.read_body do |chunk| 
          file.write chunk
        end
      end
    ensure
      file.close()
    end

    @@downloaded << fname
    fname
  end

  # generate a filename for the given url
  def self.filename url
    ext = File.extname URI(url).path
    dir = "dw"
    name = Digest::SHA2.hexdigest url

    "#{dir}/#{name}#{ext}"
  end
end

Downloader.download "https://cdn.jsdelivr.net/gh/google/code-prettify/loader/run_prettify.js?autorun=false"

