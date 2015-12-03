#include <stdio.h>

/*declare a buffer for user input of size 2048 */

static char input[2048];

int main(int argc, char** argv){
    puts("Lispy Version: 0.0.0.0.1");
    puts("Press Ctrl+c to Exit \n");

    while(1){
        fputs("Lispy> ", stdout);
        fgets(input, 2048, stdin); /* fget reads any inputs up until a new line, including the newline character*/
        printf("No you are a %s", input);
    }

    return 0;
}
