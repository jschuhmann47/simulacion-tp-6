#include <stdio.h>
#include <time.h>
#include <stdlib.h>

double generarNroRandom();
void inicializarArrayTiempos(time_t *array, int longitud);
time_t buscarMenorTiempo(time_t *array, int longitud);
int tiempoEsMenorOIgual(time_t tiempo, time_t tiempo_a_comparar);
int tiempoEsMenor(time_t tiempo, time_t tiempo_a_comparar);