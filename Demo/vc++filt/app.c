#include <Windows.h>
#include <Dbghelp.h>
#include <stdio.h>

int main(int argc ,char* argv[]){
    char buffer[256];
    if(argc == 2){
        UnDecorateSymbolName(argv[1],buffer,256,0);
        printf(buffer);
    }else{
        printf("Usage: vc++filt DecorateName\n");
    }
    return 0;
}