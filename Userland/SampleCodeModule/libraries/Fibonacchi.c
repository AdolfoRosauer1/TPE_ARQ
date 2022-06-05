#include <Utils.h>

static uint64_t lastFibo1;
static uint64_t lastFibo2;
uint64_t stopFb = 0;

/*void Fibonacchi(){
    // haria serie de fibo hasta que se lo pare
    int num1=0, num2=1,lastFibo1=1,lastFibo2=0;
    while(1){
        putDec(num2);
        print("\n");
        num1 += num2;
        lastFibo2=num1;
        putdec(num2);
        print("\n");
        num2 += num1;
        lastFibo1=num2;
    }
}

void stopFibo(){
    stopFb = 1;
}
*/

void StartFibo(){
    lastFibo1=1;
    lastFibo2=0;
}

uint64_t Fibonext(){
    if(lastFibo2 < lastFibo1){
        lastFibo2 += lastFibo1;
        return lastFibo2;
    }
    else if (lastFibo1 <= lastFibo2){
        lastFibo1 += lastFibo2;
        return lastFibo1;
    }  
}
