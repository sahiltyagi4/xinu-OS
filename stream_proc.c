# include <xinu.h>
# include <prodcons.h>
# include <clock.h>
# include <tscdf-input1.h>

struct tsvalues {
	int value, tstamp;
};

/**void stream_proc(int numproc) {
 	sid32 mutex = semcreate(1); 
	int i=0;
	int initval=51;
	for(i=0; i<numproc; i++) {
		//create numproc processes here with stream_id as 'i'
		//use stream_id, timestamp/value queue as argument to spawn_proc functions which creates these individual processes
		initval += 4;
		p.value = initval;
		p.tstamp = clktime;
		printf("the value param for tsvalues is %d \n", initval);
		printf("going to create process with id %d \n", i);
		resume(create(spawned_proc, 1024, 20, "consumerproc", 3, i, p));
	}
}

void spawned_proc(int stream_id, struct tsvalues tsval) {
	printf("for process %d the values are %d and %d \n", stream_id, tsval.tstamp, tsval.value);	
}**/

void stream_proc(int num_streams) {
	int i=0;
	sem1 = semcreate(1);
	sem2 = semcreate(0);

	//add produce_stream fxn logic here
	struct tsvalues p[num_streams];

	 for(i=0; i<num_streams; i++) {
                resume(create(produce_stream, 1024, 20, "producer", 2, i, p[i]));
                resume(create(consume_stream, 1024, 20, "consumer", 2, i, p[i]));
        }

	int st=0;
	for(i=0; i<(sizeof(stream_input)/sizeof(stream_input[0])); i++) {
		char *a = (char *)stream_input[i];
		st = atoi(a);
                while (*a++ != '\t');
			p[st].tstamp = atoi(a);
		while (*a++ != '\t');
			p[st].value = atoi(a);
	}
	return (0);
}

void produce_stream(int stream_id, struct tsvalues p) {
	int i=0;
	for(i=0; i<100; i++) {
		wait(sem1);		
		printf("producer: %d %d %d\n", stream_id, p.tstamp, p.value);
		signal(sem2);
	}
	return (0);
}

void consume_stream(int stream_id, struct tsvalues p) {
	int i=0;
        for(i=0; i<100; i++) {
		wait(sem2);
		printf("in consumer with VALUE %d %d\n", p.value, p.tstamp);
		signal(sem1);
	}
	return (0);
} 	
