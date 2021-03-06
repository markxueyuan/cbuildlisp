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

int main(int argc, char** argv){
    puts("Lispy Version 0.0.0.0.1");
    puts("Press Ctrl+c to Exit\n");

    while(1){
        char* input = readline("Lispy> ");
        add_history(input);
        printf("No you are a %s\n", input);
        free(input);
    }

    return 0;
}
