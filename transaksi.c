#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp;

    fp = fopen("databuku.docx", "r");

    if(fp == NULL){
        printf("The file is not opened");
        exit(0);
    }
    else {
        printf("The file is created Successfully.");
    }
   
    return 0;

}