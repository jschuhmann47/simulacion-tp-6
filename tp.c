#include "tp.h"
#include <time.h>

// Variables de tiempo
time_t tpll, t;
time_t tpsA[N], tpsB[M], itoA[N], itoB[M];

// Es en 2030 asi que no debería haber problema
const time_t HIGH_VALUE = 1893456000;

// Acumuladores
time_t sps = 0, sta = 0;
int nsa = 0, nsb = 0, red = 0, nta = 0, ntb = 0;

int main(){
    srand(time(NULL));

    inicializar_arrays();

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

void inicializar_arrays(){
    inicializar_array_tiempos(tpsA,N);
    inicializar_array_tiempos(tpsB,M);
    inicializar_array_tiempos(itoA,N);
    inicializar_array_tiempos(itoB,M);
}

double generar_numero_random() {
    return (double)rand() / (double)RAND_MAX;
}

void inicializar_array_tiempos(time_t *array, int longitud) {
    for (int i = 0; i < longitud; i++) {
        *array = HIGH_VALUE;
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
        int tiempoAtencion = generar_tiempo_atencion_A();
        tpsA[indiceMenorTiempoA] = t + tiempoAtencion;
        sta += tiempoAtencion;
    } else {
        int i = 0;
        itoA[i] = t;
        tpsA[indiceMenorTiempoA] = 0;
    }
}

void salida_por_b(int indiceMenorTpsB){
    sps += (tpsB[indiceMenorTpsB] - t)*(nsa-nsb);
    t = tpsB[indiceMenorTpsB];
    nsb--;
    if (nsa>=N) {
        nsb++;
        nsa--;
        red++;  
    } else {
        if (nsb < M){
            itoB[indiceMenorTpsB] = t;
            tpsB[indiceMenorTpsB] = 0;
            return;
        }
    }
    int tiempoAtencion = generar_tiempo_atencion_B();
    tpsB[indiceMenorTpsB] = t + tiempoAtencion;
    sta += tiempoAtencion;
}

void llegada() {
    sps += (tpll - t)*(nsa+nsb);
    t = tpll;
    int tiempoSiguienteReclamo = generar_intervalo_reclamo();
    tpll = t + tiempoSiguienteReclamo;
    cola tipoCola = generar_clase_de_reclamo();
    if (tipoCola == ColaA) {
        llegada_por_a();
    } else {
        llegada_por_b();
    }
}

void llegada_por_a(){
    if(se_arrepiente_cola_a()){
        return;
    }
    nsa++;
    nta++;
    if(nsa<=N){

    }

}

void llegada_por_b(){
    
}

int generar_tiempo_atencion_A(){
    // TODO
    return 0;
}

int generar_tiempo_atencion_B(){
    // TODO
    return 0;
}

int generar_intervalo_reclamo(){
    // TODO
    return 0;
}

cola generar_clase_de_reclamo(){
    // TODO
    return ColaA;
}

int se_arrepiente_cola_a(){
    // TODO
    return 0;
}

int se_arrepiente_cola_b(){
    // TODO
    return 0;
}

int es_high_value(time_t tiempo){
    return tiempo == HIGH_VALUE;
}

int indice_de_puesto_mas_tiempo_ocioso(time_t *array, int longitud){
    int j = 0;
    for (int i = 0; i<M; i++) {
        if(!es_high_value(tpsB[i])){
            continue;
        }
        if(tiempo_es_menor_o_igual(itoB[i],itoB[j])){
            j = i;
            // DUDA ACA, PUEDE SETEARSE i=0 Y FALLA?
        }
    }
    if(j==0 && !es_high_value(tpsB[0])){
        return 0;
    }
    return 1;
}