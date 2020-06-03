//
// Created by jian on 2020-05-26.
//

#ifndef PRACTICE_CIRCULAR_QUEUE_CIRCULAR_QUEUE_H
#define PRACTICE_CIRCULAR_QUEUE_CIRCULAR_QUEUE_H
#define MAX_QUEUE 5
#include "stdbool.h"
#include "stdlib.h"
#endif //PRACTICE_CIRCULAR_QUEUE_CIRCULAR_QUEUE_H
typedef struct Cir_queue
{
    unsigned char buf[MAX_QUEUE];
    int head;         // new data is written at this position in the buffer
    int tail;         // data is read from this position in the buffer
    int count;        // total number of elements in the queue <= RBUF_SIZE
} Cir_queue;

// initialise the queue
void init_Cir_queue(Cir_queue* _this);

// determine if the queue is empty
bool Cir_queue_empty(Cir_queue* _this);

// determine if the queue is full
bool Cir_queue_full(Cir_queue* _this);

void Cir_queue_push(Cir_queue * _this, unsigned char item);

//delete
unsigned int Cir_queue_pop(Cir_queue * _this);

// print the contents
void Cir_queue_print(Cir_queue* _this);

static unsigned int Cir_queue_adv(const unsigned int value, const unsigned int max);
