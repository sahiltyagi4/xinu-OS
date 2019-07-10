# include<xinu.h>
# include <stdlib.h>
# include <future.h>
//# include <future4_1.h>

shellcmd xsh_run(int nargs, char** args) {
	uint future_prod(future* fut,int n) {
		//n = i_ex;
		int status;
  		printf("Produced %d\n",n);
	  	status = (int)future_set(fut, (char *)&n);
		printf("status after future set is %d\n", status);
		return OK;
	}

	uint future_cons(future* fut) {
  		int i_con, status;
  		status = (int)future_get(fut,(char *)&i_con);
	  	if (status < 1) {
    			printf("future_get failed\n");
	    		return -1;
  		}	
  		printf("Consumed %d\n", i_con);
  		return OK;
	}

	future *f_exclusive=NULL;	
	f_exclusive = future_alloc(FUTURE_EXCLUSIVE, sizeof(int));
	printf("future exclusive is:%d\n", FUTURE_EXCLUSIVE);

	if (nargs == 4 && strncmp(args[2], "-pc", 2) == 0) {
		printf("in -pc exclusive condition\n");
  		resume(create(future_prod, 1024, 20, "fprod1", 2, f_exclusive, atoi(args[3])));
		resume(create(future_cons, 1024, 20, "fcons1", 1, f_exclusive));
		/*for(i_ex=2; i_ex<= atoi(args[3]); i_ex++) {
			printf("i value: %d\n", i_ex);
		}*/

	}
}
