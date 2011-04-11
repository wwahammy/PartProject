#include "partproject.h"
// typed_congruences [n_arg] [k_arg] [m_arg] [a]
int main(int argc, char** argv)
{
   int i, a, b;
   int * b_true;
   partopen(argv[1], argv[2], argv[3]);
   a = atoi(argv[4]);
   
   //create the b_true array and init to true
   b_true = (int* )malloc(sizeof(int)* a);
   for (i = 0; i < a; i++)
   {
      b_true[i] = 1;
   }
   
   for (b = 0; b < a; b++)
   {
      for (i =0;  (a*i) + b < 50000000 && b_true[b]; i++)
      {
          b_true[b] = parts[(a*i) + b] == 0;
      }
   }

   printf( "{");
   for (i = 0; i < a; i++)
   {
      if (b_true[i])
         printf("%i,", i);
   }
   
   printf( "}");
   
   return 0;
}
