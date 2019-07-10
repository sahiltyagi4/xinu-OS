#include <xinu.h>
#include <prodcons.h>

void consumer(int count) {
	int i=0;
	for(i=1; i<=count; i++) {
		wait(sem2);
		printf("consumed %d \n", n);
		signal(sem1);
	}
}

