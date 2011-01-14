// partproject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
int max_n = -1;
int m = -1;
int k_reg = -1;

int current_n = 2;
short * p_vals;
short * b_kvals;



#define CHECK_FOR_FAIL_IN_MAIN(val) if (val != OK) goto boinc_fail;
#define FAIL_IS_ZERO_IN_MAIN(val) if (val == 0) goto boinc_fail;
#define CALL_P(p_ret, p_argument) if (p_vals[p_argument] != -1) p_ret = p_vals[p_argument]; \
									else p_ret = p(p_argument);


inline int open_input_file()
{
	string resolved_name;
	int ret_val = boinc_resolve_filename_s("part_input.txt", resolved_name);
	if (ret_val != 0)
		return RESOLVE_FILENAME_FAIL;
	
	FILE * f = boinc_fopen(resolved_name.c_str(), "rb");
	if (f == NULL)
		return OPEN_INPUT_FILE_FAIL;

	//get the max_n
	int ret = fscanf(f, "%d", &max_n);
	
	if (ret == NULL)
	{
		fclose(f);
		return READ_N_FROM_INPUT_FAIL;
	}
	
	//get the k_reg

	ret = fscanf(f, "%d", &k_reg);
	
	if (ret == NULL)
	{
		fclose(f);
		return READ_K_FROM_INPUT_FAIL;
	}


	//get the m
	ret = fscanf(f, "%d", &m);
	
	if (ret == NULL)
	{
		fclose(f);
		return READ_M_FROM_INPUT_FAIL;
	}

	fclose(f);
	
	return OK;
}





/*
inline bool term_pred(term * t1, term * t2)
{
    return t1->p_arg < t2->p_arg;
}*/

/*this calculates the terms that should be in p(p_arg)'s and the coefficients
  for the equation used to calculate the p(p_arg)'s.

  Explanation: for n=4 the real equation is -p(2)x^4 - p(3)x^4 + p(4)x^4 = 0
  This function will add terms with the following values:
  
  p_arg	|	negative
  ------------------
  2		|	true
  3		|	true
  4		|	false
**/
/*
void equation_dev(const int n, vector<term *> * terms)
{
    int i;
    //this loops through p(0)x^0+ p(1)x^1 + p(2)x^2...

   
	int p_arg = -1;
	bool neg = false;
    for (i = 0, p_arg = inverse_poly.at(i)->p_arg, neg = inverse_poly.at(i)->negative; 
		p_arg <= n; 
		i++, p_arg = inverse_poly.at(i)->p_arg, neg = inverse_poly.at(i)->negative)
    {
        term  * temp_term = new term;
        temp_term->p_arg = n-p_arg;
        temp_term->negative = neg;
        terms->push_back(temp_term);
    }
   
     //    ofstr << "for n=" << n << ", i=" << i << " " << j  <<" j's have been looped" << "\r\n";
    
   // ofstr << "for n=" << n << " " << i << " i's have been looped" << "\r\n";
}
*/

short b_k(int n)
{
	assert(n >=0);
	if (b_kvals[n] >= 0)
		return b_kvals[n];
	
	 int current_total = 0;
    
    /* the list of terms in an equation. A term is a custom data type that holds two things: the value of n in a p(n)
       term (called p_arg) and a boolean value (called negative), that when true indicates the coefficient is -1 and when false indicates the coefficient is 1.

       For example for -p(2) - p(3) + p(4) = 0 the list of terms in the equation have the following values:
       p_arg	|	negative
       ------------------
       2		|	true
       3		|	true
       4		|	false
    */
   
    
    /*equation_dev actually fills terms with what the terms should be for a given n exponent of x. for x^4 it would be
      the terms listed just above the previous line.
    */
    /*
    time_t start_equa_dev = time(NULL);*/
   
   /* time_t end_equa_dev = time(NULL);

    
    cout << "Total time to do equation_dev(" << n << ") is " << difftime(end_equa_dev,start_equa_dev) << "\r\n";*/

    int pos_test = -1;
    int neg_test = -1;
    bool is_neg = false;
    bool firstbreak = false;
    

    

    //get the last term
   // term t = terms[terms.size() - 1];

    //initialize our return value to -1 (no need to do so but could be useful for debugging later)
    short ret = 0;

	for (int i =0, not_i = -1 ; true ; i++, not_i--)
    {
        pos_test = n - calc_inverse_func_kreg(i, k_reg);
        if (pos_test >= 0)
        {
            is_neg = is_coefficient_negative(i);
            if (is_neg)
                current_total -= (int)p_vals[pos_test];
            else
                current_total += (int)p_vals[pos_test];
        }
        else
        {
            firstbreak = true;
        }
        
        neg_test = n - calc_inverse_func_kreg(not_i, k_reg);
        if (neg_test >= 0)
        {
            is_neg = is_coefficient_negative(not_i);
            if (is_neg)
                current_total -= (int)p_vals[neg_test];
            else
                current_total += (int)p_vals[neg_test];
        }
        else
        {
            if (firstbreak)
                break;
        }
            
    }

    
    
    //we mod the ret value by mod
    while (current_total < 1)
    {
        current_total += m;
    }
    ret = current_total % m;
    
    //we record the value of p(n) for later uses
    b_kvals[n] = ret;

   

    return ret;

}

short p(int n)
{
	assert(n >=0);
    /**we keep the results of p(n) calcs so once we know them 
    so we don't need to calculate them again
    */
	if (p_vals[n] >= 0)
        return p_vals[n];

    /** current_total = the total calculated values of p funcs already
    so if the equation is -p(2) - p(3) + p(4) = 0 and we know p(2) = 2 but we haven't calculated p(3) or p(4) yet,
    then current_total = -2
    **/
    int current_total = 0;
    
    /* the list of terms in an equation. A term is a custom data type that holds two things: the value of n in a p(n)
       term (called p_arg) and a boolean value (called negative), that when true indicates the coefficient is -1 and when false indicates the coefficient is 1.

       For example for -p(2) - p(3) + p(4) = 0 the list of terms in the equation have the following values:
       p_arg	|	negative
       ------------------
       2		|	true
       3		|	true
       4		|	false
    */
   
    
    /*equation_dev actually fills terms with what the terms should be for a given n exponent of x. for x^4 it would be
      the terms listed just above the previous line.
    */
    /*
    time_t start_equa_dev = time(NULL);*/
   
   /* time_t end_equa_dev = time(NULL);

    
    cout << "Total time to do equation_dev(" << n << ") is " << difftime(end_equa_dev,start_equa_dev) << "\r\n";*/

    int pos_test = -1;
    int neg_test = -1;
    bool is_neg = false;
    bool firstbreak = false;
    

    

    //get the last term
   // term t = terms[terms.size() - 1];

    
    short ret = 0;

	for (int i =1; true ; i++)
    {
        pos_test = n - calc_inverse_func(i);
        if (pos_test >= 0)
        {
            is_neg = is_coefficient_negative(i);
            if (is_neg)
                current_total += p(pos_test);
            else
                current_total -= p(pos_test);
        }
        else
			break;
            
    }
	
	for (int not_i = -1 ; true ; not_i--)
    {
        
        neg_test = n - calc_inverse_func(not_i);
        if (neg_test >= 0)
        {
            is_neg = is_coefficient_negative(not_i);
            if (is_neg)
                current_total += p(neg_test);
            else
                current_total -= p(neg_test);
        }
		else
			break;
            
    }
    
    
    //we mod the ret value by mod
    while (current_total < 1)
    {
        current_total += m;
    }
    ret = current_total % m;
    
    //we record the value of p(n) for later uses
    p_vals[n] = ret;

   

    return ret;
}




inline int write_part_results()
{
	return write_a_result(false, p_vals, max_n, k_reg, m);
}

inline int write_final_results()
{
	return write_a_result(true, b_kvals, max_n, k_reg, m);
}

inline int open_part_checkpoint()
{
	return open_checkpoint_file(false, p_vals, &current_n);
}

inline int open_b_k_checkpoint()
{
	return open_checkpoint_file(true, b_kvals, &current_n);
}

int main(int argc, char** argv)
{
	
	int ret_val = boinc_init();
	bool ignore_part_file_load = false;
	CHECK_FOR_FAIL_IN_MAIN(ret_val)

	//open input file
	//ret_val = open_input_file();
	if (argc != 4)
		ret_val = BAD_CMD_LINE_PARAMS;

	CHECK_FOR_FAIL_IN_MAIN(ret_val)

	max_n = atoi(argv[1]);
	FAIL_IS_ZERO_IN_MAIN(max_n)

	k_reg = atoi(argv[2]);
	FAIL_IS_ZERO_IN_MAIN(k_reg)
	
	m = atoi(argv[3]);
	FAIL_IS_ZERO_IN_MAIN(m)
	
	//init p_vals with 0s
	p_vals = new short[max_n];
	b_kvals = new short[max_n];
    for (int i = 0; i < max_n; i++)
    {
        p_vals[i] = -1;
		b_kvals[i] = -1;
    }
	
    p_vals[0] = 1;
    p_vals[1] = 1;
	b_kvals[0] = 1;
	/*first check to see if the partition file has been written
		if it hasn't the checkpoint will have p_vals

	*/
	//we just ran finished the part file so no need to load it
	
	/*if the part file hasn't been written, the checkpoint will have b_kvals*/
	if (!part_file_exists())
	{
		//open checkpoint and load from there if it exists
		ret_val = open_part_checkpoint();
		CHECK_FOR_FAIL_IN_MAIN(ret_val)


		for (; current_n < max_n; current_n++)
		{
			if (boinc_time_to_checkpoint() )
			{
				do_checkpoint(p_vals, current_n);
				boinc_checkpoint_completed();
			}

			#if _DEBUG && defined(CHECKPOINTS)
			if (current_n % 100 == 0)
				do_checkpoint(p_vals, current_n);
			#endif

			p(current_n);
			boinc_fraction_done((double)current_n/((double)max_n *2));
		}
		
		//write finalresults
		ret_val = write_part_results();
		CHECK_FOR_FAIL_IN_MAIN(ret_val);
		
		#if _DEBUG && defined(CHECKPOINTS)
		for (int i =0; i < 100; i++)
		{
			cout << i << " = " << (unsigned int) p_vals[i] << "\r\n";
		}
		#endif

		//delete old checkpoint file
		delete_checkpoint();

		current_n = 0;
		ignore_part_file_load = true;
	}
	
	if (!ignore_part_file_load)
	{
		//we have a part file so just load the stupid thing
		ret_val = open_part_file(p_vals, max_n);
		CHECK_FOR_FAIL_IN_MAIN(ret_val);
			
	}

	
	current_n = 1;

	//create the b_kvals
	ret_val = open_b_k_checkpoint();
	
	CHECK_FOR_FAIL_IN_MAIN(ret_val)

	for (; current_n < max_n; current_n++)
	{
		if (boinc_time_to_checkpoint() )
		{
			do_checkpoint(b_kvals, current_n);
			boinc_checkpoint_completed();
		}

		#if _DEBUG && defined(CHECKPOINTS)
		if (current_n % 100 == 0)
			do_checkpoint(b_kvals, current_n);
		#endif

		b_k(current_n);
		boinc_fraction_done((double)current_n/((double)max_n *2) + .5);
	}
	
	//write finalresults
	ret_val = write_final_results();
	CHECK_FOR_FAIL_IN_MAIN(ret_val);
	
	//finish!
	boinc_finish(0);
	
	return OK;

boinc_fail: 
	{
	delete_checkpoint();
	boinc_finish(ret_val);
	return ret_val;}
}


#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR Args, int WinMode) {
    LPSTR command_line;
    char* argv[100];
    int argc;

    command_line = GetCommandLineA();
    argc = parse_command_line( command_line, argv );
    return main(argc, argv);
}
#endif

