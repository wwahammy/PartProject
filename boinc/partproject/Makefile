BOINC_DIR = ../
BOINC_API_DIR = $(BOINC_DIR)/api
BOINC_LIB_DIR = $(BOINC_DIR)/lib

CXXFLAGS = -g -I$(BOINC_DIR) \
-I$(BOINC_LIB_DIR) \
-I$(BOINC_API_DIR) \
-L.

PROGS = partproject

all: partproject

libstdc++.a:
	ln -s `g++ -print-file-name=libstdc++.a`

clean:
	/bin/rm -f $(PROGS) *.o *.a libstdc++.a
	

partproject:  math.o result.o file.o checkpoint.o libstdc++.a partproject.o $(BOINC_API_DIR)/libboinc_api.a $(BOINC_LIB_DIR)/libboinc.a 
	$(CXX) $(CXXFLAGS) -o partproject partproject.o math.o result.o file.o \
	checkpoint.o libstdc++.a -pthread $(BOINC_API_DIR)/libboinc_api.a \
	$(BOINC_LIB_DIR)/libboinc.a


