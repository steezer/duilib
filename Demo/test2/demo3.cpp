#include<stdio.h>
#include "math.h"

static int two(int num){
    return num*2;
}

namespace Test{
    void demo(){
        int a=10,b=2;
        printf("a+b=%d\n",Utils::add(a,b));
        printf("a-b=%d\n",Utils::sub(a,b));
        printf("a*b=%d\n",Utils::mul(a,b));
        printf("a/b=%d\n",Utils::div(a,b));
        printf("double: %d\n",two(a+b));
    }
}

 int main(void)
 {
    Test::demo();
 }