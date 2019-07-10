# include <xinu.h>
//# include <future4_1.h>
# include <future.h>

future* future_alloc(int future_flags, uint size) {
	intmask mask;
	mask = disable();

	future* f=NULL;
	f->flags=future_flags;
	f->size=size;
	f->value=atoi(getmem(size));
	f->state=FUTURE_EMPTY;
	f->pid = currpid;
	/**f->getsharedq=getmem(sizeof(pid32)*NPROC);
	*f->setsharedq=getmem(sizeof(pid32)*NPROC);
	*f->getqueue=getmem(sizeof(pid32)*NPROC);*/
	restore(mask);
	return f;
}
