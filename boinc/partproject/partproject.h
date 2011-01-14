#ifndef WIN32
	typedef unsigned char byte;
#endif

extern int open_input_file();
extern bool part_file_exists();

extern void delete_checkpoint();
extern int open_checkpoint_file(bool b_kvals, short * arry, int * current_n);
extern int do_checkpoint(short * arry, int current_n);

extern int calc_inverse_func(const int k);
extern int calc_inverse_func_kreg(const int k, int k_reg);
extern bool is_coefficient_negative(const int k);

extern int write_a_result(bool final, short * arry, int max_n, int k_reg, int mod);

extern int open_part_file(short * arry, int max_n);

short p(int n);
short b_k(int n);
