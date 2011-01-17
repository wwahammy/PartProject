def checkout_boinc
	Kernel.exec("svn co http://boinc.berkeley.edu/svn/trunk/boinc --force")
end

def update_boinc
	Kernel.exec("svn update boinc --force")
end

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

def setup_and_make
	
	Dir.chdir "boinc" do
	
		puts "Modifying Automake files"
		
		
		
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
	when "checkout_boinc"
		checkout_boinc
	when "update_boinc"
		update_boinc
	when "make"
		make
	when "setup_and_make"
		setup_and_make
end


