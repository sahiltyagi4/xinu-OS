# include <xinu.h>
//# include <future4_1.h>
# include <future.h>

syscall future_set(future* f, char* value) {
        intmask mask;
        mask = disable();
	f->value=value;
	printf("value to be set is: %d\n",value);
	printf("set future val %d\n",f->value);
        restore(mask);
        return OK;
}
