#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void inicializar_arrays();

// Genera un random entre 0 y 1
double generar_numero_random();

void inicializar_array_tiempos(time_t *array, int longitud);
int buscar_indice_menor_tiempo(time_t *array, int longitud);
int tiempo_es_menor_o_igual(time_t tiempo, time_t tiempo_a_comparar);
int tiempo_es_menor(time_t tiempo, time_t tiempo_a_comparar);
void salida_por_a(int indiceMenorTpsA);
void salida_por_b(int indiceMenorTpsB);
void llegada();
int generar_tiempo_atencion_A();
int generar_tiempo_atencion_B();