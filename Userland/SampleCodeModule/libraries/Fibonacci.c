#include <Fibonacci.h>

static uint64_t lastFibo1 = 0;
static uint64_t lastFibo2 = 0;


void start_fibo(){
    lastFibo1=1;
    lastFibo2=0;
}

uint64_t fibo_next(){
    if(lastFibo2 < lastFibo1){
        if((int64_t)(MAX - lastfibo1 - lastfibo2) >= 0){
            lastFibo2 += lastFibo1;
        }
        return lastFibo2;
    }
    else{
        if((int64_t)(MAX - lastfibo1 - lastfibo2) >= 0){
            lastFibo1 += lastFibo2;
        }
        return lastFibo1;
    }
    return (lastFibo1>lastFibo2)? lastFibo1:lastFibo2;  
}
