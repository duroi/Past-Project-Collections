// client.c

// IGLI DURO
// COP4600 
// PROGRAMING ASSIGNMENT 2





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>



//Packet struct, will be located in shared memory that both client and server access.
//Client increments send_count and waits for recv_count to match
//Server waits for send_count to change prints 4 characters in the buffer, increments recv_count when finished.
//Buffer contains 4 characters at a time. Multiple iterations needed to print a full message.
typedef struct Packets{
	int recv_count;
	int send_count;
	char buf[4];
} Packet;




//Function to divide message into 4 byte chunks and write it to shared memory.
void divideMessage(char* str, Packet* p) { 

	int size = strlen(str);
	int r;
	int parts;
	int i;
	int j;
	int pos = 0;
	char buf[4];

	//Get amount of packets needed to send full message
	parts = size / 4;
	//Get remained of leftover bytes.
	r = size % 4;
	
	
	//Test print
	//printf("Message can be transferred in %d parts with a remainder of %d\n", parts, r);
	
		//Loop for number of parts needed for full message. Keep track of position in full message.
		for (i = 0; i < parts; i++) {
			//Write 4 characters to buffer
			for (j = 0; j < 4; j++) {
				p->buf[j] = str[pos];
				pos = pos + 1;
			}
			//Test prings
			//printf("%s", buf);
			//printf("%s", p->buf);
			//printf("1");
			
			//Increment send_count and loop until server code increments recv_count and prints characters in buffer.
			p->send_count++;
			while(p->send_count != p->recv_count){
			}
			
			//Test prints
			//printf("%d\n", p->send_count);
			//printf("%s\n", buf);
		}
	//If else branch based on remainder characters, pad with space and \n.	
	if (r == 1) {
		p->buf[0] = str[pos];
		p->buf[1] = ' '; 
		p->buf[2] = ' ';
		p->buf[3] = '\n';
		//printf("2");
		//printf("%s", p->buf);
		//printf("%s\n", buf);		
	}
	else if (r == 2) {
		p->buf[0] = str[pos];
		p->buf[1] = str[pos+1];
		p->buf[2] = ' ';
		p->buf[3] = '\n';
		//printf("3");
		//printf("%s", p->buf);
		//printf("%s\n", buf);
	}
	else if (r == 3) {
		p->buf[0] = str[pos];
		p->buf[1] = str[pos+1];
		p->buf[2] = str[pos+2];
		p->buf[3] = '\n';
		//printf("4");
		//printf("%s", buf);
		//printf("%s\n", buf);
	}
	else {
	}
	//Increment send_send count, server will recognize and print the buffer.
	//Conditional so messages with remainder 0 don't get printed twice.
	if (r != 0) {
		p->send_count++;
		while(p->send_count != p->recv_count){
	
		}	
	}
	
	//Test print
	//printf("%d:%d\n", p->send_count, p->recv_count);
}



int main(int argc, char *argv[])
{


	int channel;
	int shmid;
	char message[1024];
	

	//Validate command line argument, exit if incorrect.
	if (argc == 2) {//check arguments, convert to int
		channel = atoi(argv[1]);
		
		printf("Using shared memory key %d\n", channel); // Test
		
	}
	else if (argc > 2) {//check arguments
		printf("Too many arguments, expected format: './client 200'\n");
		exit(1);
	}	
	
	else { //check arguments
		printf("No arguments inputted, expected format: './client 200'\n");
		exit(1);
	}

	//Get shared memory id.
	//Validate if correct, exit if shmget failed.
	shmid = shmget(channel, sizeof(Packet),  0666);
	if (shmid < 0) {
		printf("shmget error\n");
		exit(1);
	}
	
	//Test print
	//printf("shmid is: %d\n", shmid);

	//Intitilize packet struct
	//Attach pointer to shared memory.
	Packet *p = (Packet*)shmat(shmid, NULL, 0);
	

	while (0 != 1) {//Infinite loop to get input from user
		fgets(message, 1024, stdin);
		divideMessage(message, p);
	}
	
	return 0;
}
