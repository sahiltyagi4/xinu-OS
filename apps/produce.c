#include <xinu.h>
#include <prodcons.h>

void producer(int count) {
	int i=0;
	for(i=1; i<=count; i++) {
		wait(sem1);
		n=i;
		printf("value produced is %d \n", n);
		signal(sem2);
	}
}



