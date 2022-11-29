// problem2.c

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
    
    
    //Get commands from user, ex: "ls | wc"
    
    char str1[50];
    char str2[50];
    printf("Enter desired commands. \nExample Format (ls | wc): ");
    scanf("%s | %s", str1, str2);
    
   // printf("%s\n%s\n", str1, str2);
   
    //printf("Calling fork1()...\n");
   
    
    int fd[2];
    
    //Create pipe
    //printf("Creating pipe()...\n"
    pipe(fd);
    
    	
    int rc = fork();
    if (rc < 0) {
        // fork failed
        exit(1);
    } else if (rc == 0) {
       
        
        // Call exec
    	//printf("Calling exec1()...\n");    	
    	close(fd[0]);
    	
    	dup2(fd[1], STDOUT_FILENO);
    	
    	execlp(str1, str1, (char*) NULL);
    		
    } else {
    
    }
    
    
    //printf("Calling fork2()...\n");
    int rc2 = fork();
    
    if (rc2 < 0) {
        // fork failed
        exit(1);
    } else if (rc2 == 0) {


        
        // Call exec
    	//printf("Calling exec2()...\n");    	
    	close(fd[1]);
    	
    	dup2(fd[0], STDIN_FILENO);
    
    	execlp(str2, str2, (char*) NULL);
    	

    } else {

    
    }
    //Closing pipe
    //printf("Closing pipe...\n");
    close(fd[0]);
    close(fd[1]);
        
    wait(NULL);
    wait(NULL);
  
    printf("++++\n");
    
    
    return 0;

}
