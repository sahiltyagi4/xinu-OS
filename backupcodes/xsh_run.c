# include<xinu.h>
# include <stdlib.h>
# include <future.h>
//# include <future4_1.h>

shellcmd xsh_run(int nargs, char** args) {
	int i_ex=1;
	
	uint future_prod(future* fut,int n) {
		while(1) {
			n = i_ex;
  			printf("Produced %d\n",n);
	  		future_set(fut, (char *)&n);
		}
		return OK;
	}

	uint future_cons(future* fut) {
  		int i_con=0, status;
		while(1) {
  			status = (int)future_get(fut,(char *)&i_con);
	  		if (status < 1) {
    				printf("future_get failed\n");
	    			return -1;
  			}	
  			printf("Consumed %d\n", i_con);
		}
  		return OK;
	}

	future* f_exclusive; //,* f_shared,* f_queue;	
	f_exclusive = future_alloc(FUTURE_EXCLUSIVE, sizeof(int));
	printf("future exclusive is:%d\n", FUTURE_EXCLUSIVE);
  	//f_shared = future_alloc(FUTURE_SHARED, sizeof(int));
	//f_queue = future_alloc(FUTURE_QUEUE, sizeof(int));

	if (nargs == 4 && strncmp(args[2], "-pc", 2) == 0) {
  		resume(create(future_prod, 1024, 20, "fprod1", 2, f_exclusive, i_ex));
		resume(create(future_cons, 1024, 20, "fcons1", 1, f_exclusive));
		for(i_ex=2; i_ex<= atoi(args[3]); i_ex++) {
			printf("i value: %d\n", i_ex);
		}

	}
}
