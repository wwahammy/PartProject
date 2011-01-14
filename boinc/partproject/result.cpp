#include "stdafx.h"

//if final is true we write out the final result
// if final is false we're writing out the part file
int write_a_result(bool final, short * arry, int max_n, int k_reg, int mod)
{
	string output_name;
	if (final)
		boinc_resolve_filename_s(OUTPUT_FILE, output_name);
	else
		boinc_resolve_filename_s(PART_FILE, output_name);

	FILE * f = boinc_fopen(output_name.c_str(), "wb");
	if (f == NULL)
	{
		if (final)
			return OPEN_OUTPUT_FAIL;
		else
			return OPEN_PART_FILE_FAIL;
	}
	int * stuff = new int[3];
	
	
	if (final)
	{
		stuff[0] = max_n;
		stuff[1] = k_reg;
		stuff[2] = mod;
		fwrite(stuff, sizeof(int),  3, f);
		//do final
		//ofstr << max_n << " ";
		//ofstr << k_reg << " ";
		//ofstr << mod << " ";
		
		fwrite(arry, sizeof(short), max_n, f);
		/*
		for(int i = 0; i < max_n; i++)
		{
			//ofstr << arry[i];
		}*/
	}
	else
	{
		/*ofstream ofstr(f);
		//do part file
		for(int i = 0; i < max_n; i++)
		{
			ofstr << arry[i];
		}
		ofstr.close();*/

		fwrite(arry, sizeof(short), max_n, f);
	}
	

	delete [] stuff;
	fflush(f);
	fclose(f);

	return OK;
}

