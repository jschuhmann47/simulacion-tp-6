# Simulacion TP 6

Trabajo práctico hecho en grupo para la materia Simulación. El mismo consistía en seleccionar un sistema de la vida real y realizar simulaciones para poder determinar los valores óptimos que hagan el modelo mas eficiente y/o que obtenga mayores ganancias y menores costos.

## Modelo
El modelo consiste en un banco donde se tienen dos tipos de colas de atención de reclamos: una cola estándar y una cola prioritaria. Se tenían N colas estándar y M colas prioritarias, y el objetivo de la simulación entre otros era averiguar los valores de N y M óptimos para minimizar los tiempos de atención y los tiempos en los que los puestos estaban ociosos.

## Generación de valores aleatorios
Se utilizó el método de la inversa para la generación de intervalo entre arribos de los clientes y de tiempo de atención de cada tipo de cola. Antes se modeló la función en base a los datos con las distribuciones probabilísticas de Weibull y distrubición uniforme.

## Resultados
Los resultados se encuentran en los archivos `casoIntermedio.txt`, `casoMinimo.txt` y `casoReal.txt`, donde mínimo era un valor muy bajo de empleados, real era el caso que sucedía en la realidad de donde tomamos los datos, e intermedio es el caso más balanceado.

## Ejecución
Para compilar en Linux:
`gcc tp.c -o tp -lm`
