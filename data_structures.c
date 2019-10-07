#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"


IntNode* put_inode(IntNode* p ,unsigned int value){
    IntNode* new_pointer;
    if ((new_pointer = (IntNode *) malloc(sizeof(IntNode)))){
        new_pointer->value = value;
        new_pointer->next = p;
        ///printf("Ponteiro antes p :%p\n",p);
        ///printf("Ponteiro depois p :%p\n",p);
        ///printf("O que eu estou botando %u %p \n",new_pointer->value, new_pointer);
        return new_pointer;
    }
    exit(1);

}

WeightedN* put_inode(WeightedN* p ,unsigned int value,unsigned weight){
    WeightedN* new_pointer;
    if ((new_pointer = (WeightedN *) malloc(sizeof(WeightedN)))){
        new_pointer->value = value;
        new_pointer->next = p;
        new_pointer->weight = weight;
        ///printf("Ponteiro antes p :%p\n",p);
        ///printf("Ponteiro depois p :%p\n",p);
        ///printf("O que eu estou botando %u %p \n",new_pointer->value, new_pointer);
        return new_pointer;
    }
    exit(1);

}

IntNode queue_pop(Queue* q){
    IntNode* p_v;
    IntNode vertice;
    p_v = q->top;
    q->top = p_v->next;
    vertice = *(p_v);
    free(p_v);
    return (vertice);
}


void queue_push(Queue* q, unsigned index){
    
    IntNode* last = q->rear;
    IntNode* new_pointer;
    if ((new_pointer = (IntNode *) malloc(sizeof(IntNode)))){
        if(q->top){
            new_pointer->value = index;
            new_pointer->next = NULL;
            last->next = new_pointer;
            q->rear = new_pointer;
        }else {
            new_pointer->value =index;
            new_pointer->next = NULL;
            q->rear = new_pointer;
            q->top = new_pointer;
        }
        //return new_pointer;
    }else
    {
        printf("Fatal error Out of memory");
        exit(1);
    }
}

IntNode stack_pop(Stack* stack){
    IntNode* v_p;
    IntNode v;
    v_p = stack->top;
    stack->top = v_p->next;
    v = *(v_p);
    free(v_p);
    return v;
}

void stack_push(Stack* stack, IntNode v){
    IntNode* top = stack->top;
    IntNode* new_pointer;
    if ((new_pointer = (IntNode *) malloc(sizeof(IntNode)))){
        new_pointer->value = v.value;
        new_pointer->next = top;
        stack->top = new_pointer;
    }
    else
    {
        printf("Fatal error Out of memory");
        exit(1);
    }
}


void initialize_PQ(PriorityQueue* pq,unsigned v_number){
    HeapNode* heap;
    unsigned* position_array;
    if((heap = (HeapNode * )malloc(sizeof(HeapNode) * v_number)) && 
    (position_array = (unsigned* )malloc(sizeof(unsigned) * v_number))){
        pq->last_element = (v_number-1);
        pq->heap = heap;
        pq->position_array = position_array;
        for(unsigned i=0; i<v_number;i++){
            (heap[i]).key = (~(0x0));
            (heap[i]).value = i;
            position_array[i] = i;
        }
    }else{
        printf("Error: Out of Memory \n");
        exit(1);
    }
}

void swap(unsigned a, unsigned b, PriorityQueue* pq){
    HeapNode* heap = (pq->heap);
    unsigned* position_array = (pq->position_array);

    unsigned value_a = (heap[a]).value;
    unsigned value_b = (heap[b]).value;

    HeapNode temp_node = heap[a];
    heap[a] = heap[b];
    heap[b] = temp_node;

    unsigned temp = position_array[value_a];
    position_array[value_a]= position_array[value_b];
    position_array[value_b] = temp;

}

HeapNode extract_min(PriorityQueue* pq){
    HeapNode* heap = pq->heap;
    unsigned* position_array = pq->position_array;
    swap(0,pq->last_element,pq);
    HeapNode min = heap[(pq->last_element)--];
    unsigned heap_postion = 0;
    unsigned son_position = (((heap[1]).key< (heap[2]).key ) || (pq->last_element ==1)) ?  1 : 2;
    unsigned temp,left_son,right_son;

    while (( ( pq->last_element) >=((heap_postion<<1)+1) ) 
    && ( (heap[heap_postion].key) > (heap[son_position].key)))
    {
        swap(heap_postion,son_position, pq);
        heap_postion = son_position;
        left_son = ((heap_postion<<1)+1); 
        right_son= ((left_son+1) > (pq->last_element)) ? (left_son) : (left_son+1);
        son_position =  ( (heap[left_son].key) <= (heap[right_son].key) ) ? left_son : right_son ;

    }
    return min;

}

void decrease_key(PriorityQueue* pq,unsigned vertex, unsigned key){
    HeapNode* heap = (pq->heap);
    unsigned heap_postion = (pq->position_array)[vertex];
    unsigned parent_position =  (heap_postion & 1) ? ((heap_postion-1)/2) : (heap_postion/2 -1);
    (heap[heap_postion]).key = key; 

    while((heap_postion) && ((heap[heap_postion]).key) < ((heap[parent_position]).key)){
        swap(heap_postion,parent_position,pq);
        heap_postion = parent_position;
        parent_position =  (heap_postion & 1)?((heap_postion-1)/2):(heap_postion/2 -1);
    }
    
}