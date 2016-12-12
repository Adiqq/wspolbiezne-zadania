#include<stdio.h>
#include<stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv){
    int inputSize = 512;
    char input[inputSize];
    pid_t all_child[10];
    int counter = 0;

    puts("Bash simulator initialized");
    while (fgets(input, inputSize, stdin) != NULL && !strstr(input, "quit")) {
        char *arg = strtok(input, " ");
        int i = 0;
        char *args[32];
        args[0] = arg;

        while (arg != NULL)
        {
            //remove EOF char
            char *pos;
            if ((pos=strchr(arg, '\n')) != NULL)
                *pos = '\0';

            args[i++] = arg;
            arg = strtok (NULL, " ");

        }
        //add terminal character to array
        args[i] = NULL;
        pid_t pid = fork();

        if(pid == 0){
            if(execvp(args[0], args) == -1){
                perror("Error");
            }
        } else if(pid != -1){
            all_child[counter++] = pid;
        } else{
            perror("Child could not be created");
        }
    }
    for(int i = 0; i < counter; i++)
    {
        kill(all_child[i], SIGTERM);
    }
    return 0;
}
