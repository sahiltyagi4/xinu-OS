# include<xinu.h>
//# include <prodcons.h>
# include <stdlib.h>
# include <future.h>

shellcmd xsh_run(int nargs, char** args) {

	/*
	printf("no. of args:%d\n",nargs);	
	char usage[] = "Usage: -s num_streams -w work_queue -t time_window -o output_time\n";
	int num_streams=0;
	int work_queue=0;
	i nt time_window=0;
	int output_time=0;	
	if (!(nargs % 2)) {
  		printf("%s", usage);
  		return(-1);
	}

	resume(create(stream_proc,1024, 20, "stream_processes", 4, nargs, args));
	return (0);*/
	
	int ring_count=0;
	int value_ring=0;

	uint future_ring(future *in, future *out) {
                //int val=ring_count;
                future_get(in, (char *)&value_ring);
                printf("Process %d gets %d, puts %d\n", getpid(), value_ring, value_ring-1);
                value_ring--;
                future_free(in);
                future_set(out, (char *)&value_ring);
                return OK;
        }
		  
		int i;
		int ring=0;
 		int future_flags=0;

		#ifndef NFUTURE
		  printf("no support for futures (NFUTURES not defined.)\n");
		  return OK;
		#endif
			
		  printf("# of args %d\n", nargs);	
		  if (nargs == 4 && strncmp(args[2], "-r", 2) == 0) {
		    ring = 1;
		    ring_count = atoi(args[3]);
		    printf("ring count value is: %d\n", ring_count);
		    value_ring=ring_count;
		    printf("Producer/consumer process ring\n");
		  }
		  else {
		    printf("No valid options\n");
		    return(OK);		  
		  }

		  if (ring == 1) {
    			future *first, *in, *out = NULL;
			first = future_alloc(future_flags, sizeof(int));
			in = first;
		    	for (i=0; i < ring_count; i++) {
      				out = future_alloc(future_flags, sizeof(int));
	      			resume( create(future_ring, 1024, 20, "", 2, in, out) );
	      			in = out;
    			}
		    	printf("master sets %d\n", ring_count);
		    	future_set(first, (char *)&ring_count);
		    	future_get(out, (char *)&value_ring);
			printf("master gets %d\n", value_ring);
	    		return(OK);
  		}
  		return(OK);
	}
