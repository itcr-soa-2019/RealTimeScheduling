## Proyecto 3 Sistemas Operativos Avanzados
### Scheduling en Tiempo Real

El propósito de este proyecto es simular el comportamiento
de varios algoritmos de scheduling clásicos para Sistemas
Operativos de Tiempo Real (RTOS). 

### II. ALGORITMOS
RTOS:

-RM: Rate Monothonic

-EDF: Earliest Deadline First

-LLF: Least Laxity First

### Instrucciones de uso

#### Compilación
``` bash
$ sudo make install
$ make
```
#### Ejecución
```
$ cd bin/
$ ./main
```
Seleccionar las opciones deseadas en la interfaz gráfica y dar click en procesar:
* Ingresar la cantidad de tareas y dar click en ***Crear Tareas***
* Para cada tarea indicar el tiempo de ejecución y periodo.
* Finalmente escoger los algoritmos y si se quiere o no los resultados de forma conjunta.
* Dar click en procesar.
* Con suerte se generará un pdf con la presentación de los resultados para la simulación.
![](images/maingui.png)