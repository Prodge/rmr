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
bool toLog(char *message){
    // Print log to stdout if in verbose mode
    if(verbose)
        printf("%s\n", message);

    // If logging is enabled...

    // Implement this
    return true;
}

/*
 * Concatenates two given strings
 */
char* concat(char *string1, char *string2){
    char *result = malloc(strlen(string1) + strlen(string2) + 1);
    if(result){
        strcpy(result, string1);
        strcat(result, string2);
    }else{
        toLog("Memory allocation for string concatenation failed.");
    }
    return result;
}

/*
 * Validates whether a file can be deleted or not
 * Returns true if the file can be deleted
 */
bool canDelete(char *filename){
    bool state = true;
    // Validating file Exists
    if(access(filename, F_OK) == -1)
        toLog(concat("File does not exist: ", filename));
        state = false;

    // Validating Read Permission
    if(access(filename, R_OK) == -1)
        toLog(concat("User does not have read permission for file: ", filename));
        state = false;

    // Validating Write Permission
    if(access(filename, W_OK) == -1)
        toLog(concat("User does not have write permission for file: ", filename));
        state = false;

    return state;
}

/*
 * Permanantly delete file
 * Returns true if the deletion was successful
 */
bool delete(char *filename){
    // Checking if file exists and we can delete
    if(canDelete(filename) != 0){
        printf("Cannot delete file '%s'\n", filename);
        return false;
    }

    // Attempting to delete file
    int status = remove(filename);
    if(status == -1){
        toLog(concat("File could not be permanantly deleted: ", filename));
        printf("Cannot delete file '%s'\n", filename);
        return false;
    }
    toLog(concat("File permanantly deleted: ", filename));
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
        printf("Server not yet implemented\n");
        //sleep(60);
    }else{
        while((flag = getopt(argc, argv, "d:k:sr:nhcv")) != -1){
            switch(flag){
                case 'd':   //Delete file for d days
                    printf("Delete is Not yet implemented\n");
                    break;
                case 'a':   //archive to rmrtmp and never delete
                    printf("Archive not yet implemented\n");
                    break;
                case 's':   //Display status for all files rmrtmp
                    printf("Not yet implemented\n");
                    break;
                case 'r':   //Recursivley delete files and directories
                    printf("Recursive delete not yet implemented\n");
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
