#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CHAIRS 5
#define DELAY 100000
#define	CUSTOMER_COUNT	40

// Semaphores to keep track of some dangerous variables.
sem_t mutex;
sem_t stylistSem;
sem_t customersSem;

// Some variables to keep track of how many people are where, used for debugging.
int waiting = 0;
int shopping = 0;
int cut = 0;

// Code the barber thread runs.
void stylist() {
	int j;
	while(1) {

		// Print out debugging info.
		printf("B: waiting room customers count: %i, shopping customers count: %i, completed haircuts count: %i\n", waiting, shopping, cut);		

		// If everybody has had their hair cut, then leave the barber shop.
		if(cut == CUSTOMER_COUNT) {
			printf("All done\n");
			break;
		}		

		// Take in a customer, and cut their hair.
		sem_wait(&customersSem);
		sem_wait(&mutex);
		waiting = waiting - 1;
		sem_post(&stylistSem);
		sem_post(&mutex);

		cut = cut + 1;
		for(j = 0; j < DELAY; j++) {
			// Cut hair, takes some time to do.
		}
	}
}

// Code the customer threads run.
void customer() {
	int hasShopped = 0;
	int j;
	while(1) {

		// If there is a chair available, then take the chair.
		sem_wait(&mutex);
		if(waiting < CHAIRS) {
			waiting = waiting + 1;
			// Print out debugging info.
			printf("C: waiting room customers count: %i, shopping customers count: %i, completed haircuts count: %i\n", waiting, shopping, cut);

			// If you've been shopping and enter the chair, then there is one less shopper.
			if(hasShopped == 1) {
				hasShopped = 0;
				shopping = shopping - 1;
			}
			sem_post(&customersSem);
			sem_post(&mutex);
			sem_wait(&stylistSem);
			break;
		} else {
			// Otherwise go shopping, and keep track of yourself if you are shopping for debugging.
			if(hasShopped == 0) {
				hasShopped = 1;
				shopping = shopping + 1;
			}
			sem_post(&mutex);
			for(j = 0; j < DELAY; j++) {
				// Go shopping, takes some time to do.
			}
		}
	}
}

int main(void) {

	// Initialize the semaphores
	sem_init(&mutex, 0, 1);
	sem_init(&stylistSem, 0, 0);
	sem_init(&customersSem, 0, 0);

	// Create thread variables
	pthread_t stylistThread;
	pthread_t customerThread[CUSTOMER_COUNT];

	// Create threads
	pthread_create(&stylistThread, NULL, (void *)stylist, NULL);
	for(int i = 0; i < CUSTOMER_COUNT; i++) {
		pthread_create(&customerThread[i], NULL, (void *)customer, NULL);
	}

	// Join threads
	for(int i = 0; i < CUSTOMER_COUNT; i++ ) {
		pthread_join(customerThread[i], NULL);
	}	
	pthread_join(stylistThread, NULL);

	// Close when done with threads.
	return 0;
}

