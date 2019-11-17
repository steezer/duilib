#include<stdio.h>
#include "math.h"
 int main(void)
 {
    int a=10,b=2;
    printf("a+b=%d\n",Utils::add(a,b));
    printf("a-b=%d\n",Utils::sub(a,b));
    printf("a*b=%d\n",Utils::mul(a,b));
    printf("a/b=%d\n",Utils::div(a,b));
 }