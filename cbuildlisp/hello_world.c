#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} point;


void testfor(){
    for(int i=0;i<5;i++){
        puts("hello, World!");
    }
}

void testwhile(){
    int i = 0;
    while(i < 5){
        puts("Hello, world!");
        i++;
    }
}

void excercise3(int n){
    for(int i = n ; i > 0; i--){
        puts("hello from exercise 3");
    }
}

void exercise8(){
    int i = 0;
    do{
        puts("Hello from exercise 8");
    } while( i > 0);
}

void tryswitch(int i){
    switch(i){
    case 1:
        puts("case 1");
        break; // the break is a must
    case 2:
        puts("case 2");
        break;
    default :
        puts("it is an unknown case");
    }
}

void trycontinue(int i){
    for(int n = i; n > 0; n--){
        if(n%2 == 0){
            continue;
        }
        printf("%d\n",n);
    }
}

void trypoint(float i, float j){
    point p;
    p.x = i;
    p.y = j;
    float length = sqrt(p.x * p.x + p.y * p.y);
    printf("%f\n",length);
}

int main(int argc, char** argv) {
    testfor();
    testwhile();
    excercise3(7);
    exercise8();
    tryswitch(2);
    tryswitch(1);
    tryswitch(3);
    trycontinue(9);
    trypoint(3.0,4.0);
    return 0;
}


