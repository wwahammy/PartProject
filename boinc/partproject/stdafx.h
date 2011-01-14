// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#include <stdio.h>

#ifdef WIN32
#include <tchar.h>
#include "boinc_win.h"
#else
	#include "config.h"
	#include <cstdio>
	#include <cctype>
	#include <ctime>
	#include <cstring>
	#include <cstdlib>
	#include <csignal>
	#include <unistd.h>

#endif

#include "str_util.h"
#include "util.h"
#include "filesys.h"
#include "boinc_api.h"
#include "mfile.h"
#include "ret_vals.h"
using namespace std;

// TODO: reference additional headers your program requires here
#include "assert.h"
#include "partproject.h"

#define INPUT_FILE "part_input.txt"
#define CHECKPOINT_FILE "part_checkpoint.bin"
#define OUTPUT_FILE "part_output.bin"
#define PART_FILE "p_vals.bin"
