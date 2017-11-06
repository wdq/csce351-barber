#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "monitor.h"

extern arena monitorArena;
extern int haircutCount;

// ==== sleepingStylistMon ====//
#define DELAY 100000 // adjust this value
#define	CUSTOMER_COUNT	10 //40

void stylistloop() {
	//printf("Barber start\n");
	// add more variables as needed
	int j;
	while(1) {
		salonState();
		if(haircutCount == CUSTOMER_COUNT) {
			printf("All done\n");
			break;
		}
		checkCustomer();
		//printf("Cutting hair\n");
		for(j = 0; j < DELAY; j++) {
			// cut hair
		}
	}
}

void customerloop() {
	//printf("Customer start\n");
	// add more variables as needed
	int j;
	while(1) {
		salonState();
		if(checkStylist()) {
			//printf("Customer exit\n");
			break;
		}
		for(j = 0; j < DELAY; j++) {
			// go shopping
		}
	}
}

int main() {
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

