#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CHAIRS 5
#define DELAY 100000
#define	CUSTOMER_COUNT	5

sem_t mutex;
sem_t stylistSem;
sem_t customersSem;

//semaphore mutex = 1, stylist = 0 customers = 0;
int waiting = 0;

void stylist() {
	printf("I'm a stylist and I don't do anything yet\n");
	/*int j;
	while(1) {
		down(&customers);
		down(&mutex);
		waiting = waiting - 1;
		up($stylist);
		up(&mutex);

		for(j = 0; j < DELAY; j++) {
			// cut hair
		}
	}*/
}

void customer() {
	printf("I'm a customer and I don't do anything yet\n");
	/*int j;
	while(1) {
		down(&mutex);
		if(waiting < CHAIRS) {
			waiting = waiting + 1;
			up(&customers);
			up(&mutex);
			down(&stylist);
			break;
		} else {
			up(&mutex);

			for(j = 0; j < DELAY; j++) {
				// Go shopping
			}
		}
	}*/
}

int main(void) {
	// Create 40 customer threads and 1 stylist thread
	// Don't forget to join threads
	pthread_t stylistThread;
	pthread_t customerThread[CUSTOMER_COUNT];

	// Create threads
	pthread_create(&stylistThread, NULL, (void *)stylist, NULL);

	for(int i = 0; i < CUSTOMER_COUNT; i++) {
		pthread_create(&customerThread[i], NULL, (void *)customer, NULL);
	}


	// Join threads
	pthread_join(stylistThread, NULL);

	for(int i = 0; i < CUSTOMER_COUNT; i++ ) {
		pthread_join(customerThread[i], NULL);
	}

	return 0;


}

