#include <Fibonacci.h>

static uint64_t lastFibo1 = 0;
static uint64_t lastFibo2 = 0;


void start_fibo(){
    lastFibo1=1;
    lastFibo2=0;
}

uint64_t fibo_next(){
    if(lastFibo2 < lastFibo1){
        if((MAX - lastFibo1) >= lastFibo2){
            lastFibo2 += lastFibo1;
        }
        else
            return (lastFibo1>lastFibo2)? lastFibo1:lastFibo2;
        return lastFibo2;
    }
    else{
        if((MAX - lastFibo2) >= lastFibo1){
            lastFibo1 += lastFibo2;
        }
        else
            return (lastFibo1>lastFibo2)? lastFibo1:lastFibo2;
        return lastFibo1;
    }
    return (lastFibo1>lastFibo2)? lastFibo1:lastFibo2;  
}
