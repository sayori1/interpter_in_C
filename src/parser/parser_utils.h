#ifndef PARSER_UTILS_H
#define PARSER_UTILS_H

#include "nodes/node.h"
#include <core/char_utils.h>
#include "nodes/num_node.h"
#include "nodes/expression_node.h"
#include "nodes/compound_statement_node.h"
#include "nodes/symbol_node.h"

char *nodeToString(Node *node)
{
    switch (node->type)
    {
    case NUMBER:
        return charsFormat("NumNode(value: %d)", ((NumNode *)node)->value);
    case BINOP:
        return charsFormat("expressionNode(left: %s, right: %s, op: %s)", nodeToString(((ExpressionNode *)node)->left), nodeToString(((ExpressionNode *)node)->right), lexemToString(((ExpressionNode *)node)->op));
    case COMPOUND:
    {
        CompoundNode *compoundNode = (CompoundNode *)node;
        char *buffer = "";
        for (int i = 0; i < compoundNode->count; i++)
        {
            buffer = charsFormat("%s%s;", buffer, nodeToString((Node *)compoundNode->statements[i]));
        }
        return charsFormat("CompoundNode(statements: %s)", buffer);
    }
    case STATEMENT:
        return charsFormat("StatementNode(child: %s)", nodeToString(((StatementNode *)node)->child));
    case ASSIGN:
    {
        AssignNode *assignNode = (AssignNode *)node;
        return charsFormat("AssignNode(name: %s, expr: %s)", assignNode->name, nodeToString(assignNode->expr));
    }
    case VAR_LITERAL:
        return charsFormat("SymbolNode(name: %s)", ((SymbolNode *)node)->name);
    default:
        return "Unknown";
    }
}

#endif // !PARSER_UTILS
