#include "partproject.h"
// congruence [n_arg] [k_arg] [m_arg] [a] [b]
int main(int argc, char** argv)
{
   int i, a, b, truth;
   partopen(argv[1], argv[2], argv[3]);
   //when truth is 1, it's true
   truth = 1;
   a = atoi(argv[4]);
   b = atoi(argv[5]);
   for (i =0; (a*i) + b < 50000000 && truth; i++)
   {
       truth = parts[(a*i) + b] == 0;
       break;
   }
   
   if (truth)
      printf("yes\n");
   else
      printf("no at %i\n", i);
}
