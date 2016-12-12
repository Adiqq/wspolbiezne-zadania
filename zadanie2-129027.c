#include<stdio.h>
#include<stdlib.h>
#include <memory.h>
#include <unistd.h>

void processInput(char *input, int *quitFlag);
void handleQuit(int *quitFlag);
void handleCommand(char *command, char **args);
void tokenize(char *input, char **delimited, int delimitedSize);

int main(int argc, char **argv){
    int inputSize = 512;
    char input[inputSize];
    char *result;
    int quit = 0;

    puts("Bash simulator initialized");
    while (result != NULL && quit == 0) {
        result = fgets(input, inputSize, stdin);
        processInput(input, &quit);
    }
    free(input);
    return 0;
}

void processInput(char* input, int* quitFlag){
    if(strstr(input, "quit")){
        handleQuit(quitFlag);
    } else{
        char *command;
        int argumentsSize = 32;
        char *args[argumentsSize];
        memset(args, 0, sizeof(args));
        tokenize(input, args, argumentsSize);
        command = args[0];

        handleCommand(command, args);
    }
}

void handleQuit(int* quitFlag){
    *quitFlag = 1;
}

void handleCommand(char *command, char **args){
    if(fork() == 0){
        puts("executing");
        execvp(command, args);
        exit(0);
    }
}

void tokenize(char *input, char **delimited, int delimitedSize){
    char *arg = strtok(input, " ");
    delimited[0] = arg;
    int i = 1;
    while(arg != NULL && i < delimitedSize){
        arg = strtok(NULL, " ");
        delimited[i] = arg;
        i++;
    }
}
