
#ifndef NODE_H
#define NODE_H

typedef enum {
    NUMBER,
    BINOP,
    VAR_LITERAL,
    COMPOUND,
    STATEMENT,
    ASSIGN
} NodeType;

typedef struct{
    NodeType type;
} Node;


#endif // !NODE_H
