#include "core/array.h";
#include "core/map.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "interpreter/interpreter.h"

void main(){
    Lexer* lexer = lexerCreate("{var a = 10; var b = 20; var c = a + b;}");
    Parser* parser = parserCreate(lexer);
    Node* node = parse(parser);

    Interpreter* interpreter = interpreterCreate();
    visit(interpreter, node);

    for(int i = 0; i < interpreter->variables->pairs->size; i++){
        Pair* pair = (Pair*)arrayGet(interpreter->variables->pairs, i);
        printf("%s = %d\n", (char*)pair->key, (int)pair->value);
    }

    printf("%s\n", nodeToString(node));
    
}