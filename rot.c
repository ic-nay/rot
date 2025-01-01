#include <stdio.h>
#include <string.h> //strlen
#include <stdlib.h> //atoi
#include <stdbool.h>
#include <unistd.h> //isatty
#include <getopt.h>

void printHelp(){
    printf("Usage: rot [OPTION] [TEXT]\n");
    printf("rot allows you to rotate a string of text, like a ceasar cipher!\n");
    printf("Example: rot -o 2 'hello world'\n");
    printf("Example: rot -o 2 -r 'fcjjm umpjb'\n");
    printf("Options:\n");
    printf("-o    The offset by which text will be rotated.\n");
    printf("-r    Reverses the direction the offset is applied. By default, subtracts.\n");
    printf("-h    Prints this help menu. Prevents any other output.\n");
    exit(0); //Exits to prevent any other output
}

void rot(char c, int offset, bool reversed){

    char lower_limit, upper_limit;
    bool isletter = false;

    if ((c >= 'A')&&(c <= 'Z')){
        lower_limit = 'A';
        upper_limit = 'Z';
        isletter = true;
    }
    else if ((c >= 'a')&&(c <= 'z')){
        lower_limit = 'a';
        upper_limit = 'z';
        isletter = true;
    }

    if (isletter){
        char newchar;

        newchar = reversed ? c + offset : c - offset;

        //Deals with wraparound

        if (newchar > upper_limit){
            newchar = lower_limit + (newchar-upper_limit) - 1;
        }

        else if (newchar < lower_limit){
            newchar = upper_limit - (lower_limit - newchar) + 1;
        }

        printf("%c", newchar);
    }

    else {
        printf("%c", c);
    }

}

int main(int argcount, char* args[]){

    int opt;
    int offset = 13;
    bool reversed = false;


    //Used for deciding which input will be used depending on whether or not this is being piped
    bool stdinPresent = true;

    if (isatty(fileno(stdin)) == 1){
        stdinPresent = false;
    }
    
    if (argcount <= 1 && stdinPresent == false){
        //Too few args, default help screen
        printHelp();
    }
    else if (argcount > 6){
        //The maximum number of flags and arguments which can be put into this.
        perror("Too many arguments input into rot!\n");
    }
    else {
        
        while((opt = getopt(argcount, args, "o:hr")) != -1){  
            switch(opt) {
                case 'o':
                    offset = atoi(optarg) % 26; //Ensures all offsets fall between 0 and 25.
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
        //Checks if there are any additional arguments (i.e. text to be rotated).
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
            printf("\n");
        }

    }
    exit(0);
}