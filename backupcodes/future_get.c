# include <xinu.h>
//# include <future4_1.h>
# include <future.h>

syscall future_get(future* f, char* value) {
	intmask mask;
	mask = disable();
	value=f->value;
	printf("inside future get method...\n");
	printf("future get value is: %d\n", value);
	restore(mask);
	return OK;
}
