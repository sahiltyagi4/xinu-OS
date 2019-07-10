# include <xinu.h>
# include <future.h>

syscall removefromq(pid32 *futureq[], pid32 *proc) {
	intmask mask;
        mask = disable();
	if(*futureq[0] !=0 || *futureq[0] != NULL) {
		*proc = *futureq[0];
	}
	
	//re-adjust the array by shifting the indices of the rest processes in the array
	pid32 adjustedarr[10];
	int i;
	for(i=0; i<10; i++) {
		if(*futureq[i] != 0 || *futureq[i] != NULL) {
			adjustedarr[i] = *futureq[i];
		}
	}

	*futureq = NULL;
	*futureq = adjustedarr;
	restore(mask);
	return OK;
}
