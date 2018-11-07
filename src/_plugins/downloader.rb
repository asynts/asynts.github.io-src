require "uri"
require "net/http"
require "digest"

module Downloader
  # TODO: private
  def _download uri, file
    Net::HTTP.get_response uri do |resp|
      resp.read_body do |chunk|
        file.write chunk
      end
    end
  end

  def download url, ext=""
    uri = URI url
    name = Digest::SHA2.hexdigest url
    name += ext

    file = open name, "w"

    begin 
      _download uri, file
    ensure
      file.close()
    end

    name
  end
end

