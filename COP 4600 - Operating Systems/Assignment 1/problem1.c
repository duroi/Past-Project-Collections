// problem1.c

// IGLI DURO
// COP4600 
// PROGRAMING ASSIGNMENT 1





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    
    //Get commands from user, ex: "ls -a -l"
    
    char str[50];
    printf("Enter desired commands. \nExample (ls -a -l): ");
    scanf("%[^\n]*c", str);
    
    //printf("%s\n", str);
    
    // Split inputs. Size of params is arbitrary. 
    char* params[20];
    char* token = strtok(str," ");
 
    int i = 0;
    while (token != NULL) 
    {
        //printf("i = %d\n", i);
        params[i] = token;
        //printf(" %s\n", params[i]);
        token = strtok(NULL, " ");
        i++;
    }
    
    //Set index after input to NULL.
    params[i] = NULL;
     
    //printf("Calling fork()...\n");
   

    int rc = fork();
    
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr,"fork failed\n");
        exit(1);
    } else if (rc == 0) {

        // Call exec
        //printf("Calling exec()...\n");        
        execvp(params[0], params);
    } else {

        int wc = wait(NULL);
    
    }

  
    printf("++++\n");
    
    
    
    return 0;

}
