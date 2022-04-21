#include <stdio.h>
int main()
{
    int fori;
    int forw;
    int i;

   while ( i < 4)
   {
       fori  = fork();
       if(fori == 0)   printf("djjd\n");
       i++;
   }
   waitpid(-1, NULL, 0);
}