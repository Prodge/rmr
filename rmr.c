/**
 * rmr by prodge
 *      
 *      http://prodge.net
 *      https://github.com/Prodge/rmr
 *      
 *      rm with additional functionality for recycling files
 *
 * Creates the following files in the .rmr/ folder in the users home directory
 *  - 'db' for storing file information
 *  - 'log' for storing log information
 *  - All files being recycled in the 'tmp/' folder
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>

bool toLog(char message[], char filename[]){
    // Implement this
}

bool delete(char filename[]){
    int status = remove(filename);
    if(status == -1){
        //toLog('file could not be deleted', filename)
        //error no has been set, do something with this
        return false;
    }
    return true;
}

int main(int argc, char **argv){
    int flag;
    if(argc == 1){
        //No arguments supplied
        //Running as silent server
        
        //Monitor db file, check if a file needs to be perm deleted, sleep
        printf("Not yet implemented\n");
        //sleep(60);
    }else{
        while((flag = getopt(argc, argv, "d:k:sr:nhcv")) != -1){
            switch(flag){
                case 'd':   //Delete file for d days
                    printf("Not yet implemented\n");
                    break;
                case 'k':   //Move to rmrtmp and never delete
                    printf("Not yet implemented\n");
                    break;
                case 's':   //Display status for all files rmrtmp
                    printf("Not yet implemented\n");
                    break;
                case 'r':   //Recursivley delete files and directories
                    printf("Not yet implemented\n");
                    break;
                case 'n':   //Delete on next boot
                    printf("Not yet implemented\n");
                    break;
                case 'h':   //Show help information
                    printf("Not yet implemented\n");
                    break;
                case 'c':   //Move to rmrtmp and compress
                    printf("Not yet implemented\n");
                    break;
                case 'v':   //Run in verbose mode
                    printf("Not yet implemented\n");
                    break;
            }
        }
    }
}
