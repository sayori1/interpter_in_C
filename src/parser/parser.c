#include "parser.h"
#include "nodes/assingment_node.h"

Parser *parserCreate(Lexer *lexer)
{
    Parser *parser = (Parser *)malloc(sizeof(Parser));
    parser->lexer = lexer;
    return parser;
}

Node *parseLiteral(Parser *self)
{
    Lexem *lexem = self->lexer->currentLexem;

    switch (lexem->type)
    {
    case NUM:
        eatToken(self->lexer, NUM);
        return (Node *)numNodeCreate((int)lexem->value);
    case PARB:
        eatToken(self->lexer, PARB);
        Node *expr = parsePlusMinus(self);
        eatToken(self->lexer, PARE);
        return expr;
    case ID:
        eatToken(self->lexer, ID);
        return (Node *)symbolNodeCreate((char *)lexem->value);
    default:
        return NULL; // Handle error appropriately in production code
    }
}

Node *parseMulDiv(Parser *self)
{
    Node *left = parseLiteral(self);
    Lexem *lexem = self->lexer->currentLexem;

    while (lexem->type == OPERATOR && ((char)lexem->value == '*' || (char)lexem->value == '/'))
    {
        char op = (char)lexem->value;
        eatToken(self->lexer, OPERATOR);
        Node *right = parseLiteral(self);

        if (op == '*')
        {
            left = (Node *)binOpNodeCreate(left, right, lexem);
        }
        else if (op == '/')
        {
            left = (Node *)binOpNodeCreate(left, right, lexem);
        }

        lexem = self->lexer->currentLexem;
    }

    return left;
}

Node *parsePlusMinus(Parser *self)
{
    Node *left = parseMulDiv(self);
    Lexem *lexem = self->lexer->currentLexem;

    while (lexem->type == OPERATOR && ((char)lexem->value == '+' || (char)lexem->value == '-'))
    {
        char op = (char)lexem->value;
        eatToken(self->lexer, OPERATOR);
        Node *right = parseMulDiv(self);

        if (op == '+')
        {
            left = (Node *)binOpNodeCreate(left, right, lexem);
        }
        else if (op == '-')
        {
            left = (Node *)binOpNodeCreate(left, right, lexem);
        }

        lexem = self->lexer->currentLexem;
    }

    return left;
}

Node *parseStatement(Parser *self)
{
    Node *node = NULL;
    if (self->lexer->currentLexem->type == VAR)
    {
        node = parseAssign(self);
    }
    eatToken(self->lexer, STATEMEND_END);

    return (Node *)statementNodeCreate(node);
}

Node *parseCompoundStatement(Parser *self)
{
    eatToken(self->lexer, COMB);
    CompoundNode *compoundNode = compoundNodeCreate();

    while (self->lexer->currentLexem->type != COME)
    {
        StatementNode *statement = (StatementNode *)parseStatement(self);
        compoundNodeAddStatement(compoundNode, statement);
    }

    eatToken(self->lexer, COME);
    return (Node *)compoundNode;
}

Node *parse(Parser *self)
{
    return parseCompoundStatement(self);
}

Node *parseAssign(Parser *self)
{
    eatToken(self->lexer, VAR);
    Lexem *varName = eatToken(self->lexer, ID);
    eatToken(self->lexer, OPERATOR);
    Node *expr = parsePlusMinus(self);

    return (Node *)assignNodeCreate((char *)varName->value, expr);
}

char *nodeToString(Node *node)
{
    switch (node->type)
    {
    case NUMBER:
        return charsFormat("NumNode(value: %d)", ((NumNode *)node)->value);
    case BINOP:
        return charsFormat("BinOpNode(left: %s, right: %s, op: %s)", nodeToString(((BinOpNode *)node)->left), nodeToString(((BinOpNode *)node)->right), lexemToString(((BinOpNode *)node)->op));
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
