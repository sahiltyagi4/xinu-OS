# include <xinu.h>
//# include <future4_1.h>
# include <future.h>

syscall addtoq(pid32 *futureq[], pid32 *proc) {
	 intmask mask;
        mask = disable();
	int i;
	for(i=0; i< 10; i++) {
		if(*futureq[i] != 0 || *futureq[i] != NULL) {
			//do nothing as the array already has a pid at this index
		} else {
			*futureq[i] = *proc;
			break;	
			restore(mask);
			return OK;
		}
	}
	return OK;
}
