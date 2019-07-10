# include <xinu.h>
# include <prodcons.h>
# include <tscdf-input1.h>

void stream_proc(int32 num_streams) {
	struct streamqueue q;
	int32 j=0;

	q.stream_id = 33;
	q.arr.ts = 100;
	q.arr.val = 200;
	for(j=0; j<num_streams; j++) {
		q.sem1 = semcreate(1);
		q.sem2 = semcreate(0);
		resume(create(consume_streamqueue, 1024, 20, "consumer_queue_"+j, 1, &q));	 
	}
	
		printf(": %d, %d, %d\n", q.stream_id,  q.arr.ts,  q.arr.val);
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
		signal((*q).sem1);
	}
}
