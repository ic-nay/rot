/*
THE PLAN

Really quite simple

1. We've got some input!
2. Is there any standard input? x
3. How many arguments are there? x
4. If there are too many, fail out. x
5. If there aren't too many, pass along the necessary information to the rot function
5.5. If there isn't any input, just arguments. Well honestly that's probably fine. Idk. We'll see.
6. rot
7. profit

*/

#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h> //atoi
#include <stdbool.h>
#include <unistd.h> //isatty
#include <getopt.h>

void printHelp(){
    printf("help!\n");
}

char rot(char c, int offset, bool reversed){
    printf("Offsetting %c by %d\n", c, offset);

}

int main(int argcount, char* args[]){

    int opt;
    int offset = 13;
    bool reversed = false;


    //Used for deciding which input will be used depending on whether or not this is being piped
    bool stdinPresent = true;

    if (isatty(fileno(stdin)) == 1){
        printf("Nothing in STDIN!\n");
        stdinPresent = false;
    }
    
    if (argcount <= 1 && stdinPresent == false){
        //Too few args, default help screen
        printHelp();
    }
    else if (argcount > 4){
        //Too many args
        perror("Too many arguments input into rot!\n");
    }
    else {
        for (int i = 0; i < argcount; i ++){
            printf("Arg %d: %s\n", i, args[i]);
        }
        
        while((opt = getopt(argcount, args, "o:hr")) != -1){  
            switch(opt) {
                case 'o':
                    offset = atoi(optarg);  
                    break;
                case 'r':
                    reversed = true;
                    break;
                case 'h':
                    printHelp();
                    exit(0);
                    break;
            }
        }
        printf("rot: %d\n", offset);

        if (((optind - argcount) == 0)){
            char nextChar;

            if (stdinPresent){
                nextChar = getchar();
                while (nextChar != EOF){
                    rot(nextChar, offset, reversed);
                    nextChar = getchar();
                }
                exit(0);
            }
            else {
                perror("Nothing to rotate!");
                exit(1);
            }
        }
        else {
            int i;
            int len;
            for(; optind < argcount; optind++){
                //There are better, more efficient ways to do this, which I cannot be bothered with for a silly toy
                len = strlen(args[optind]);
                for (i = 0; i < len; i ++){
                    rot(args[optind][i], offset, reversed);
                }
                
            }
        }

    }
    exit(0);
}