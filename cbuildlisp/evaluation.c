#include "mpc.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32

#include <string.h>

static char buffer[2048];

/* fake readline function */
char* readline(char* prompt){
    fputs(prompt, stdout);
    fgets(buffer, 2048, stdin);
    char* cpy = malloc(strlen(buffer)+1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return cpy;
}

/* fake add_history function */
void add_history(char* unused){}

#else
#include <editline/readline.h>
#include <editline/history.h>
#endif // _WIN32

int number_of_nodes(mpc_ast_t* t){
    if(t->children_num == 0){
        return 1;
    }
    if(t->children_num >= 1) {
        int total = 1;
        for(int i = 0; i < t->children_num; i++){
            total += number_of_nodes(t->children[i]);
        }
        return total;
    }
}

long eval_op(long x, char* op, long y){
    if(strcmp(op, "+") == 0){
        return x + y;
    }
    if (strcmp(op, "-") == 0){
        return x - y;
    }
    if (strcmp(op, "*") == 0){
        return x * y;
    }
    if (strcmp (op, "/") == 0){
        return x / y;
    }
    return 0;
}


long eval(mpc_ast_t* t){

    /* if tagged as number, returned immediately */
    if(strstr(t->tag, "number")){
        return atoi(t->contents);
    }

    /* the second child will always be <operator> */
    char* op = t->children[1]->contents;

    /* store the third child in `x' */
    long x = eval(t->children[2]);

    /* iterate the remaining children and combining */
    int i = 3;
    while(strstr(t->children[i]->tag, "expr")){
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }
    return x;
}



int main(int argc, char** argv){

    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lispy = mpc_new("lispy");

mpca_lang(MPCA_LANG_DEFAULT,
    "                                                           \
        number      : /-?[0-9]+/ ;                              \
        operator    : '+' | '-' | '*' | '/' | '%' | \"add\" | \"sub\" | \"mul\" | \"div\" ; \
        expr        : <number> | '(' <operator> <expr>+ ')' ;   \
        lispy       : /^/ <operator> <expr>+ /$/ ;              \
    ",
    Number, Operator, Expr, Lispy);

    puts("Lispy Version 0.0.0.0.2");
    puts("Press Ctrl+c to Exit\n");

    while(1){

        char* input = readline("Lispy> ");
        add_history(input);

        mpc_result_t r;

        if(mpc_parse("<stdin>", input, Lispy, &r)){

            mpc_ast_t* a = r.output;
            printf("Number of Nodes: %d\n", number_of_nodes(a));
            printf("Tag: %s\n", a->tag);
            printf("Contents: %s\n", a->contents);
            printf("Number of children %i\n", a->children_num);

            puts("\n");

            mpc_ast_t* c0 = a->children[0];
            printf("Tag of First Child: %s\n", c0->tag);
            printf("Contents of First Child: %s\n", c0->contents);
            printf("Number of Children of First Child: %i\n", c0->children_num);

            mpc_ast_print(a);

            long result = eval(a);
            printf("%li\n", result);
            mpc_ast_delete(a);
        } else{
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    mpc_cleanup(4, Number, Operator, Expr, Lispy);

    return 0;
}
