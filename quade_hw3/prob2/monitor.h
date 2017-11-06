#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct cond cond;

typedef struct arena arena;

int haircutCount;

void monInit();

int count(cond cv);

void wait(cond cv);

void signal(cond cv);

void salonState();

void checkCustomer();

int checkStylist();