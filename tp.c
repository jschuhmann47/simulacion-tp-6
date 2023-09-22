#include "tp.h"
#include <time.h>

// Variables de control
const int N = 1, M = 2;

// Variables de tiempo
time_t tpll, t;
time_t tps_a[N], tps_b[M];

// Acumuladores
int SPS = 0, STA = 0, NT = 0;

int main(){
    srand(time(NULL));
    
    inicializarArrayTiempos(tps_a,N);
    inicializarArrayTiempos(tps_b,M);

    time_t menor_tps_a = buscarMenorTiempo(tps_a, N);
    time_t menor_tps_b = buscarMenorTiempo(tps_b, M);

    if(tiempoEsMenorOIgual(menor_tps_a,menor_tps_b)){
        if(tiempoEsMenor(menor_tps_a, tpll)){
            salida_por_a();
        }
        else {
            llegada();
        }
    }
    else {
        if(tiempoEsMenor(menor_tps_b, tpll)){
            salida_por_b();
        }
        else {
            llegada();
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

void salida_por_a(){

}

void salida_por_b(){

}

void llegada() {

}