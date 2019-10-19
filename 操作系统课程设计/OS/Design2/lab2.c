#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argv[])
{
   int a=syscall(333,argv[1],argv[2]);
   printf("%d\n",a);
   return 0;
}
