
files = File.join(ARGV[0], "**", "*")

Dir.glob(files) { |filename|

   if (!File.directory? filename)
      cmd_line = "./file_info \"#{File.expand_path(filename)}\""
      ret = `#{cmd_line}`
      puts "#{filename} = #{ret}"
   end

}
