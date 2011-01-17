def checkout
	puts "Checking out boinc...."
	puts `svn co http://boinc.berkeley.edu/svn/trunk/boinc --force`
	puts "\nChecking out boost...."
	puts `svn co http://svn.boost.org/svn/boost/tags/release/Boost_1_45_0/ boost`
end

def update_boinc
	puts "Updating boinc...."
	Kernel.exec("svn update boinc --force")
end

def checkout_boost

def clean_build
	Kernel.exec("boinc/make clean");
end

def int_make
	puts "Running make...."
	output = `make`
	puts "make output:"
	puts output
end

def make
	Dir.chdir "boinc" do
		int_make
	end
end

def main_automake(change)

	if (change)
		Dir.chdir "boinc"
	end
	
	lines = IO.readlines("Makefile.am")
			lines.each { |line| 
			
				if (line =~ /\w*SERVER_SUBDIRS = .*?$/)
					if (!line.include?("partproject"))
						line.sub!(/\n/," partproject\n")
					end
					
				end 
			}
	File.rename("Makefile.am", "Makefile.am.OLD")
	File.open("Makefile.am", "w") {|io|
		io << lines
	}
	

end

def sched_automake(change)
	
	if (change)
		Dir.chdir "boinc/sched"
	end
	lines = IO.readlines("Makefile.am")
	lines.each { |line| 
	
		if (line =~ /\w*sched_PROGRAMS = .*?\\\n$/)
			if (!line.include?("partproject_assimilator"))
				line.sub!(/\\/," partproject_assimilator partproject_work_generator\n")
			end
			
		end
		
		if (line =~ /\*sample_work_generator_LDADD = \$\(SERVERLIBS\)\w*$/)
			line << "\npartproject_work_generator_SOURCES = partproject_work_generator.cpp\n"
			line << "\npartproject_work_generator_LDADD = $(SERVERLIBS)\n"
			line << "\npartproject_assimilator_SOURCES = $(ASSIMILATOR_SOURCES) partproject_assimilator.cpp"
	}
	File.rename("Makefile.am", "Makefile.am.OLD")
	File.open("Makefile.am", "w") {|io|
		io << lines
	}
end

def setup_and_make
	
	Dir.chdir "boost" do
		
	end
	
	Dir.chdir "boinc" do
	
		puts "Modifying Automake files..."
		
		
		
		puts "Running autosetup...."
		output = `./_autosetup`
		puts "autosetup output:"
		puts output;
		
		
		
		puts "Running configure...."
		output = `./configure --disable-manager --disable-client`
		puts "configure output:"
		puts output
		
		int_make
	end
	
end


case ARGV[0]
	when "checkout"
		checkout_boinc
	when "update_boinc"
		update_boinc
	when "make"
		make
	when "setup_and_make"
		setup_and_make
	when "lines"
		lines(true)
end


