// This file is part of BOINC.
// http://boinc.berkeley.edu
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

// Work generator for the PartProject file. Creates work units.

#include <unistd.h>
#include <cstdlib>
#include <string>
#include <cstring>

#include "boinc_db.h"
#include "error_numbers.h"
#include "backend_lib.h"
#include "parse.h"
#include "util.h"
#include "svn_version.h"

#include "sched_config.h"
#include "sched_util.h"
#include "sched_msgs.h"
#include "str_util.h"
#define REPLICATION_FACTOR 2
#define MAX_K 150
#define MAX_M 100


// globals
//
char* wu_template;
DB_APP app;
int start_time;
int seqno;

// create one new job
//
int make_job(int k_reg, int m) {
    DB_WORKUNIT wu;
    char name[256], path[256], command_line[256];
    const char* infiles[1];
    int retval;

    // make a unique name (for the job and its input file)
    //
	sprintf(name, "partproject_%d_%d_k%d_m%d", start_time, seqno++, k_reg, m);

    // Create the input file.
    // Put it at the right place in the download dir hierarchy
    //
    retval = config.download_path(name, path);
   

    // Fill in the job parameters
    //
    wu.clear();
    wu.appid = app.id;
    strcpy(wu.name, name);
    
    wu.min_quorum = REPLICATION_FACTOR;
    wu.target_nresults = REPLICATION_FACTOR;
    wu.max_error_results = REPLICATION_FACTOR*4;
    wu.max_total_results = REPLICATION_FACTOR*8;
    wu.max_success_results = REPLICATION_FACTOR*4;
	wu.rsc_fpops_bound = 10e50;
	wu.rsc_disk_bound = 10e7 * 4;
	wu.rsc_memory_bound = 10e7 * 3;

	sprintf(command_line, "50000000 %d %d", k_reg, m);
	//strcpy(wu.command_line, command_line);
	
    // Register the job with BOINC
    //
    return create_work(
        wu,
        wu_template,
        "templates/partproject_result.xml",
        config.project_path("templates/partproject_result.xml"),
        infiles,
        0,
        config,
		command_line
    );
}

// creates all the workunits
void main_loop() {
    int retval;


	for (int k = 2; k < MAX_K; k++)
	{
		for (int m= 2; m< MAX_M; m++)
		{
			retval = make_job(k,m);
			if (retval)
			{
				log_messages.printf(MSG_CRITICAL,
					"can't make job: %d\n", retval);
				exit(retval);
			}
			
		}
	}
}


// grabs the work unit template, adds what is needed and then creates
// the work units.
int main(int argc, char** argv) {
    int i, retval;

    retval = config.parse_file();
    if (retval) {
        log_messages.printf(MSG_CRITICAL,
            "Can't parse config.xml: %s\n", boincerror(retval)
        );
        exit(1);
    }

    retval = boinc_db.open(
        config.db_name, config.db_host, config.db_user, config.db_passwd
    );
    if (retval) {
        log_messages.printf(MSG_CRITICAL, "can't open db\n");
        exit(1);
    }
    if (app.lookup("where name='partproject'")) {
        log_messages.printf(MSG_CRITICAL, "can't find app\n");
        exit(1);
    }
    if (read_file_malloc(config.project_path("templates/partproject_wu.xml"), wu_template)) {
        log_messages.printf(MSG_CRITICAL, "can't read WU template\n");
        exit(1);
    }

    start_time = time(0);
    seqno = 0;

    log_messages.printf(MSG_NORMAL, "Starting\n");

    main_loop();
}
