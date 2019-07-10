# include<xinu.h>
# include <stdlib.h>
# include <future.h>
//# include <future4_1.h>

shellcmd xsh_run(int nargs, char** args) {

	uint future_prod_exclusive(future* fut, int n) {
		int status;
  		printf("Produced %d\n",n);
	  	status = (int)future_set(fut, &n);
		printf("status after future set is %d\n", status);
		/*if(isempty(fut->getqueueshared)) {
			printf("the get shared queue is EMPTY!!!\n");
		} else {
			printf("GET Q not EMPTY\n");
			printf("first id of queue:%d and current pid is%d and last id %d\n", firstid(fut->getqueueshared), currpid, lastid(fut->getqueueshared));
			//enqueue(currpid, fut->getqueueshared);
			printf("size of getsharedqueue is %d\n", sizeof(fut->getqueueshared));
			printf("new first id after enqueue %d and last id %d\n", firstid(fut->getqueueshared), lastid(fut->getqueueshared));
		}*/
		return OK;
	}

	uint future_cons_exclusive(future* fut) {
  		int i_con, status;
  		//status = (int)future_get(fut,(char *)&i_con);
  		status = (int)future_get(fut, &i_con);
	  	if (status < 1) {
    			printf("future_get failed\n");
	    		return -1;
  		}	
  		printf("Consumed %d\n", i_con);
  		return OK;
	}

	uint future_prod_shared(future* fut, int n){
                int status;
                if(fut->state == FUTURE_EMPTY) {
			status = (int)future_set(fut, &n);
               		printf("Shared produced %d\n", n);
			fut->state = FUTURE_FULL;
			return OK;
		} else {
			printf("going to return ERROR since a value has already been set on the future\n");
			return SYSERR;
		}
        }

        uint future_cons_shared(future* fut) { 
		if(fut->state != FUTURE_FULL) {
			//add procid to queue
			int i;
			for(i=0; i<10; i++) {
				if(fut->getqueue[i] != 0 || fut->getqueue[i] != NULL) {
					fut->getqueue[i] = currpid;
					break;
				}
			}

		} else if(fut->state == FUTURE_FULL) {
			int i_con, status;
			status = (int)future_get(fut, &i_con);
                	if (status < 1) {
                        	printf("future_get failed\n");
                        	return -1;
                	}
                	printf("consumed shared %d\n", i_con);
                	return OK;
		}
        }
	
	uint future_prod_queue(future* fut, int n) {
		int status;
		pid32 proc;
		printf("going to run fut_prod_queue\n");
		if(fut->getsharedq[0] != 0 && fut->getsharedq[0] != NULL) {
			//status = (int)future_set(fut, &n);
			removefromq(&fut->getsharedq, &proc);
			resume(proc);
			status = (int)future_set(fut, &n);
			printf("shared produced value %d\n", n);
		} else {
			printf("added to shared queue in prod_queue\n");
			addtoq(&fut->setsharedq, currpid);
		}
	}

	uint future_cons_queue(future* fut) {
		int status;
		pid32 proc;
		int i_shared;
		printf("going to run fut_cons_queue\n");
		if(fut->setsharedq[0] != 0 && fut->setsharedq[0] != NULL) {
			removefromq(&fut->setsharedq, &proc);
			resume(proc);
			status = (int)future_get(fut, &i_shared);
			printf("shared consumed value %d\n", i_shared);
		} else {
			printf("added to shared queue in cons_queue\n");
			addtoq(&fut->getsharedq, currpid);
		}
	}

	future *f_exclusive=NULL;
	f_exclusive = future_alloc(FUTURE_EXCLUSIVE, sizeof(int));
	printf("future exclusive is:%d\n", FUTURE_EXCLUSIVE);

	future *f_shared=NULL;
	printf("going to run future alloc\n");
	f_shared = future_alloc(FUTURE_SHARED, sizeof(int));
	printf("future shared is %d\n", FUTURE_SHARED);
	
	future *f_queue=NULL;
	f_queue = future_alloc(FUTURE_QUEUE, sizeof(int));
	printf("future queue is %d\n", FUTURE_QUEUE);
	printf("pid32 size:%d\n", sizeof(pid32));

	if (nargs == 4 && strncmp(args[2], "-pc", 2) == 0) {
		printf("in -pc exclusive condition\n");
		//future exclusive mode
  		//resume(create(future_prod_exclusive, 1024, 20, "fprod1", 2, f_exclusive, atoi(args[3])));
		//resume(create(future_cons_exclusive, 1024, 20, "fcons1", 1, f_exclusive));
		
		//future shared mode
		//resume(create(future_prod_shared, 1024, 20, "fprod1", 2, f_shared, atoi(args[3])));
		//resume(create(future_prod_shared, 1024, 20, "fprod2", 2, f_shared, atoi(args[3])));
		//resume(create(future_cons_shared, 1024, 20, "fcons1", 1, f_shared));
		//resume(create(future_cons_shared, 1024, 20, "fcons2", 1, f_shared));
		
		//future queue mode
		resume(create(future_prod_queue, 1024, 20, "prod1", 2, f_queue, 2));
		//resume(create(future_prod_queue, 1024, 20, "prod2", 2, f_queue, 4));
		resume(create(future_cons_queue, 1024, 20, "cons1", 1, f_queue));
		//resume(create(future_cons_queue, 1024, 20, "cons2", 1, f_queue));
	}
}
