#include <Utils.h>

static uint64_t lastPrimo;

/*void StartPrimos(){
    //imprimo numeros primos hasta que me paren
    int pr=2;
    lastPrimo=pr;
    putDec(pr);
    print("\n");
    pr++;
    while(stopPr!=1){
        if (esprimo(pr)){
            putDec(pr);
            print("\n");
            lastPrimo=pr;
        }
        pr++;
    }

}
*/

int es_primo(int n){
    int cantdediv = 0;
    for(int i=1; i<n+1; i++){
        if (n%i==0){
            cantdediv++;
        }
    }
    if (cantdediv==2){
        return 1;
    }
    return 0;
    
}


void start_prime(){
    lastPrimo=1;
}

int primo_next(){
    if (lastPrimo==1){
        lastPrimo++;
        return lastPrimo;
    }
    
    lastPrimo++;
    while ( !es_primo(lastPrimo) ){
        lastPrimo++;
    }
    return lastPrimo;
}