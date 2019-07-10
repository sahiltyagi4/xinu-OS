#ifndef _FUTURE_H_
#define _FUTURE_H_

    /* modes of operation for future*/
    #define FUTURE_EXCLUSIVE  1	
    #define FUTURE_SHARED     2	    
    #define FUTURE_QUEUE      3     
 
    /* define states */
    #define FUTURE_FREE   0x00
    #define FUTURE_EMPTY  0x01
    #define FUTURE_FULL   0x03
    #define FUTURE_WAITING  0x05     

typedef struct futent
{
  uint16 state;
  uint16 flags;
  uint32 size;
  int value;
  pid32 pid;
  pid32 getqueue[1];
  pid32 getsharedq[1];
  pid32 setsharedq[1];
  /*pid32 getqueue;
  pid32 getsharedq;
  pid32 setsharedq;*/
} future;

syscall addtoq(pid32 *futq[], pid32 *proc); 
syscall removefromq(pid32 *futq[], pid32 *proc);
future* future_alloc(int future_flags, uint size);
syscall future_free(future*);
syscall future_get(future*, int *);
syscall future_set(future*, int *);
#endif /* _FUTURE_H_ */
