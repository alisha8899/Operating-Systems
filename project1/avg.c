#include <stdio.h>
#include <stdlib.h>

void averageFunction(FILE *fp){
    double totalSum = 0;
    double totalLines = 0;
    double value;

    //adds each line to find total sum of the file
    while(fscanf(fp, "%lf\n", &value) == 1){
        ++totalLines;
        totalSum = totalSum +  value;
    }
    //empty file
    if(totalLines == 0){
        printf("%d\n", 0);
        return;
    }
    //prints average by dividing sum with total lines
    printf("%lf\n", totalSum / totalLines);
}

int main(int argc, char *argv[]){
    if(argc < 2 ){
        exit(0); //program ran and exit was successful
    }
    FILE *fp = fopen(argv[1], "r");
    // open input file that was given on command line
    if(fp == NULL){
        printf("avg: cannot open the input file\n");
        exit(1); //exit code that is non-zero means something went wrong
    }
    averageFunction(fp);
    fclose(fp);
    return 0;
}
