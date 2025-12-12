#include<stdio.h>
#include "method1.h"
#include <stdlib.h>
int main(int argc,char** argv){
    if(argc < 3) {
        printf("Usage: %s <size> <location>\n", argv[0]);
        return 1;
    }
    int size = atoi(argv[1]);
    char* location = argv[2];
    method1(size, location);
    return 0;
}
