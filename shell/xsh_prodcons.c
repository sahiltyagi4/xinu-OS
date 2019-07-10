#include <xinu.h>
#include <prodcons.h>

int n;
sid32 sem1;
sid32 sem2;

shellcmd xsh_prodcons(int nargs, char *args[])
{
	int count = atoi(args[1]);
	sem1 = semcreate(1);
	sem2 = semcreate(0);
	//if(nargs > 0) {
	//	count=args[1];
	//}

	resume(create(producer, 1024, 20, "producer", 3, count, sem1, sem2));
  	resume(create(consumer, 1024, 20, "consumer", 1, count, sem1, sem2));
  	return (0);
}
