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

    typedef struct futent
    {
        uint16 state;
        uint16 flags;
        uint32 size;
        char *value; /* alloc must memget size (in chars) space */
        pid32 pid; /* for single waiter case */
        queue set_queue;     
        queue get_queue;

    } future;
 ...
#endif /* _FUTURE_H_ */
