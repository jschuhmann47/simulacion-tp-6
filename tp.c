#include "tp.h"
#include <bits/types/time_t.h>
#include <stdio.h>
#include <time.h>

// Variables de tiempo
time_t tpll, t;
time_t tpsA[N], tpsB[M], itoA[N], itoB[M];

// Es en 2030 asi que no debería haber problema
const time_t HIGH_VALUE = 1893456000;

// TF, le puse Wed, 01 Nov 2023 00:00:00 GMT
const time_t FINAL_TIME = 1698796800;

// Estado
int nsa = 0, nsb = 0;

// Acumuladores
time_t sps = 0, sta = 0;
int red = 0, nta = 0, ntb = 0, sarra = 0, sarrb = 0;

int stoa[N], stob[M];

int main(){
    srand(time(NULL));

    inicializar_arrays();

    do {
       ejecutar();
    } while (t<FINAL_TIME);

    // vaciamiento
    tpll = HIGH_VALUE;
    while (nsa != 0 || nsb != 0) {
        ejecutar();
    }
   
    impresion_de_resultados();

    return 0;
}

void inicializar_arrays(){
    inicializar_array_tiempos(tpsA,N);
    inicializar_array_tiempos(tpsB,M);
    inicializar_array_tiempos(itoA,N);
    inicializar_array_tiempos(itoB,M);

    inicializar_array_tiempos_ociosos(stoa,N);
    inicializar_array_tiempos_ociosos(stob,M);
}

void ejecutar() {
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
}

void impresion_de_resultados(){
    int ptoa[N];
    int ptob[M];

    for(int i = 0; i<N; i++){
        ptoa[i] = stoa[i]*100/t;
        printf("PTOA(%d): %d\n", i+1, ptoa[i]);
    }
    for(int i = 0; i<M; i++){
        ptob[i] = stob[i]*100/t;
        printf("PTOB(%d): %d\n", i+1, ptob[i]);
    }

    printf("N (cantidad de puestos A): %d\n", N);
    printf("M (cantidad de puestos B): %d\n", M);
    printf("PPS: %ld\n", sps/(nta+ntb));
    printf("PEC: %ld\n", (sps-sta)/(nta+ntb));
    printf("PPDA: %d\n", 100*sarra/(nta+sarra)); // falta sumar arrepentidos en el diagrama
    printf("PPDB: %d\n", 100*sarrb/(ntb+sarrb)); // idem
    printf("PPRB: %d\n", red/nta);

    printf("Fin de la simulación\n");
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

void inicializar_array_tiempos_ociosos(int *array, int longitud){
    for (int i = 0; i<longitud; i++) {
        *array = 0;
        array++;
    }
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
        int indicePuestoMasOcioso = indice_de_puesto_mas_tiempo_ocioso(itoA,N);
        stoa[indicePuestoMasOcioso] += t - itoA[indicePuestoMasOcioso];
        int tiempoAtencion = generar_tiempo_atencion_A();
        tpsA[indicePuestoMasOcioso] = t + tiempoAtencion;
        sta += tiempoAtencion;
    }
    else {
        // chequear como decir que no hay, porque 0 es un indice valido), revisar esta parte
        int indicePuestoMasOcioso = indice_de_puesto_mas_tiempo_ocioso(itoB,M);
        if (indicePuestoMasOcioso != -1){
            nsa--;
            nsb++;
            stob[indicePuestoMasOcioso] += t - itoB[indicePuestoMasOcioso];
            int tiempoAtencion = generar_tiempo_atencion_B();
            tpsB[indicePuestoMasOcioso] = t + tiempoAtencion;
            sta += tiempoAtencion;
            red++;
        }
    }

}

void llegada_por_b(){
     if(se_arrepiente_cola_b()){
        return;
    }
    nsb++;
    ntb++;
    if(nsb<=M){
        int indicePuestoMasOcioso = indice_de_puesto_mas_tiempo_ocioso(itoB,M);
        stob[indicePuestoMasOcioso] += t - itoB[indicePuestoMasOcioso];
        int tiempoAtencion = generar_tiempo_atencion_B();
        tpsB[indicePuestoMasOcioso] = t + tiempoAtencion;
        sta += tiempoAtencion;
    }
    return;
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
    double rand = generar_numero_random();
    if(rand <= 0.0484){
        return ColaA;
    }
    return ColaB;
}

int se_arrepiente_cola_a(){
    double rand = generar_numero_random();
    if(rand < 0.1681){
        sarra++;
        return 1;
    }
    return 0;
}

int se_arrepiente_cola_b(){
    double rand = generar_numero_random();
    if(rand < 0.1708){
        sarrb++;
        return 1;
    }
    return 0;
}

int es_high_value(time_t tiempo){
    return difftime(tiempo, HIGH_VALUE) == 0;
}

int indice_de_puesto_mas_tiempo_ocioso(time_t *array, int longitud){
    // TODO
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
