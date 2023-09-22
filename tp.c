#include "tp.h"
#include <time.h>

enum variables_de_control{
    N = 1,
    M = 2
};

// Variables de tiempo
time_t tpll, t;
time_t tpsA[N], tpsB[M], itoA[N], itoB[M];

// Acumuladores
time_t sps = 0, sta = 0;
int nsa = 0, nsb = 0;

int main(){
    srand(time(NULL));
    
    inicializar_array_tiempos(tpsA,N);
    inicializar_array_tiempos(tpsB,M);

    int indiceMenorTpsA = buscar_indice_menor_tiempo(tpsA, N);
    int indiceMenorTpsB = buscar_indice_menor_tiempo(tpsB, M);

    if(tiempo_es_menor_o_igual(tpsA[indiceMenorTpsA],tpsB[indiceMenorTpsB])){
        if(tiempo_es_menor(tpsA[indiceMenorTpsA], tpll)){
            salida_por_a(indiceMenorTpsA);
        }
        else {
            llegada();
        }
    }
    else {
        if(tiempo_es_menor(tpsB[indiceMenorTpsB], tpll)){
            salida_por_b(indiceMenorTpsB);
        }
        else {
            llegada();
        }
    }

    printf("%f",generar_numero_random());

    return 0;
}

double generar_numero_random() {
    return (double)rand() / (double)RAND_MAX;
}

void inicializar_array_tiempos(time_t *array, int longitud) {
    for (int i = 0; i < longitud; i++) {
        *array = 0;
        array++;
    }
    return;
}

int buscar_indice_menor_tiempo(time_t *array, int longitud) {
    int min = 0;
    for (int i = 1; i < longitud; i++) {
        if (*array < min){
            min = i;
        }
        array++;
    }
    return min;
}

int tiempo_es_menor_o_igual(time_t tiempo, time_t tiempoAComparar) {
    return difftime(tiempo, tiempoAComparar) <= 0;
}

int tiempo_es_menor(time_t tiempo, time_t tiempoAComparar) {
    return difftime(tiempo, tiempoAComparar) < 0;
}

void salida_por_a(int indiceMenorTiempoA){
    sps += (tpsA[indiceMenorTiempoA]-t)*(nsa-nsb);
    t = tpsA[indiceMenorTiempoA];
    nsa--;

    if (nsa>=N){
        int tiempoAtencion = tiempo_atencion_A();
        tpsA[indiceMenorTiempoA] = t + tiempoAtencion;
        sta += tiempoAtencion;
    } else {
        int i = 0;
        itoA[i] = t;
        tpsA[indiceMenorTiempoA] = 0;
    }
}

void salida_por_b(int indiceMenorTpsB){

}

void llegada() {

}

int tiempo_atencion_A(){
    // TODO
    return 0;
}