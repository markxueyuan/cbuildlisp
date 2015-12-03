#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>
#include <editline/history.h>

int main(int argc, char** argv){
    puts("Lispy Version 0.0.0.0.1");
    puts("Press Ctrl+c to Exit");

    while(1){
        char* input = readline("Lispy> ");
        add_history(input);
        printf("No you are a %s\n", input); /* readline function strips the newline character, so we add one in printf */
        free(input); /*  unlike fgets, which writes to some existing buffer,
                        the readline function allocates new memory when it is called */
    }
    return 0;
}
