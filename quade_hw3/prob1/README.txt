- Team members: William Quade (I did this assignment alone)




- To compile and execute my code type this into this directory:

gcc -pthread -std=c99 sleepingStylistSem.c -o out && ./out




- To test my code:

Look at the output on the screen after the program has executed, here is an example line:

B: waiting room customers count: 5, shopping customers count: 21, completed haircuts count: 6

At the start there is a letter (B or C) to signal where the message is from.
Messages starting with B come from the stylist/barber thread, messages starting with C come from a customer thread.

Then there are three things logged. 

1. Waiting room customer count: is the number of customers waiting in chairs. Ranges from 0-5. 
2. Shopping customer count: is the number of customers who are waiting for a chair (shopping). 
3. Completed haircut count: is the number of customers that have had their hair cut.

Reading the output shows that there is a stream of customers who get into the chairs first.
Once the chairs are full you will see the number of shopping customers increase to a maximum point, and then begin to decrease. 
Throughout the whole program the completed haircut count should increase. 

At the end of execution the last line should show 0 customers in the waiting room, 0 customers shopping, and 40 completed haircuts. 



- Time spent on this code:

I spent somewhere around 2 or 3 hours for this part of the assignment.



- Level of challenge:

3

It took me a little while to find examples on how to use the sem_t and pthread stuff, and where I should print the debug output.
But once I got that figured out it wasn't too difficult. The pseudo-code had all of the structure I needed.
