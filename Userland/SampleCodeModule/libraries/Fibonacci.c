#include <Fibonacci.h>

static uint64_t lastFibo1 = 0;
static uint64_t lastFibo2 = 0;


void start_fibo(){
    lastFibo1=1;
    lastFibo2=0;
}

uint64_t fibo_next(){
    if(lastFibo2 < lastFibo1){
        lastFibo2 += lastFibo1;
        if ( lastFibo2 <= MAX )
            return lastFibo2;
    }
    else{
        lastFibo1 += lastFibo2;
        if ( lastFibo1 <= MAX )
            return lastFibo1;
    }
    return (lastFibo1>lastFibo2)? lastFibo1:lastFibo2;  
}
