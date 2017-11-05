// ==== monitor ==== //

#define CHAIRS 5
cond stylistAvailable, customerAvailable;
int customer = 0;
int stylist = 0;

// add more variables as necessary (e.g. a semaphore for entry queue)

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

int main() {
	// Create 40 customer threads and a stylist thread
	// don't forget to join threads
	return 0;
}

void salonState() { // print how many customers are waiting
	// print the state of the waiting chair using the following
	// format: first used chair: last used chair: count\n.
}

void stylist() {
	// add more variables as needed
	int j;
	while(1) {
		salonState();
		checkCustomer();
		for(j = 0; j < DELAY; j++) {
			// cut hair
		}
	}
}

void customer() {
	// add more variables as needed
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

