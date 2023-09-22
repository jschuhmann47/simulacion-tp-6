#include "tp.h"
#include <time.h>

// Variables de control
const int CANT_PUESTOS_A = 1, CANT_PUESTOS_B = 2;

// Variables de tiempo
time_t tpll, t;

// Acumuladores
int SPS = 0, STA = 0, NT = 0;

int main(){
    srand(time(NULL));
    time_t tps_a[CANT_PUESTOS_A], tps_b[CANT_PUESTOS_B];
    inicializarArrayTiempos(tps_a,CANT_PUESTOS_A);
    inicializarArrayTiempos(tps_b,CANT_PUESTOS_B);

    time_t menor_tps_a = buscarMenorTiempo(tps_a, CANT_PUESTOS_A);
    time_t menor_tps_b = buscarMenorTiempo(tps_b, CANT_PUESTOS_B);

    if(tiempoEsMenorOIgual(menor_tps_a,menor_tps_b)){
        if(tiempoEsMenor(menor_tps_a, tpll)){
            // salida por A
        }
        else {
            // llegada
        }
    }
    else {
        if(tiempoEsMenor(menor_tps_b, tpll)){
            // salida por B
        }
        else {
            // llegada
        }
    }

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

time_t buscarMenorTiempo(time_t *array, int longitud) {
    time_t min = *array;
    for (int i = 1; i < longitud; i++) {
        if (*array < min){
            min = *array;
        }
        array++;
    }
    return min;
}

int tiempoEsMenorOIgual(time_t tiempo, time_t tiempo_a_comparar) {
    return difftime(tiempo, tiempo_a_comparar) <= 0;
}

int tiempoEsMenor(time_t tiempo, time_t tiempo_a_comparar) {
    return difftime(tiempo, tiempo_a_comparar) < 0;
}

