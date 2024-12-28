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

Things to look at
- getopt (https://www.man7.org/linux/man-pages/man3/getopt.3.html)

Other features worth considering
- Exclusions
- Case conversion

*/

#include <stdio.h>
#include <stdlib.h> //atoi
#include <stdbool.h>
#include <unistd.h> //isatty
#include <getopt.h>

void printHelp(){
    printf("help!\n");
}

int main(int argcount, char* args[]){

    int opt;
    int rot = 13;


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
        
        while((opt = getopt(argcount, args, "r:")) != -1){  
            switch(opt) {
                case 'r':
                    rot = atoi(optarg);  
                    break;
            }
        }
        printf("rot: %d\n", rot);
        // optind is for the extra arguments 
        // which are not parsed
        if (((optind - argcount) == 0)){
            if (stdinPresent){

            }
            else {
                perror("Nothing to rotate!");
                exit(1);
            }
        }
        else {
            for(; optind < argcount; optind++){
                printf("extra arguments: %s\n", args[optind]);  
            }
        }

    }
    exit(0);
}