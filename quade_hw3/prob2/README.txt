

- Team members: William Quade (I did this assignment alone)




- To compile and execute my code type this into this directory:

gcc -o out monitor.c sleepingStylistMon.c -pthread -std=c99 && ./out



- To test my code:

Look at the output on the screen after the program has executed, here is an example line:

haircuts: 30, customer: 4, stylist: 1

At the start is the number of completed haircuts. 
Then there is a counter that specifies how many customers are currently sitting in chairs.
At the end is a bit that specifies if the stylist is available to give a haircut (1) or not (0).

Reading the output shows that there is a stream of customers who get into the chairs first.
The stylist will go between 1 and 0 and the haircut count should increase to the maximum.
At the end the number of customers in chairs will go down 5, 4, 3, 2, 1, 0, and the haircuts will go 35, 36, 37, 38, 39, 40.

At the end of execution the last line should show 0 customers in chairs, an available barber, and 40 completed haircuts. 



- Time spent on this code:

I spent somewhere around 6 to 8 hours for this part of the assignment.



- Level of challenge:

5

This one was trickier, and even though the output seems to be correct, I'm still not 100% sure the code is a correctly implemented monitor.

Debugging this was a pain because when the code isn't correct the output is kind of unpredictable. 
Somtimes it may output everything correctly, other times it wouldn't. 
Figuring out what a monitor was, and what a condition variable were, and how to initialize them, was hard to figure out.