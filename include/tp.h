#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

enum variables_de_control{
    // Cola A
    N = 3,

    // Cola B
    M = 200
};

enum cola_elegida {
    ColaA,
    ColaB 
};

typedef enum cola_elegida cola;

void inicializar_arrays();

// Genera un random entre 0 y 1
double generar_numero_random(double min, double max);

void ejecutar();
void impresion_de_resultados();
void inicializar_array_tiempos(time_t *array, int longitud, time_t valInicial);
int buscar_indice_menor_tiempo(const time_t *array, int longitud);
int tiempo_es_menor_o_igual(time_t tiempo, time_t tiempo_a_comparar);
int tiempo_es_menor(time_t tiempo, time_t tiempo_a_comparar);
void salida_por_a(int indiceMenorTpsA);
void salida_por_b(int indiceMenorTpsB);
void llegada();
int generar_tiempo_atencion_A();
int generar_tiempo_atencion_B();
int generar_intervalo_reclamo();
cola generar_clase_de_reclamo();
void llegada_por_a();
void llegada_por_b();
int se_arrepiente_cola_a();
int se_arrepiente_cola_b();
int es_high_value(time_t tiempo);
int indice_de_puesto_mas_tiempo_ocioso_N();
int indice_de_puesto_mas_tiempo_ocioso_M();
int primer_tiempo_high_value(const time_t *array, int tamanio);