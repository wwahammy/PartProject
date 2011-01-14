#include "stdafx.h"

void delete_checkpoint()
{
	string resolved_name;
	boinc_resolve_filename_s(CHECKPOINT_FILE, resolved_name);
	
	if (boinc_file_exists(resolved_name.c_str()))
		boinc_delete_file(resolved_name.c_str());
}


int do_checkpoint(short * arry, int current_n)
{
	FILE * f = boinc_fopen("temp", "wb");
	if (!f)
		return OPEN_CHKPNT_TEMP_FAIL;
	
	int * a = new int[1];
	a[0] = current_n;

	//check for error

	fwrite(a, sizeof(int), 1, f);
	if (ferror(f))
		return OPEN_CHKPNT_TEMP_FAIL;

	//check for error
	fwrite(arry, sizeof(short), current_n, f);
	if (ferror(f))
		return OPEN_CHKPNT_TEMP_FAIL;
	
	fflush(f);
	fclose(f);

	//rename temp to the name of checkpoint file
	string resolved_name;
	boinc_resolve_filename_s(CHECKPOINT_FILE, resolved_name);
	delete_checkpoint();
	

	int retval = boinc_rename("temp", resolved_name.c_str());
    if (retval) 
		return retval;

	return OK;
}
// b_kvals is true if we're done with the partitions and doing the b_kvalues
// b_kvals is false if we're still doing paritions
int open_checkpoint_file(bool b_kvals, short* arry, int * current_n)
{
	string resolved_name;
	boinc_resolve_filename_s(CHECKPOINT_FILE, resolved_name);

	if (boinc_file_exists(resolved_name.c_str()))
	{
		FILE * f = boinc_fopen(resolved_name.c_str(), "rb");
		if (f == NULL)
		{
			return OPEN_CHKPNT_FAIL;
		}
		
		//get the current_n
		//int ret = fscanf(f, "%d", current_n);
		int r[1];
		fread(&r, sizeof(int), 1, f);
		if (ferror(f))
		{
			fclose(f);
			return READ_CURRENT_N_FROM_CHKPNT_FAIL;
		}
		
		(*current_n) = r[0];
		//load all the p_vals from checkpoint

		//ret = fseek(f, 1, SEEK_CUR);
		/*
		if (ret != 0)
		{
			fclose(f);
			if (b_kvals)
				return READ_B_KVAL_FROM_CHKPNT_FAIL;
			else
				return READ_PVAL_FROM_CHKPNT_FAIL;
		}*/

		int ret = fread(arry, sizeof(short), *current_n, f);
			
		if (ferror(f))
		{
			fclose(f);
			if (b_kvals)
				return READ_B_KVAL_FROM_CHKPNT_FAIL;
			else
				return READ_PVAL_FROM_CHKPNT_FAIL;
		}
		

		fclose(f);
	}

	return OK;
}

