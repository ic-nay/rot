#include <stdio.h>

void printHelp(){
    printf("hellp!\n");
}

void parseArgs(int argcount, char* args[]){

}

int main(int argcount, char* args[]){
    if (argcount <= 1){
        printHelp();
    }
    else if (argcount > 4){
        perror("Too many arguments input into rot!\n");
    }
    else {
        for (int i = 1; i < argcount; i ++){
            printf("Arg %d: %s\n", i, args[i]);
        }
        parseArgs(argcount, args);
    }
    if (stdin == NULL){
        printf("Null rn\n");
    }
    else {
        printf("Not null tbh\n");
    }
}