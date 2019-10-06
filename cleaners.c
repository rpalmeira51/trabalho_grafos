#include "cleaners.h"
#include <stdio.h>

void free_list(IntNode** list, unsigned v_number){
    IntNode* p;
    IntNode* pointer;
    IntNode** size = list+v_number;
    for(unsigned i =0 ;i<v_number;i++){
        pointer = list[i];
        while((pointer)!=NULL){
            p = pointer->next;
            free(pointer);
            pointer = p;
        }
    }
    free(list);

}

void free_matrix(char** matrix, unsigned v_number){
    char** p;
    char **size = matrix + v_number;
    for ( p = matrix; p < size; p++)
    {
        free(*p);
    }
    free(matrix);
}