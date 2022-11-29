// client.c

// IGLI DURO
// COP4600 
// PROGRAMING ASSIGNMENT 3





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#include <pthread.h>
#include "shared_mem.h"

//Global define shared_mem
struct shm_data* shared_mem;

//put function, write messages to c2s buffer
void* put(void* arg){

	char message[MAX_MSG_LEN];
	int i = 0;
	while(1 == 1) {
		
		//lock critical section
		pthread_mutex_lock(&shared_mem->c2s.mutex);


		//printf("PUT: %d : %d\n", shared_mem->c2s.tail, shared_mem->c2s.front);
		
		//put thread to sleep if condition is true, wait for full signal from server
		while((shared_mem->c2s.tail > shared_mem->c2s.front)){
			pthread_cond_wait(&shared_mem->c2s.full, &shared_mem->c2s.mutex);
		}
		//get input
		fgets(message, 1024, stdin);

		//for(i = 0; i < strlen(message); i++){ 
		//	shared_mem->c2s.messages[shared_mem->c2s.tail % NUMBER_OF_MSG][i] = message[i];
		//
		//}
		
		//write input to c2s buffer
		memcpy(shared_mem->c2s.messages[shared_mem->c2s.tail % NUMBER_OF_MSG], message, strlen(message)+1);
		//increase tail
		shared_mem->c2s.tail++;

		//signal empty conditional variable
		pthread_cond_signal(&shared_mem->c2s.empty);
		//unlock critical section
		pthread_mutex_unlock(&shared_mem->c2s.mutex);
	}
	return NULL;
}

//get function, read messages from s2c buffer
void* get(void* arg){

	char message[MAX_MSG_LEN];
	int i = 0;
	while(1 == 1) {
	
		//lock critical section
		pthread_mutex_lock(&shared_mem->s2c.mutex);
		//printf("GET: %d : %d\n", shared_mem->s2c.tail, shared_mem->s2c.front);
		
		//put thread to sleep if condition is true, wait for empty signal from server	
		while(shared_mem->s2c.front == shared_mem->s2c.tail){
			pthread_cond_wait(&shared_mem->s2c.empty, &shared_mem->s2c.mutex );
		}
		
		//read input from s2c buffer
		for(i = 0; i < strlen(shared_mem->s2c.messages[shared_mem->s2c.front % NUMBER_OF_MSG]); i++){
			printf("%c", shared_mem->s2c.messages[shared_mem->s2c.front % NUMBER_OF_MSG][i]);
		}
		//increase front
		shared_mem->s2c.front++;
		//signal full condition variable
		pthread_cond_signal(&shared_mem->s2c.full);
		
		pthread_mutex_unlock(&shared_mem->s2c.mutex);
	}
	return NULL;
}

int main(int argc, char *argv[])
{

	int channel;
	int shmid;
	

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
	shmid = shmget(channel, sizeof(struct shm_data),  0666);
	if (shmid < 0) {
		printf("shmget error\n");
		exit(1);
	}
	
	//Test print
	//printf("shmid is: %d\n", shmid);

	//Intitilize shm_data struct
	//Attach pointer to shared memory.
	shared_mem = (struct shm_data*)shmat(shmid, NULL, 0);
	
	//define threads
	pthread_t thread_1;
	pthread_t thread_2;
	
	
	//create threads, starting at put() and get()
	pthread_create(&thread_1, NULL, put, &shared_mem);
	pthread_create(&thread_2, NULL, get, &shared_mem);
	
	
	//wait for threads to join
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);

	
	return 0;
}
