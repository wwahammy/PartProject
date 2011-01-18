#include "partproject.h"
// get_n [filename] [n to test]
int main(int argc, char** argv)
{  
   int n_test = 0;
   partopen(argv[1]);
   n_test = atoi(argv[2]);
   printf("b_%i(%i) = %i\n", k, n_test, parts[n_test]);
   return 0;
}
