#include "node.h"
#include <stdlib.h>

#ifndef NUM_NODE_H
#define NUM_NODE_H

typedef struct{
    Node base;
    int value;
} NumNode;

NumNode* numNodeCreate(int value){
    NumNode* self = (NumNode*)malloc(sizeof(NumNode));
    self->base.type = NUMBER;
    self->value = value;

    return self;
}

#endif