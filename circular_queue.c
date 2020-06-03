//
// Created by jian on 2020-05-26.
//
#include "circular_queue.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
//initialise the queue

void init_Cir_queue(Cir_queue* _this){
    memset( _this, 0, sizeof(*_this) );
}

// determine if the queue is empty

bool Cir_queue_empty(Cir_queue* _this){
    // test if the queue is empty
    // 0 returns true
    // nonzero false
    if( 0 == _this->count)
        return 0;
}

// determine if the queue is full
bool Cir_queue_full(Cir_queue* _this){
    if(MAX_QUEUE >= _this->count)
        // full when no of elements exceed the max size
        return (_this->count >= MAX_QUEUE);
}
void Cir_queue_push(Cir_queue * _this, unsigned char item){

    if(_this->count < MAX_QUEUE) {
        //set position
        _this->buf[_this->head] = item;
        //advance index
        _this->head = Cir_queue_adv(_this->head, MAX_QUEUE);
        ++_this->count;
    }
}
unsigned int Cir_queue_pop (Cir_queue * _this){
    int item;
    if (_this->count > 0){

        // get frist item element
        item = _this->buf[_this->tail-1];
        // advance the tail
        _this->tail = Cir_queue_adv(_this->tail, MAX_QUEUE);
        //value = 0
        _this->buf[_this->tail-1] =0;
        // reduce the total count
        --_this->count;
    }
    else {
        // the queue is empty
        printf("the queue is empty ");
    }
    return item;
}

void Cir_queue_print(Cir_queue * _this)
{
    for (int i = 0; i < MAX_QUEUE; i++)
        printf("%d ",_this->buf[i]);
    printf("\n");
}

static unsigned int Cir_queue_adv(const unsigned int value, const unsigned int max)
{
    unsigned int index = value + 1;
    if (index >= max)
    {
        index = 0;
    }
    return index;
}