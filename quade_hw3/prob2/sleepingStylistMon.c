#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "monitor.h"

#define DELAY 100000 // adjust this value
#define	CUSTOMER_COUNT	40

// Keep track of the arena and number of haircuts from the other file.
extern arena monitorArena;
extern int haircutCount;

// This function runs in the stylist thread.
// It continually prints the salon state, checks for customers in the monitor, and cuts hair when possible.
// It quits once the number of haircuts reaches the maximum so the baber won't fall into a coma.
void stylistloop() {
	int j;
	while(1) {
		salonState();
		if(haircutCount == CUSTOMER_COUNT) {
			printf("All done\n");
			break;
		}
		checkCustomer();
		for(j = 0; j < DELAY; j++) {
			// cut hair
		}
	}
}

// This function runs in the customer thread.
// It continually prints the salon state, checks for an available seat, and goes shopping when there isn't one.
// It quits once it gets a haircut since that's all they want.
void customerloop() {
	int j;
	while(1) {
		salonState();
		if(checkStylist()) {
			break;
		}
		for(j = 0; j < DELAY; j++) {
			// go shopping
		}
	}
}

// This function initializes the haircut counter, and monitor, and then starts the threads.
int main() {
	// Initialize monitor and haircut counter.
	haircutCount = 0;
	monInit();

	// Create thread variables
	pthread_t stylistThread;
	pthread_t customerThread[CUSTOMER_COUNT];

	// Create threads
	pthread_create(&stylistThread, NULL, (void *)stylistloop, NULL);
	for(int i = 0; i < CUSTOMER_COUNT; i++) {
		pthread_create(&customerThread[i], NULL, (void *)customerloop, NULL);
	}

	// Join threads
	for(int i = 0; i < CUSTOMER_COUNT; i++ ) {
		pthread_join(customerThread[i], NULL);
	}	
	pthread_join(stylistThread, NULL);

	// Close when done with threads.
	return 0;
}

