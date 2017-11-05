#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// ==== monitor ==== //

typedef struct cond cond;
struct cond {
	int blockedThreadsCount;
	sem_t suspendSem;
};

#define CHAIRS 5
cond stylistAvailable;
cond customerAvailable;
int customer = 0;
int stylist = 0;

// add more variables as necessary (e.g. a semaphore for entry queue)

// Returns the number of threads blocked on the cv
void count(cond cv) {

}

// Relinquishes exclusive access to the monitor and then suspends the executing threads
void wait(cond cv) {

}

// Unblocks one thread suspended at the head of the cv blocking queue.
// The signaled thread resumes execution where it was last suspended.
// The signaler exits the monitor and suspends itself at the entry queue. 
void signal(cond cv) {

}

void checkCustomer() {
	stylist = stylist + 1;
	signal(stylistAvailable); // stylist's ready to cut hair
	if(customer == 0) { // do not use while here
		wait(customerAvailable);
	}
	customer = customer - 1;
}

int checkStylist() {
	// This function may have faults.
	// If you think it does, you'll need to fix it.
	int status = 0;
	if(customer < CHAIRS) {
		customer = customer + 1;
		signal(customerAvailable);
		if(stylist == 0) { // do not use while here
			wait(stylistAvailable);
		}
		stylist = stylist - 1;
		status = 1;
	}
	return status;
}



// ==== sleepingStylistMon ====//
#define DELAY 100000 // adjust this value
#define	CUSTOMER_COUNT	40

void stylistloop() {
	printf("Barber start\n");
	// add more variables as needed
	/*int j;
	while(1) {
		salonState();
		checkCustomer();
		for(j = 0; j < DELAY; j++) {
			// cut hair
		}
	}*/
}

void customerloop() {
	printf("Customer start\n");
	// add more variables as needed
	/*int j;
	while(1) {
		salonState();
		if(checkStylist()) {
			break;
		}
		for(j = 0; j < DELAY; j++) {
			// go shopping
		}
	}*/
}

int main() {
	// Initialize the semaphores
	//sem_init(&mutex, 0, 1);
	//sem_init(&stylistSem, 0, 0);
	//sem_init(&customersSem, 0, 0);

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

void salonState() { // print how many customers are waiting
	// print the state of the waiting chair using the following
	// format: first used chair: last used chair: count\n.
}

