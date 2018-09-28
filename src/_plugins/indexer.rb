Jekyll::Hooks.register :site, :post_write do |site|
  Dir.foreach(site.dest) do |file|
    puts file
  end
end
