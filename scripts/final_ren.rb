=begin
Renames and moves files to final location
----------------------
Result files currently use the name of their workunit, instead of a simpler
name. Additionally, a few of them were put into the wrong directory initially.
This scripts give them a nice name and puts them in the proper directory.

=end

require 'fileutils'

files = File.join("**", "*")

Dir.glob(files) { |filename|
	if (File.stat(filename).size == 100000012 && 
		File.basename(filename) =~ /^partproject_\d*?_\d*?_(k\d+?)_(m\d+?)$/)
    k_part = $1
    m_part = $2
  
    #create the sub directories
    if (!File.exists?("./n50000000/#{k_part}"))
      Dir.mkdir("./n50000000/#{k_part}")
    end
    
    if (!File.exists?("./n50000000/#{k_part}/#{m_part}"))
      Dir.mkdir("./n50000000/#{k_part}/#{m_part}")
    end
    
    #move the file
    final_location = File.join(".", "n50000000", k_part, m_part, 
        File.basename(filename))
    if (File.expand_path(filename) != File.expand_path(final_location))
      FileUtils.mv(File.expand_path(filename),  File.expand_path(final_location))
    end
    #finally rename file
    File.rename(File.expand_path(final_location), File.join(File.dirname(final_location), 
        "n50000000_#{k_part}_#{m_part}"))
    
	end
}
