# include <xinu.h>
# include <prodcons.h>
# include <tscdf-input1.h>

void stream_proc(int32 num_streams) {
	//struct streamqueue q[num_streams];
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
	
		printf("data11: %d, %d, %d\n", q.stream_id,  q.arr.ts,  q.arr.val);
	int32 i=0; int32 streamId=0;
	for(i=0; i<(sizeof(stream_input)/sizeof(stream_input[0])); i++) {
		char *a = (char *)stream_input[i];
		streamId = atoi(a);
		wait(q.sem1);
		//q[streamId].stream_id = streamId;
		q.stream_id = streamId;
		while (*a++ != '\t');
			//q[streamId].arr[0].ts = atoi(a);
			q.arr.ts = atoi(a);
		while (*a++ != '\t');
			//q[streamId].arr[0].val = atoi(a);
			q.arr.val = atoi(a);
		
		//printf("data: %d, %d, %d\n", q[streamId].stream_id,  q[streamId].arr[0].ts,  q[streamId].arr[0].val);
		printf("data: %d, %d, %d\n", q.stream_id,  q.arr.ts,  q.arr.val);
		signal(q.sem2);
	}
	
	wait(q.sem2);	
	wait(q.sem2);	
	printf("data333: %d, %d, %d\n", q.stream_id,  q.arr.ts,  q.arr.val);
	//printf("pushing producer: %d %d %d\n", q[0].stream_id, q[0].arr[0].ts, q[0].arr[0].val);
	//resume(create(consume_streamqueue, 1024, 20, "consumer_queue_"+i, 3, q[streamId]));
	//return(0);
}

void consume_streamqueue(struct streamqueue *q) {
	bool b = TRUE;
	printf("WWWWWWW\n");
	while(b) {
	//int k=0;
	//for(k=0; k< 150; k++) {
		wait((*q).sem2);
		printf("consume %d stream with ts %d and value %d\n", (*q).stream_id, (*q).arr.ts, (*q).arr.val);
		signal((*q).sem1);
	}
	//return (0);
}
