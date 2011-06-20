#include "partproject.h"
// get_n [n_arg] [k_arg] [m_arg] [n to get]
int main(int argc, char** argv)
{  
   int n_test = 0;
   partopen(argv[1], argv[2], argv[3]);
   n_test = atoi(argv[4]);
   printf("b_%i(%i) mod %i = %i\n", k, n_test, m, parts[n_test]);
   return 0;
}
