#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    //pipe connection
    int fd[2];
    pid_t child;
    //average variables
    double totalSum = 0;
    double totalLines = 0;
    double value;

    //making a child process by initializing
    for(int i = 1; i < argc; i++){
        if(pipe(fd) == -1){
            fprintf(stderr, "The pipe failed");
            return 1;
        }
        child = fork();
        if(child < 0) { //fork failed
            fprintf(stderr, "The fork failed");
            return 1;
        }
        if(child == 0) { //child new process
            //open input file in read mode
            FILE *fp = fopen(argv[i], "r");
            close(fd[0]);
            if (fp == NULL) {
                printf("avg: cannot open the input file\n");
                exit(1); //exit code that is non zero means something went wrong
            }
            //adds each line to find total sum in file
            while (fscanf(fp, "%lf\n", &value) == 1) {
                ++totalLines;
                totalSum = totalSum + value;
            }
            //empty file
            if (totalLines == 0) {
                printf("The file is empty");
                return 0;
            }
            // write num and sum for parent process
            write(fd[1], &totalSum, sizeof(totalSum));
            write(fd[1], &totalLines, sizeof(totalLines));
            close(fd[1]);
            fclose(fp);
            exit(0);
        }
        else {
            wait(NULL);
            close(fd[1]);
           read(fd[0], &totalSum, sizeof(totalSum));
           read(fd[0], &totalLines, sizeof(totalLines));
        }
        close(fd[0]);
    }
    //prints average by dividing sum with total lines
    printf("%lf\n", totalSum/totalLines);
    return 0;
}



