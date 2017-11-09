#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CHAIRS 5

// A condition variable defined with:
//	1. Number of threads that are blocked on the CV.
//	2. A mutex semaphore to keep prevent concurrency issues within the CV.
//	3. A maximum running threads number. Used to know if it's a CV for the barber (1 barber) or the customer (5 chairs).
typedef struct cond cond;
struct cond {
	int blockedThreadsCount;
	sem_t mutex;
	int maxThreads;
};

// I defined an arena variable like the one mentioned in the old homework1 on Dr. Witty's website.
// This is an easy way to work with the monitor's mutex, CV's, and the customer/stylist counters.
typedef struct arena arena;
struct arena {
	sem_t mutex;
	cond stylistAvailable;
	cond customerAvailable;
	int customer;
	int stylist;
};

// Define the arena, and a haircut counter.
arena monitorArena;
int haircutCount;


// This initializes the monitor's arena variable with the appropriate values.
// Specifically the mutexes are all set to 1, and the counters all start at zero.
void monInit() {
	// Stylist CV
	cond stylistAvailableCond;
	sem_init(&stylistAvailableCond.mutex, 0, 1);
	stylistAvailableCond.blockedThreadsCount = 0;
	stylistAvailableCond.maxThreads = 1;

	// Customer CV
	cond customerAvailableCond;
	customerAvailableCond.blockedThreadsCount = 0;
	customerAvailableCond.maxThreads = CHAIRS;
	sem_init(&customerAvailableCond.mutex, 0, 1);

	// Arena
	sem_init(&monitorArena.mutex, 0, 1);
	monitorArena.stylistAvailable = stylistAvailableCond;
	monitorArena.customerAvailable = customerAvailableCond;
	monitorArena.customer = 0;
	monitorArena.stylist = 0;
}


// Returns the number of threads blocked on the CV
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

// Prints the number of completed haircuts, the number of customers that are in the chairs,
// 		and how many barbers are available.
// Since this function is part of the monitor it uses the arena mutex to only allow one thread in at a time.
void salonState() { 
	sem_wait(&monitorArena.mutex);
	printf("haircuts: %i, customer: %i, stylist: %i\n", haircutCount, monitorArena.customer, monitorArena.stylist);
	sem_post(&monitorArena.mutex);
}

// Called from stylistLoop
// Since this function is part of the monitor it uses the arena mutex to only allow one thread in at a time.
// It signals the stylist as available, then checks for a customer.
// If no customer it just waits for a customer signal, otherwise it takes in the customer and cuts their hair.
void checkCustomer() {
	sem_wait(&monitorArena.mutex);
	monitorArena.stylist = 1;

	signal(monitorArena.stylistAvailable); // stylist's ready to cut hair

	if(monitorArena.customer == 0) { // do not use while here
		wait(monitorArena.customerAvailable); // If there aren't customers, then wait/sleep.
	}

	if(monitorArena.customer != 0) { // This condition prevents some weirdness.
		monitorArena.customer = monitorArena.customer - 1;
		haircutCount = haircutCount + 1;
	}
	sem_post(&monitorArena.mutex);
}

// Called from customerLoop
// Since this function is part of the monitor it uses the arena mutex to only allow one thread in at a time.
// It uses an entry queue (the number of customers less than the number of chairs).
// If the customer can make it through the queue they are added to a chair.
// 		Then they signal that they are available. If a stylist is also available they get a haircut.
//		If no stylist is available then they wait for a stylist signal.
// If the customer can't make it through the queue, they leave and come back later.
// Status = 1 means that they got a haircut.
// Status = 0 means that they didn't get a haircut.
int checkStylist() {
	// This function may have faults.
	// If you think it does, you'll need to fix it.
	sem_wait(&monitorArena.mutex);
	int status = 0;
	if(monitorArena.customer < CHAIRS) {

		monitorArena.customer = monitorArena.customer + 1;


		signal(monitorArena.customerAvailable);
		if(monitorArena.stylist == 0) { // do not use while here
			wait(monitorArena.stylistAvailable);
		}
		monitorArena.stylist = 0;
		status = 1;
	}
	sem_post(&monitorArena.mutex);
	return status;
}