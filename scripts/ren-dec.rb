=begin
Renames and decompresses results files
-------
The result files are compressed using gzip. In order to unzip them, we
rename them by adding .gz to the end of the filename and then run the 
gzip on the file.
=end

files = File.join("**", "*")
Dir.glob(files) { |filename|
	unless (File.directory?(filename) || File.stat(filename).size == 100000012 || filename =~ /.*(\.rb|\.gz)/)
		name = File.expand_path("./#{filename}")
		File.rename(name, "#{name}.gz")
		system("gzip -d #{name}.gz")
		puts name
	end
}

