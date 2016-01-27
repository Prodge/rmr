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
 *
 * Dependencies:
 *  - Sqlite3
 *      - libsqlite3-dev
 *      - sqlite3
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <unistd.h>
#include <sqlite3.h>
#include <sys/stat.h>
#include <sys/types.h>

/*Upper bound for path length*/
int PATH_MAX_LENGTH = 2000;

/*Setting mode to verbose by default*/
bool verbose = false;

/*Users home folder*/
char *homeFolder;

/*Folder containing rmr recycle bin and database*/
char *appFolder = ".rmr";

/*Path to appFolder*/
char *appPath;

/*Folder containing all deleted files*/
char *recycle_folder = "recycle";

/*Options list*/
char *options = "d:a:sr:nhcv";

/*The directory from which rmr is being run*/
char *currentDirectory;

/*iFolder containing the log*/
char *logFile = "rmr.log";

/*Database Pointer*/
sqlite3 *db;

/*Database Name*/
char *databaseName = "rmr.db";

/*File states*/
int STATE_ARCHIVED              = 0;
int STATE_DELETED               = 1;
int STATE_DELETE_ON_NEXT_BOOT   = 2;
int STATE_DELETE_IN_N_DAYS      = 3;


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
    if(access(filename, F_OK) == -1){
        toLog(concat("File does not exist: ", filename));
        state = false;
    }

    // Validating Read Permission
    if(access(filename, R_OK) == -1){
        toLog(concat("User does not have read permission for file: ", filename));
        state = false;
    }

    // Validating Write Permission
    if(access(filename, W_OK) == -1){
        toLog(concat("User does not have write permission for file: ", filename));
        state = false;
    }

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
 * Returns true if the system has been initialized
 *      .rmr folder exists
 *      DB exists and is in valid state
 *      recycle bin folder exists
 */
bool isInitialized(){
    //implement this
    return false;
}

/*
 * Initializes the system for rmr
 *      Creates the rmr folder
 *      Creates the db
 *      Creates the recycle bin
 *      Creates the log file
 */
void initialize(){
    //Log folder may not be created yet so we buffer any
    //log outputs here until we know it exists.
    char *logBuffer = "System required Initialization.\n";

    // Create rmr folder if it does not exist
    struct stat st= {0};
    if (stat(concat(homeFolder, appFolder), &st) == -1) {
        if(mkdir(concat(homeFolder, appFolder), 0777) == -1){
            fprintf(stderr, "Could not create .rmr folder in home directory.\n");
            exit(EXIT_FAILURE);
        }
        logBuffer = concat(logBuffer, "Created rmr home folder directory.");
    }else{
        logBuffer = concat(logBuffer, "rmr home folder directory already exists.");
    }

    // Create log file if it does not exist
    if(access(concat(appPath, logFile), F_OK) == -1){
        fopen(concat(appPath, logFile), "ab+");
        toLog(logBuffer);
        toLog("Log file does not exist. Creating log file.");
    }else{
        toLog(logBuffer);
        toLog("Log file already exists");
    }

    // Create recycle folder if it does not exist
    struct stat stu= {0};
    if (stat(concat(appPath, recycle_folder), &stu) == -1) {
        if(mkdir(concat(appPath, recycle_folder), 0777) == -1){
            fprintf(stderr, "Could not create recycle folder in _home_/.rmr.\n");
            exit(EXIT_FAILURE);
        }
        toLog("Recycle folder does not exist. Creating recycle folder.");
    }else{
        toLog("Recycle folder already exists.");
    }

    // Checking if database exists
    if(access(concat(appPath, databaseName), F_OK) == -1){
        toLog("Database does not exist. Creating Database.");

        // Creating database
        if(sqlite3_open(concat(appPath, databaseName), &db)){
            fprintf(stderr, "Cant open database:\n    %s\n", sqlite3_errmsg(db));
            exit(EXIT_FAILURE);
        }else{
            toLog("Opened Database Successfully");
        }

        // Creating tables
        char *zErrMsg = 0;
        char *sql = "CREATE TABLE FILES("  \
                "ID INT PRIMARY     KEY                 NOT NULL," \
                "ORIGINAL_PATH      VARCHAR(2000)       NOT NULL," \
                "FILENAME           VARCHAR(255)        NOT NULL," \
                "STATE              INT                 NOT NULL," \
                "DAYS_UNTILL_DELETE INT                 NOT NULL," \
                "DATE_DELETED       DATETIME            NOT NULL);";

        if(sqlite3_exec(db, sql, NULL, 0, &zErrMsg) == SQLITE_OK){
            toLog("Successfully Created Files Table");
        }else{
            fprintf(stderr, "Failed to create Files table");
            exit(EXIT_FAILURE);
        }
    }else{
        toLog("Database already exists.");
    }

    toLog("Successfully Initialized rmr");
}

/*
 * Moves the given file to the rmr directory permenantly
 */
void archive(char *filename){
    toLog(concat("Attempting to archive: ", filename));


}


int main(int argc, char **argv){
    verbose = true;
    // Gotting the current working directory
    char buff[PATH_MAX_LENGTH + 1];
    currentDirectory = getcwd(buff, PATH_MAX_LENGTH + 1);
    homeFolder = concat(getenv("HOME"), "/");
    appPath = concat(concat(homeFolder, appFolder), "/");
    if(currentDirectory != NULL){
        toLog(concat("Current working directory set to: ", currentDirectory));
    }else{
        fprintf(stderr, "Could not get current working directory\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the system for rmr if it is not already
    if(! isInitialized())
        initialize();

    int flag;
    if(argc == 1){
        //No arguments supplied
        //Running as silent server

        //Monitor db file, check if a file needs to be perm deleted, sleep
        printf("Server not yet implemented\n");
        //sleep(60);
    }else{
        while((flag = getopt(argc, argv, options)) != -1){
            switch(flag){
                case 'd':   //Delete file in d days
                    printf("Delete is Not yet implemented\n");
                    break;
                case 'a':   //archive to rmrtmp and never delete
                    archive(optarg);
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
    sqlite3_close(db);
    exit(EXIT_SUCCESS);
}
