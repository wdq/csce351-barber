#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// ==== monitor ==== //

typedef struct cond cond;
struct cond {
	int blockedThreadsCount;
	sem_t mutex;
	int maxThreads;
};

typedef struct arena arena;
struct arena {
	sem_t mutex;
	cond stylistAvailable;
	cond customerAvailable;
	int customer;
	int stylist;
};

arena monitorArena;
int haircutCount;


#define CHAIRS 5

// add more variables as necessary (e.g. a semaphore for entry queue)

void monInit() {

	cond stylistAvailableCond;
	sem_init(&stylistAvailableCond.mutex, 0, 1);
	stylistAvailableCond.blockedThreadsCount = 0;
	stylistAvailableCond.maxThreads = 1;
	cond customerAvailableCond;
	customerAvailableCond.blockedThreadsCount = 0;
	customerAvailableCond.maxThreads = 5;
	sem_init(&customerAvailableCond.mutex, 0, 1);

	sem_init(&monitorArena.mutex, 0, 1);

	monitorArena.stylistAvailable = stylistAvailableCond;
	monitorArena.customerAvailable = customerAvailableCond;
	monitorArena.customer = 0;
	monitorArena.stylist = 0;
}


// Returns the number of threads blocked on the cv
int count(cond cv) {
	return cv.blockedThreadsCount;
}

// Relinquishes exclusive access to the monitor and then suspends the executing threads
void wait(cond cv) {
	sem_wait(&cv.mutex);
	cv.blockedThreadsCount = cv.blockedThreadsCount + 1;
	sem_post(&cv.mutex);
	while(1) {
		sem_wait(&cv.mutex);
		int cvcount = count(cv);
		if(cvcount <= cv.maxThreads) {
			sem_post(&cv.mutex);
			break;
		}
		sem_post(&cv.mutex);
	}

}

// Unblocks one thread suspended at the head of the cv blocking queue.
// The signaled thread resumes execution where it was last suspended.
// The signaler exits the monitor and suspends itself at the entry queue. 
void signal(cond cv) {
	sem_wait(&cv.mutex);
	cv.blockedThreadsCount = cv.blockedThreadsCount - 1;
	sem_post(&cv.mutex);

}

void salonState() { // print how many customers are waiting
	// print the state of the waiting chair using the following
	// format: first used chair: last used chair: count\n.
	printf("haircuts: %i, customer: %i, stylist: %i, blockedCustomer: %i, blockedStylist: %i\n", haircutCount, monitorArena.customer, monitorArena.stylist, count(monitorArena.customerAvailable), count(monitorArena.stylistAvailable));
}

// Called from stylistLoop
void checkCustomer() {
	sem_wait(&monitorArena.customerAvailable.mutex);
	sem_wait(&monitorArena.stylistAvailable.mutex);
	monitorArena.stylist = 1;
	sem_post(&monitorArena.customerAvailable.mutex);
	sem_post(&monitorArena.stylistAvailable.mutex);

	signal(monitorArena.stylistAvailable); // stylist's ready to cut hair

	if(monitorArena.customer == 0) { // do not use while here
		wait(monitorArena.customerAvailable); // If there aren't customers, then wait/sleep.
	}

	sem_wait(&monitorArena.customerAvailable.mutex);
	sem_wait(&monitorArena.stylistAvailable.mutex);
	monitorArena.customer = monitorArena.customer - 1;
	haircutCount = haircutCount + 1;
	sem_post(&monitorArena.customerAvailable.mutex);
	sem_post(&monitorArena.stylistAvailable.mutex);
}

// Called from customerLoop
int checkStylist() {
	// This function may have faults.
	// If you think it does, you'll need to fix it.
	int status = 0;
	if(monitorArena.customer < CHAIRS) {

		sem_wait(&monitorArena.customerAvailable.mutex);
		sem_wait(&monitorArena.stylistAvailable.mutex);
		monitorArena.customer = monitorArena.customer + 1;
		sem_post(&monitorArena.customerAvailable.mutex);
		sem_post(&monitorArena.stylistAvailable.mutex);


		signal(monitorArena.customerAvailable);
		if(monitorArena.stylist == 0) { // do not use while here
			wait(monitorArena.stylistAvailable);
		}
		sem_wait(&monitorArena.customerAvailable.mutex);
		sem_wait(&monitorArena.stylistAvailable.mutex);
		monitorArena.stylist = 0;
		sem_post(&monitorArena.customerAvailable.mutex);
		sem_post(&monitorArena.stylistAvailable.mutex);
		status = 1;
	}
	return status;
}