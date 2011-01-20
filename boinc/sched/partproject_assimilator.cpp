// This file is part of BOINC.
// http://boinc.berkeley.edu
//
// Copyright (C) 2010-11 Eric Schultz, 2008 University of California
//
// BOINC is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// BOINC is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BOINC.  If not, see <http://www.gnu.org/licenses/>.

// Assimilator for PartProject
// If there's a valid, canonical result, the result is copied to the results
// directory. It is put into the following subdirectory based on the 
// number of n calculated, the k-regularity calculated and the mod m 
// used. For the a result with 50 million values for the 2-regular 
// partition function, mod 5 the results path would be:
// results/n50000000/k2/m5
// If a workunit failed, an error is written out to the results/errors file

#include <vector>
#include <string>
#include <cstdlib>

#include "boinc_db.h"
#include "error_numbers.h"
#include "filesys.h"
#include "sched_msgs.h"
#include "validate_util.h"
#include "sched_config.h"
#include "boost/regex.hpp"

using std::vector;
using std::string;

//writes an error out to the errors file in the results directory
int write_error(char* p) {
    static FILE* f = 0;
	int retval = boinc_mkdir(config.project_path("results"));
    if (retval) return retval;

    if (!f) {
        f = fopen(config.project_path("results/errors"), "a");
        if (!f) return ERR_FOPEN;
    }
    fprintf(f, "%s", p);
    fflush(f);
    return 0;
}

//main handler, moves the file to proper folder or writes out an error
int assimilate_handler(
    WORKUNIT& wu, vector<RESULT>& /*results*/, RESULT& canonical_result
) {
    int retval;
    char buf[1024];
    unsigned int i;

    retval = boinc_mkdir(config.project_path("results"));
    if (retval) return retval;

	retval = boinc_mkdir(config.project_path("results/n50000000"));
	if (retval) return retval;

    if (wu.canonical_resultid) {
        vector<FILE_INFO> output_files;
        const char *copy_path;
        get_output_file_infos(canonical_result, output_files);
        unsigned int n = output_files.size();
        bool file_copied = false;
        
		boost::regex reg("^partproject_\\d*?_\\d*?_(k\\d*?)_(m\\d+?)$");
		boost::cmatch matches;
		if(regex_match(wu.name, matches, reg))
		{
			FILE_INFO& fi = output_files[0];
			
			retval = boinc_mkdir(config.project_path("results/n50000000/%s",  matches[1].str().c_str()));
			if (retval) return retval;

			retval = boinc_mkdir(config.project_path("results/n50000000/%s/%s",  matches[1].str().c_str(), matches[2].str().c_str()));
			if (retval) return retval;

			copy_path = config.project_path("results/n50000000/%s/%s/%s", matches[1].str().c_str(), matches[2].str().c_str(),wu.name);
			
			retval = boinc_copy(fi.path.c_str() , copy_path);
			if (!retval) {
				file_copied = true;
			}
	        
			if (!file_copied) {
				
				sprintf(buf, "failed to copy for wu: %s - %s to %s\n", wu.name, fi.path.c_str(), copy_path);
				return write_error(buf);
			}
		}
		else
		{
			sprintf(buf, "regex error - %s\n", wu.name);
			return write_error(buf);
		}
    } else {
        sprintf(buf, "%s: 0x%x\n", wu.name, wu.error_mask);
        return write_error(buf);
    }
    return 0;
}
