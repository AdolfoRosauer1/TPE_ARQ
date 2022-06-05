#include <Utils.h>
#include <stdbool.h>

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

bool esprimo(int n){
    int cantdediv = 0;
    for(int i=1; i<n+1; i++){
        if (n%i==0){
            cantdediv++;
        }
    }
    if (cantdediv==2){
        return true;
    }
    return false;
    
}


void resetPrimo(){
    lastPrimo=1;
}

int Primonext(){
    if (lastPrimo==1){
        lastPrimo++;
        return lastPrimo;
    }
    
    lastPrimo++;
    while (esprimo(lastPrimo)==false){
        lastPrimo++;
    }
    return lastPrimo;
}