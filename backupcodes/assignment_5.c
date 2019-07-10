# include<xinu.h>
# include <stdlib.h>
# include <future.h>
# include <prodcons.h>
# include <tscdf-input1.h>

	extern struct tscdf *td1=NULL;
	extern int num_streams=0;
       	extern int work_queue=0;
        extern int time_window=0;
        extern int output_time=0;
        extern int32 out_ctr=0;
        extern int32* cdfarr=NULL;

shellcmd xsh_run(int nargs, char** args) {
	//assignment 3 goes here
	printf("no. of args:%d\n",nargs);

        char usage[] = "Usage: -s num_streams -w work_queue -t time_window -o output_time\n";
        int n = 0;
        for (n=1; n<nargs; n+=2) {
                char *w = (char *)args[n];
                if(*w == 's') {
                        num_streams = atoi(args[n+1]);
                } else if(*w == 'o') {
                        output_time = atoi(args[n+1]);
                } else if(*w == 't') {
                        time_window = atoi(args[n+1]);
                } else if(*w == 'w') {
                        work_queue = atoi(args[n+1]);
                }
        }

        printf("# streams:%d, output_time:%d, time_window:%d, work_queue:%d\n", num_streams, output_time, time_window, work_queue);
	 
	td1 = tscdf_init(time_window);

        struct streamqueue q;
        int32 j=0;

        for(j=0; j<num_streams; j++) {
                q.sem1 = semcreate(1);
                q.sem2 = semcreate(0);
		stream_proc_future(&q.fstream);
                resume(create(consume_streamqueue, 1024, 20, "consumer_queue_"+j, 1, &q));
        }

        int32 i=0; int32 streamId=0;
        for(i=0; i<(sizeof(stream_input)/sizeof(stream_input[0])); i++) {
                char *a = (char *)stream_input[i];
                streamId = atoi(a);
                wait(q.sem1);
                q.stream_id = streamId;
                while (*a++ != '\t');
                        q.arr.ts = atoi(a);
                while (*a++ != '\t');
                        q.arr.val = atoi(a);

                printf("producer: %d, %d, %d\n", q.stream_id,  q.arr.ts,  q.arr.val);
		future_set(q.fstream, &q.arr.val);
		printf("set future value in xsh_run %d\n", q.arr.val);
                signal(q.sem2);
        }

        wait(q.sem2);
        wait(q.sem2);
	
}

void consume_streamqueue(struct streamqueue *q) {
        bool b = TRUE;
        while(b) {
                wait((*q).sem2);
                out_ctr++;
                printf("consume %d stream with ts %d and value %d\n", (*q).stream_id, (*q).arr.ts, (*q).arr.val);
		
		int* future_val;
		future_get((*q).fstream, &future_val);
		printf("future get value in xsh_run is %d\n", future_val);

                tscdf_update(td1, (*q).arr.ts, (*q).arr.val);

                if(out_ctr % output_time ==0) {

                        printf("out_ctr is:%d\n", out_ctr);
                        cdfarr = tscdf_quartiles(td1);
                        if(cdfarr == NULL) {
                                kprintf("tscdf_quartiles returned NULL\n");
                        }

                        int i=0;
                        for(i=0; i < 5; i++) {
                                kprintf("%d ", cdfarr[i]);
                        }
                        kprintf("\n");

                        freemem((char *)cdfarr, (6*sizeof(int32)));
                        out_ctr=0;
                }

                signal((*q).sem1);
        }
}

/*void stream_proc_future(future** farray) {
	int i;
	printf("work_queue value in stream_proc_future: %d\n", work_queue);
	for(i=0; i<work_queue; i++) {
		future *f_exclusive=NULL;
		f_exclusive = future_alloc(FUTURE_EXCLUSIVE, sizeof(int));
		*farray[i] = *f_exclusive;
		printf("future exclusive is:%d\n", FUTURE_EXCLUSIVE);	
	}
}*/

void stream_proc_future(future* fut) {
        printf("work_queue value in stream_proc_future: %d\n", work_queue);
	fut = future_alloc(FUTURE_EXCLUSIVE, sizeof(int));
	printf("future exclusive is:%d\n", FUTURE_EXCLUSIVE);
}
