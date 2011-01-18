#include "partproject.h"
// congruence [filename] [a] [b]
int main(int argc, char** argv)
{
   int i, a, b, truth;
   partopen(argv[1]);
   //when truth is 1, it's true
   truth = 1;
   a = atoi(argv[2]);
   b = atoi(argv[3]);
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
