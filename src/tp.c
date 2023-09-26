#include "../include/tp.h"

// Variables de tiempo
time_t tpll = 0, t = 0;
time_t tpsA[N], tpsB[M], itoA[N], itoB[M];

const time_t HIGH_VALUE = 2145916800;

const time_t FINAL_TIME = 99999999;

// Estado
int nsa = 0, nsb = 0;

// Acumuladores
time_t sps = 0, sta = 0;
int red = 0, nta = 0, ntb = 0, sarra = 0, sarrb = 0;

time_t stoa[N], stob[M];

int main(){
    if(FINAL_TIME>=HIGH_VALUE){
        printf("Error: TF no puede ser mayor a high value\n");
        return 1;
    }
    printf("Inicio de la simulación\n");
    srand((unsigned int) time(NULL));
    inicializar_arrays();

    printf("Inicio de ejecución\n");
    do {
       ejecutar();
    } while (t<FINAL_TIME);
    printf("Fin de ejecución\n");

    // vaciamiento
    printf("Vaciamiento\n");
    tpll = HIGH_VALUE;
    while (nsa != 0 || nsb != 0) {
        ejecutar();
    }
    printf("Fin de vaciamiento\n");
    printf("NSA=%d y NSB=%d\n", nsa, nsb);
   
    impresion_de_resultados();

    printf("Fin de la simulación\n");

    return 0;
}

void inicializar_arrays(){
    inicializar_array_tiempos(tpsA, N, HIGH_VALUE);
    inicializar_array_tiempos(tpsB, M, HIGH_VALUE);
    inicializar_array_tiempos(itoA, N, 0);
    inicializar_array_tiempos(itoB, M, 0);
    inicializar_array_tiempos(stoa, N, 0);
    inicializar_array_tiempos(stob, M, 0);
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

// Funciones principales

void salida_por_a(int indiceMenorTpsA){
    // printf("salida por A=%ld\n", tpsA[indiceMenorTpsA]);
    sps += (tpsA[indiceMenorTpsA]-t)*(nsa+nsb);
    t = tpsA[indiceMenorTpsA];
    nsa--;

    if (nsa>=N){
        int tiempoAtencionA = generar_tiempo_atencion_A();
        tpsA[indiceMenorTpsA] = t + tiempoAtencionA;
        sta += tiempoAtencionA;
    } else {
        itoA[indiceMenorTpsA] = t;
        tpsA[indiceMenorTpsA] = HIGH_VALUE;
    }
}

void salida_por_b(int indiceMenorTpsB){
    // printf("salida por B=%ld\n", tpsB[indiceMenorTpsB]);
    sps += (tpsB[indiceMenorTpsB] - t)*(nsa+nsb);
    t = tpsB[indiceMenorTpsB];
    nsb--;

    if (nsa>N) {
        nsb++;
        nsa--;
        red++;
        int tiempoAtencionA = generar_tiempo_atencion_A();
        tpsB[indiceMenorTpsB] = t + tiempoAtencionA;
        sta += tiempoAtencionA;
    } else {
        if (nsb < M){
            itoB[indiceMenorTpsB] = t;
            tpsB[indiceMenorTpsB] = HIGH_VALUE;
        }
        else {
            int tiempoAtencionB = generar_tiempo_atencion_B();
            tpsB[indiceMenorTpsB] = t + tiempoAtencionB;
            sta += tiempoAtencionB;
        }
    }

}

void llegada() {
    // printf("llegada=%ld\n", tpll);
    sps += (tpll - t)*(nsa+nsb);
    t = tpll;
    time_t intervaloEntreReclamos = generar_intervalo_reclamo();
    tpll = t + intervaloEntreReclamos;
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
        int indicePuestoMasOcioso = indice_de_puesto_mas_tiempo_ocioso_N();
        stoa[indicePuestoMasOcioso] += t - itoA[indicePuestoMasOcioso];
        int tiempoAtencionA = generar_tiempo_atencion_A();
        tpsA[indicePuestoMasOcioso] = t + tiempoAtencionA;
        sta += tiempoAtencionA;
    }
    else {
        if (nsb < M) {
            int indicePuestoMasOcioso = indice_de_puesto_mas_tiempo_ocioso_M();
            nsa--;
            nsb++;
            stob[indicePuestoMasOcioso] += t - itoB[indicePuestoMasOcioso];
            int tiempoAtencionB = generar_tiempo_atencion_B();
            tpsB[indicePuestoMasOcioso] = t + tiempoAtencionB;
            sta += tiempoAtencionB;
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
        int indicePuestoMasOcioso = indice_de_puesto_mas_tiempo_ocioso_M();
        stob[indicePuestoMasOcioso] += t - itoB[indicePuestoMasOcioso];
        int tiempoAtencionB = generar_tiempo_atencion_B();
        tpsB[indicePuestoMasOcioso] = t + tiempoAtencionB;
        sta += tiempoAtencionB;
    }
    return;
}

void impresion_de_resultados(){
    long int ptoa[N];
    long int ptob[M];
    printf("N (cantidad de puestos A): %d\n", N);
    printf("M (cantidad de puestos B): %d\n", M);
    printf("NTA: %d reclamos\n", nta); 
    printf("NTB: %d reclamos\n", ntb);

    for(int i = 0; i<N; i++){
        ptoa[i] = stoa[i]*100/t;
        printf("PTOA(%d): %ld%%\n", i+1, ptoa[i]);
    }
    for(int i = 0; i<M; i++){
        ptob[i] = stob[i]*100/t;
        printf("PTOB(%d): %ld%%\n", i+1, ptob[i]);
    }

    // evitar division por 0 en caso de que no llegue nadie por alguna de las colas
    if(nta != 0 || ntb != 0){
        printf("PPDA: %.2f%%\n", (double)100*sarra/(nta+sarra)); 
        printf("PPDB: %.2f%%\n", (double)100*sarrb/(ntb+sarrb));
        printf("PPS: %.3f minutos\n", (double)sps/((nta+ntb)*60));
        printf("PEC: %.3f minutos\n", (double)(sps-sta)/((nta+ntb)*60));
        printf("PPRB: %.2f%%\n", (double) red/nta);
    } else {
        printf("PPDA: 0\n"); 
        printf("PPS: 0\n");
        printf("PEC: 0\n");
        printf("PPDB: 0\n");
        printf("PPRB: 0\n");
    }
}

// Funciones auxiliares

int generar_tiempo_atencion_A(){
    double rand = generar_numero_random(0,1);
    return (int) (-0.89306 + 117.44*(pow(rand, 0.96368) - 1)/-0.96368) * 60;
}

int generar_tiempo_atencion_B(){
    double rand = generar_numero_random(0,1);
    return (int) (149.23 + 172.32*(pow(rand, 0.94075) - 1)/-0.94075) * 60;
}

int generar_intervalo_reclamo(){
    double rand = generar_numero_random(0.0000001,1);
    return (int) (-45.023 * (pow((1-rand),(1/11.792)) - 1) * pow((1-rand),(-1/11.792))) * 60;
}

cola generar_clase_de_reclamo(){
    double rand = generar_numero_random(0,1);
    if(rand <= 0.0484){
        return ColaA;
    }
    return ColaB;
}

int se_arrepiente_cola_a(){
    double rand = generar_numero_random(0,1);
    if(rand < 0.1681){
        sarra++;
        return 1;
    }
    return 0;
}

int se_arrepiente_cola_b(){
    double rand = generar_numero_random(0,1);
    if(rand < 0.1708){
        sarrb++;
        return 1;
    }
    return 0;
}

double generar_numero_random(double min, double max) {
    double resultado;
    do {
        resultado = (double)rand() / (double)RAND_MAX;
    } while (resultado < min || resultado > max);
    return resultado;
}

void inicializar_array_tiempos(time_t *array, int longitud, time_t valInicial) {
    for (int i = 0; i < longitud; i++) {
        *array = valInicial;
        array++;
    }
    return;
}

int buscar_indice_menor_tiempo(const time_t *array, int longitud) {
    int minIndice = 0;
    for (int i = 1; i < longitud; i++) {
        if (difftime(array[i], array[minIndice]) < 0){
            minIndice = i;
        }
    }
    return minIndice;
}

int tiempo_es_menor_o_igual(time_t tiempo, time_t tiempoAComparar) {
    return difftime(tiempo, tiempoAComparar) <= 0;
}

int tiempo_es_menor(time_t tiempo, time_t tiempoAComparar) {
    return difftime(tiempo, tiempoAComparar) < 0;
}

int es_high_value(time_t tiempo){
    return difftime(tiempo, HIGH_VALUE) == 0;
}


int indice_de_puesto_mas_tiempo_ocioso_M(){
    int j = primer_tiempo_high_value(tpsB, M);
    for (int i = j+1; i<M; i++) {
        if(es_high_value(tpsB[i]) && tiempo_es_menor(itoB[i],itoB[j])){
                j = i;
        }
    }
    return j;
}

int indice_de_puesto_mas_tiempo_ocioso_N(){
    int j = primer_tiempo_high_value(tpsA, N);
    for (int i = j+1; i<N; i++) {
        if(es_high_value(tpsA[i]) && tiempo_es_menor(itoA[i],itoA[j])){
                j = i;
        }
    }
    return j;
}

int primer_tiempo_high_value(const time_t *array, int tamanio) {
    for (int i = 0; i < tamanio; i++) {
        if (es_high_value(array[i]))
            return i;
    }
    return 0;
}

