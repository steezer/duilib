#include<stdio.h>
 #include <windows.h>
 typedef int (*AddFunc)(int ,int);
 typedef int (*SubFunc)(int ,int);
 typedef int (*MulFunc)(int ,int);
 typedef int (*DivFunc)(int ,int);
 int main(void)
 {
       int a=10,b=2;
       HMODULE hDll = LoadLibrary("math.dll");
       if (hDll != NULL)
       {
             AddFunc add = (AddFunc)GetProcAddress(hDll, "add");
             SubFunc sub = (SubFunc)GetProcAddress(hDll, "sub");
             MulFunc mul = (MulFunc)GetProcAddress(hDll, "mul");
             DivFunc div = (DivFunc)GetProcAddress(hDll, "div");

             if (add != NULL)
                printf("a+b=%d\n",add(a,b));
             if (sub != NULL)
                printf("a-b=%d\n",sub(a,b));
             if (mul != NULL)
                printf("a*b=%d\n",mul(a,b));
             if (div != NULL)
                printf("a/b=%d\n",div(a,b));

             FreeLibrary(hDll);
       }
 }