# include <xinu.h>
//# include <future4_1.h>
# include <future.h>

syscall future_free(future* f) {
        intmask mask;
	mask=disable();
	freemem(f, sizeof(f));
	restore(mask);
}
