#include <stdio.h>
#include "circular_queue.h"


int main(){

    Cir_queue buffer ;
    init_Cir_queue(&buffer);
    Cir_queue_push(&buffer,1);
    Cir_queue_push(&buffer,2);
    Cir_queue_push(&buffer,3);
    Cir_queue_push(&buffer,4);
    Cir_queue_push(&buffer,5);
    Cir_queue_pop(&buffer);
    Cir_queue_pop(&buffer);
    Cir_queue_push(&buffer,7);
    Cir_queue_push(&buffer,8);
    Cir_queue_print(&buffer);
    return 0;
}

