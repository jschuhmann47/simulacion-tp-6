#include "tp.h"

// Variables de tiempo
time_t tpll = 0, t = 0;
time_t tpsA[N], tpsB[M], itoA[N], itoB[M];

const time_t HIGH_VALUE = 15000000;

const time_t FINAL_TIME = 50000;

// Estado
int nsa = 0, nsb = 0;

// Acumuladores
time_t sps = 0, sta = 0;
int red = 0, nta = 0, ntb = 0, sarra = 0, sarrb = 0;

time_t stoa[N], stob[M];

int main(){
    printf("Inicio\n");
    srand((unsigned int) time(NULL));
    inicializar_arrays();
    printf("Arrays inicializados\n");

    printf("Inicio ejecucion\n");
    do {
       ejecutar();
    } while (t<FINAL_TIME);
    printf("Fin ejecucion\n");

    // vaciamiento
    printf("Vaciamiento\n");
    tpll = HIGH_VALUE;
    while (nsa != 0 || nsb != 0) {
        ejecutar();
    }
    printf("Fin vaciamiento\n");
   
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

void impresion_de_resultados(){
    long int ptoa[N];
    long int ptob[M];
    printf("N (cantidad de puestos A): %d\n", N);
    printf("M (cantidad de puestos B): %d\n", M);

    for(int i = 0; i<N; i++){
        ptoa[i] = stoa[i]*100/t;
        printf("PTOA(%d): %ld\n", i+1, ptoa[i]);
    }
    for(int i = 0; i<M; i++){
        ptob[i] = stob[i]*100/t;
        printf("PTOB(%d): %ld\n", i+1, ptob[i]);
    }

    printf("PPS: %ld\n", sps/(nta+ntb));
    printf("PEC: %ld\n", (sps-sta)/(nta+ntb));
    printf("PPDA: %d\n", 100*sarra/(nta+sarra)); 
    printf("PPDB: %d\n", 100*sarrb/(ntb+sarrb));
    printf("PPRB: %d\n", red/nta);
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

void salida_por_a(int indiceMenorTpsA){
    printf("salida por A=%ld\n", tpsA[indiceMenorTpsA]);
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
    printf("salida por B=%ld\n", tpsB[indiceMenorTpsB]);
    sps += (tpsB[indiceMenorTpsB] - t)*(nsa+nsb);
    t = tpsB[indiceMenorTpsB];
    nsb--;
    if (nsa>N) {
        nsb++;
        nsa--;
        red++;  
    } else {
        if (nsb < M){
            itoB[indiceMenorTpsB] = t;
            tpsB[indiceMenorTpsB] = HIGH_VALUE;
            return;
        }
    }
    int tiempoAtencionB = generar_tiempo_atencion_B();
    tpsB[indiceMenorTpsB] = t + tiempoAtencionB;
    sta += tiempoAtencionB;
}

void llegada() {
    printf("llegada con tpll=%ld, t=%ld\n", tpll, t);
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
        int indicePuestoMasOcioso = indice_de_puesto_mas_tiempo_ocioso_M();
        if (indicePuestoMasOcioso != M+1){
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

int generar_tiempo_atencion_A(){
    double rand = generar_numero_random(0,0.99);
    return (int) (3083.1*(pow(-log(1-rand),(1/0.84892))));
}

int generar_tiempo_atencion_B(){
    double rand = generar_numero_random(0,0.99);
    return (int) (2180.9*(pow(-log(1-rand),(1/0.77918))));
}

int generar_intervalo_reclamo(){
    double rand = generar_numero_random(0,1);
    return (int) (-45.023 * (pow((1-rand),(1/11.792)) - 1) * pow((1-rand),(-1/11.792)));
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

int es_high_value(time_t tiempo){
    return difftime(tiempo, HIGH_VALUE) == 0;
}

int indice_de_puesto_mas_tiempo_ocioso_M(){
    int j = 0;
    for (int i = 1; i<M; i++) {
        if(!es_high_value(tpsB[i])){
            continue;
        }
        if(tiempo_es_menor_o_igual(itoB[i],itoB[j])){
            j = i;
        }
    }
    if(j==0 && !es_high_value(tpsB[0])){
        return M+1;
    }
    return j;
}

int indice_de_puesto_mas_tiempo_ocioso_N(){
    int j = 0;
    for (int i = 1; i<N; i++) {
        if(!es_high_value(tpsA[i])){
            continue;
        }
        if(tiempo_es_menor_o_igual(itoA[i],itoA[j])){
            j = i;
        }
    }
    if(j==0 && !es_high_value(tpsA[0])){
        return N+1;
    }
    return j;
}
