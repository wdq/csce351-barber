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
		mon.checkCustomer();
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
		if(mon.checkStylist()) {
			break;
		}
		for(j = 0; j < DELAY; j++) {
			// go shopping
		}
	}
}

// ==== monitor ==== //
