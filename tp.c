#include "tp.h"
#include <time.h>

// Variables de control
const int CANT_PUESTOS_A = 1, CANT_PUESTOS_B = 2;

// Variables de tiempo
const time_t TPLL, T;

// Acumuladores
const int SPS = 0, STA = 0, NT = 0;

int main(){
    srand(time(NULL));
    time_t tps_a[CANT_PUESTOS_A], tps_b[CANT_PUESTOS_B];
    inicializarArrayTiempos(tps_a,CANT_PUESTOS_A);
    inicializarArrayTiempos(tps_b,CANT_PUESTOS_B);

    printf("%f",generarNroRandom());

    return 0;
}

double generarNroRandom() {
    return (double)rand() / (double)RAND_MAX;
}

void inicializarArrayTiempos(time_t *array, int longitud) {
    for (int i = 0; i < longitud; i++) {
        *array = 0;
        array++;
    }
    return;
}
