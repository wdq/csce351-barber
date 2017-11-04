#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define CHAIRS 5
#define DELAY 100000
semaphore mutex = 1, stylist = 0 customers = 0;
int waiting = 0;

void main(void) {
	// Create 40 customer threads and 1 stylist thread
	// Don't forget to join threads
}

void stylist(void) {
	int j;
	while(1) {
		down(&customers);
		down(&mutex);
		waiting = waiting - 1;
		up($stylist);
		up(&mutex);

		for(j = 0; j < DELAY; j++) {
			// cut hair
		}
	}
}

void customer(void) {
	int j;
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
	}
}