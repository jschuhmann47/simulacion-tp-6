#include "tp.h"

// Variables de control
const int CANT_PUESTOS_A = 1, CANT_PUESTOS_B = 2;

// Variables de tiempo
const time_t TPLL, TPSA, TPSB, T;

// Acumuladores
const int SPS = 0, STA = 0, NT = 0;

int main(){
    srand(time(NULL));


    printf("%f",generarNroRandom());

    return 0;
}

double generarNroRandom() {
    return (double)rand() / (double)RAND_MAX ;
}