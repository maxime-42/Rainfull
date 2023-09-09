#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define _GNU_SOURCE
#define _GNU_SOURCE

int main(int argc, char *argv[]) {
    int inputInt;          // To store the converted integer from the command-line argument
    char *shellPath;       // To store the path of the shell ("/bin/sh")
    __uid_t effectiveGID;  // To store the effective group ID
    __uid_t effectiveUID;  // To store the effective user ID

    // Convert the command-line argument to an integer
    inputInt = atoi(argv[1]);

    // Check if the input integer is equal to 423 (0x1a7 in hexadecimal)
    if (inputInt == 0x1a7) {
        // Set up the shell path
        shellPath = strdup("/bin/sh");
        
        // Get the effective group ID and effective user ID
        effectiveGID = getegid();
        effectiveUID = geteuid();
        
        // Change the effective group ID and user ID to the real group ID and user ID
        setresgid(effectiveGID, effectiveGID, effectiveGID);
        setresuid(effectiveUID, effectiveUID, effectiveUID);
        
        // Replace the current process with a new process running the shell
        execv("/bin/sh", &shellPath);
    }
    else {
        // If the input integer is not 423, print "No !" to stderr
        fwrite("No !\n", 1, 5, stderr);
    }
    
    return 0;
}
