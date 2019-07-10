/*Global variable for producer consumer*/
# include <future.h>
extern int n; /*this is just declaration*/

extern sid32 sem1;
extern sid32 sem2;

//extern struct tsvalues {int32 tstamp; int32 value};

//extern struct tsvalues tsval;

extern struct tsvals {
        int32 ts;
        int32 val;
};

extern struct streamqueue {
        int stream_id;
        struct tsvals arr;
        sid32 sem1;
        sid32 sem2;
	//future* farray[10];
	future* fstream;
};

void consume_streamqueue(struct streamqueue *p);

/*function Prototype*/
void consumer(int count);
void producer(int count);
//void stream_proc(int numproc);
void stream_proc(int* nargs, char** args);
void spawned_proc(int stream_id, struct tsvalues tsval);
void produce_stream(int stream_id, struct tsvalues p);
void consume_stream(int stream_id, struct tsvalues p);
