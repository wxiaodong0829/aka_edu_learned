#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _STADARG
#define _STADARG

typedef char *va_list;

#define va_arg(ap, T)   (*(T*)(((ap) += _Bnd(T, 3U)) - _Bnd(T, 3U)))
#define va_end(ap)  (void)0
#define va_start1(ap, A) (void)((ap) = (char *)&(A) + _Bnd(A, 3U))
#define va_start(ap, A) (void)((ap) = (char *)&(A) )
#define _Bnd(X, bnd) (sizeof(X) + (bnd) & ~(bnd))
#endif 

void vstrcat(const char *format, ...)
{
    va_list ap;
    char c;
    char *p;

   va_start1(ap, format);
//   p = va_arg(ap, char*); 
//   while(strcmp(p, NULL))
   p = va_arg(ap, char*); 
   printf("%s\n", p);
//    va_end(ap);
}

int main(void)
{
   vstrcat("hello", "world", "I", "you", "NULL"); 

   return 0;

}



