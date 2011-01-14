#include "stdafx.h"

bool part_file_exists()
{
	string partfile;
	boinc_resolve_filename_s(PART_FILE, partfile);
	int ret = boinc_file_exists(partfile.c_str());
	if (ret == 0)
		return false;
	else
		return true;
}

int open_part_file(short * arry, int max_n)
{
	string resolved_name;
	boinc_resolve_filename_s(PART_FILE, resolved_name);

	if (boinc_file_exists(resolved_name.c_str()))
	{
		FILE * f = boinc_fopen(resolved_name.c_str(), "rb");
		if (f == NULL)
		{
			return OPEN_PART_FILE_FAIL;
		}
		

		int ret = fread(arry, sizeof(short), max_n, f);
		
		if (ferror(f))
		{
			fclose(f);		
			return READ_FROM_PART_FILE_FAIL;

		}

		fclose(f);
	}

	return OK;
}
