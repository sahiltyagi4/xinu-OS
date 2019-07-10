# include <xinu.h>
# include <prodcons.h>
# include <tscdf-input1.h>
# include <tscdf.h>

extern int num_streams=0;
extern int work_queue=0;
extern int time_window=0;
extern int output_time=0;

//extern struct tscdf *td1;

void stream_proc(int nargs, char** args) {

	printf("no. of args:%d\n",nargs);
        char usage[] = "Usage: -s num_streams -w work_queue -t time_window -o output_time\n";
        /*int num_streams=0;
        int work_queue=0;
        int time_window=0;
        int output_time=0;*/

	int n = 0;
	for (n=1; n<nargs; n+=2) {
		//printf("read arguments are: %d and %s\n", n, args[n]);
		char *w = (char *)args[n];
		//printf("w value:%s qwerty\n", w);
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

	//struct tscdf *td2 = tscdf_init(time_window);	
	//td1 = &td2;
	
	struct streamqueue q;
	int32 j=0;

	for(j=0; j<num_streams; j++) {
		q.sem1 = semcreate(1);
		q.sem2 = semcreate(0);
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
		signal(q.sem2);
	}
	
	wait(q.sem2);	
	wait(q.sem2);
}

void consume_streamqueue(struct streamqueue *q) {
	bool b = TRUE;
	while(b) {
		wait((*q).sem2);
		printf("consume %d stream with ts %d and value %d\n", (*q).stream_id, (*q).arr.ts, (*q).arr.val);
	
		//tscdf_update(td1, (*q).arr.ts, (*q).arr.val);

		signal((*q).sem1);
	}
}
