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

/*Setting mode to verbose by default*/
bool verbose = false;

/*Folder containing rmr recycle bin and database*/
char folder[] = ".rmr";

/*
 * Writes the input string to the log
 * Returns true upon success
 */
bool toLog(char message[]){
    // Implement this
    return true;
}

/*
 * Permanantly delete file
 */
bool delete(char filename[]){
    int status = remove(filename);
    if(status == -1){
        //toLog('file could not be deleted', filename)
        //error no has been set, do something with this
        return false;
    }
    return true;
}

/*
 * Returns true if the system has been initialised
 *      .rmr folder exists
 *      DB exists and is in valid state
 *      recycle bin folder exists
 */
bool isInitialised(){
    //implement this
    return true;
}

/*
 * Initialises the system for rmr
 *      Creates the rmr folder
 *      Creates the db
 *      Creates the recycle bin
 *      Creates the log file
 */
bool initialise(){
    return true;
}



int main(int argc, char **argv){
    //Initialise the system for rmr if it is not already
    if(! isInitialised()){
        if(! initialise()){
            // The system failed to initialise
            // Print to stderr
        }
    }

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
                    verbose = true;
                    break;
            }
        }
    }
}
