
#include <stdlib.h>     // para usar exit y funciones de la libreria standard
#include <string.h>
#include <pthread.h>    // para usar threads
#include <semaphore.h>  // para usar semaforos
#include <unistd.h>


#include <stdio.h>      // libreria estandar
#define LIMITE 50

//creo estructura de semaforos 
struct semaforos {
    sem_t s_mezclarCPAyCarne;
	sem_t s_salarMezcla;
	sem_t s_armarMedallones;
	sem_t s_cocinarMedallones;
	sem_t s_LYT;
	sem_t s_panListo;
	sem_t s_armarHamburguesa;
	sem_t s_hornoLibre;		//mutex
	sem_t s_saleroLibre;	//mutex
	sem_t s_cocinaLibre; 	//mutex
};

//creo los pasos con los ingredientes
struct paso {
   char accion [LIMITE];
   char ingredientes[4][LIMITE];
   
};

//creo los parametros de los hilos 
struct parametro {
 int equipo_param;
 struct semaforos semaforos_param;
 struct paso pasos_param[8];
};

//funcion para imprimir las acciones y los ingredientes de la accion
void* imprimirAccion(void *data, char *accionIn) {
	struct parametro *mydata = data;
	//calculo la longitud del array de pasos 
	int sizeArray = (int)( sizeof(mydata->pasos_param) / sizeof(mydata->pasos_param[0]));
	//indice para recorrer array de pasos 
	int i;
	for(i = 0; i < sizeArray; i ++){
		//pregunto si la accion del array es igual a la pasada por parametro (si es igual la funcion strcmp devuelve cero)
		if(strcmp(mydata->pasos_param[i].accion, accionIn) == 0){
		printf("\tEquipo %d - accion %s \n " , mydata->equipo_param, mydata->pasos_param[i].accion);
		//calculo la longitud del array de ingredientes
		int sizeArrayIngredientes = (int)( sizeof(mydata->pasos_param[i].ingredientes) / sizeof(mydata->pasos_param[i].ingredientes[0]) );
		//indice para recorrer array de ingredientes
		int h;
		printf("\tEquipo %d -----------ingredientes : ----------\n",mydata->equipo_param); 
			for(h = 0; h < sizeArrayIngredientes; h++) {
				//consulto si la posicion tiene valor porque no se cuantos ingredientes tengo por accion 
				if(strlen(mydata->pasos_param[i].ingredientes[h]) != 0) {
							printf("\tEquipo %d ingrediente  %d : %s \n",mydata->equipo_param,h,mydata->pasos_param[i].ingredientes[h]);
				}
			}
		}
	}
}

//funcion para tomar de ejemplo
void* cortar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "Cortar Verduras";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 20000 );
	//doy la señal a la siguiente accion (Cortar me habilita mezclar)
    sem_post(&mydata->semaforos_param.s_mezclarCPAyCarne);
	
    pthread_exit(NULL);
}

void* mezclar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "Mezclar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 20000 );
	//doy la señal a la siguiente accion (Mezclar me habilita Salar)
    sem_post(&mydata->semaforos_param.s_salarMezcla);
	
    pthread_exit(NULL);
}


void* salar(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "Salar";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 20000 );
	//doy la señal a la siguiente accion (Salar me habilita Armar Medallones)
    sem_post(&mydata->semaforos_param.s_armarMedallones);
	
    pthread_exit(NULL);
}

void* armarMedallones(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "Armar Medallones";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 20000 );
	//doy la señal a la siguiente accion (Armar Medallones me habilita Cocinar Medallones)
    sem_post(&mydata->semaforos_param.s_cocinarMedallones);
	
    pthread_exit(NULL);
}


void* cocinarMedallones(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "Cocinar Medallones";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 50000 );
	//doy la señal a la siguiente accion (Cocinar Medallones me habilita Armar Hamburguesa)
    sem_post(&mydata->semaforos_param.s_armarHamburguesa);
	
    pthread_exit(NULL);
}

void* cortarLYT(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "Cortar Lechuga y Tomate";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 20000 );
	//doy la señal a la siguiente accion (Cortar lechuga y tomate me habilita Armar Hamburguesa)
    sem_post(&mydata->semaforos_param.s_LYT);
	
    pthread_exit(NULL);
}

void* hornearPan(void *data) {
	//creo el nombre de la accion de la funcion 
	char *accion = "Hornear Pan";
	//creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero). 
	struct parametro *mydata = data;
	//llamo a la funcion imprimir le paso el struct y la accion de la funcion
	imprimirAccion(mydata,accion);
	//uso sleep para simular que que pasa tiempo
	usleep( 100000 );
	//doy la señal a la siguiente accion (Hornear Pan me habilita Armar Hamburguesa)
    sem_post(&mydata->semaforos_param.s_panListo);
	
    pthread_exit(NULL);
}

void* ejecutarReceta(void *i) {
	
	//variables semaforos
	sem_t s_mezclarCPAyCarne;
	sem_t s_salarMezcla;
	sem_t s_armarMedallones;
	sem_t s_cocinarMedallones;
	sem_t s_LYT;
	sem_t s_panListo;
	sem_t s_armarHamburguesa;
	//sem_t s_hornoLibre;
	//sem_t s_saleroLibre;
	//sem_t s_cocinaLibre;
	//crear variables semaforos aqui
	
	//variables hilos
	pthread_t p1; 
	pthread_t p2; 
	pthread_t p3; 
	//crear variables hilos aqui
	
	//numero del equipo (casteo el puntero a un int)
	int p = *((int *) i);
	
	printf("Ejecutando equipo %d \n", p);

	//reservo memoria para el struct
	struct parametro *pthread_data = malloc(sizeof(struct parametro));

	//seteo los valores al struct
	
	//seteo numero de grupo
	pthread_data->equipo_param = p;

	//seteo semaforos
	pthread_data->semaforos_param.s_mezclarCPAyCarne = s_mezclarCPAyCarne;
	pthread_data->semaforos_param.s_salarMezcla = s_salarMezcla;
	pthread_data->semaforos_param.s_armarMedallones = s_armarMedallones;
	pthread_data->semaforos_param.s_cocinarMedallones = s_cocinarMedallones;
	pthread_data->semaforos_param.s_LYT = s_LYT;
	pthread_data->semaforos_param.s_panListo = s_panListo;
	pthread_data->semaforos_param.s_armarHamburguesa = s_armarHamburguesa;
	//pthread_data->semaforos_param.s_hornoLibre = s_hornoLibre;
	//pthread_data->semaforos_param.s_saleroLibre = s_saleroLibre;
	//pthread_data->semaforos_param.s_cocinaLibre = s_cocinaLibre;
	
	//setear demas semaforos al struct aqui
	

	//seteo las acciones y los ingredientes (Faltan acciones e ingredientes) ¿Se ve hardcodeado no? ¿Les parece bien?
     	strcpy(pthread_data->pasos_param[0].accion, "cortar");
		strcpy(pthread_data->pasos_param[0].ingredientes[0], "ajo");
        strcpy(pthread_data->pasos_param[0].ingredientes[1], "perejil");
		strcpy(pthread_data->pasos_param[0].ingredientes[2], "cebolla");

		strcpy(pthread_data->pasos_param[1].accion, "mezclar");
		strcpy(pthread_data->pasos_param[1].ingredientes[0], "ajo");
        strcpy(pthread_data->pasos_param[1].ingredientes[1], "perejil");
		strcpy(pthread_data->pasos_param[1].ingredientes[2], "cebolla");
		strcpy(pthread_data->pasos_param[1].ingredientes[3], "carne picada");
	
	
	//inicializo los semaforos

	sem_init(&(pthread_data->semaforos_param.s_mezclarCPAyCarne),0,1);
	sem_init(&(pthread_data->semaforos_param.s_salarMezcla),0,0);
	sem_init(&(pthread_data->semaforos_param.s_armarMedallones),0,0);
	sem_init(&(pthread_data->semaforos_param.s_cocinarMedallones),0,0);
	sem_init(&(pthread_data->semaforos_param.s_LYT),0,0);
	sem_init(&(pthread_data->semaforos_param.s_panListo),0,0);
	sem_init(&(pthread_data->semaforos_param.s_armarHamburguesa),0,0);
	//sem_init(&(pthread_data->semaforos_param.s_hornoLibre),0,1);
	//sem_init(&(pthread_data->semaforos_param.s_saleroLibre),0,1);
	//sem_init(&(pthread_data->semaforos_param.s_cocinaLibre),0,1);
	



	//creo los hilos a todos les paso el struct creado (el mismo a todos los hilos) ya que todos comparten los semaforos 
    int rc;
    rc = pthread_create(&p1,                           //identificador unico
                            NULL,                          //atributos del thread
                                cortar,             //funcion a ejecutar
                                pthread_data);                     //parametros de la funcion a ejecutar, pasado por referencia
								
	rc = pthread_create(&p2,                          
                            NULL,                          
                                mezclar,            
                                pthread_data);                 	

	rc = pthread_create(&p3,                        
                            NULL,                    
                                salar,         
                                pthread_data);       

	rc = pthread_create(&p4,                        
                            NULL,                    
                                armarMedallones,         
                                pthread_data); 

	rc = pthread_create(&p5,                        
                            NULL,                    
                                cocinarMedallones,         
                                pthread_data); 

	rc = pthread_create(&p6,                        
                            NULL,                    
                                cortarLYT,         
                                pthread_data); 

	rc = pthread_create(&p7,                        
                            NULL,                    
                                hornearPan,         
                                pthread_data); 		

	rc = pthread_create(&p8,                        
                            NULL,                    
                                armarHamburguesa,         
                                pthread_data); 									
								
	//crear demas hilos aqui
	
	
	//join de todos los hilos
	pthread_join (p1,NULL);
	pthread_join (p2,NULL);
	pthread_join (p3,NULL);
	//crear join de demas hilos


	//valido que el hilo se alla creado bien 
    if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     }

	 
	//destruccion de los semaforos 
	sem_destroy(&s_mezclarCPAyCarne);
	sem_destroy(&s_salarMezcla);
	sem_destroy(&s_armarMedallones);
	sem_destroy(&s_cocinarMedallones);
	sem_destroy(&s_LYT);
	sem_destroy(&s_panListo);
	sem_destroy(&s_armarHamburguesa);
	//sem_destroy(&s_hornoLibre);
	//sem_destroy(&s_saleroLibre);
	//sem_destroy(&s_cocinaLibre);
	
	//destruir demas semaforos 
	
	//salida del hilo
	 pthread_exit(NULL);
}


int main ()
{
	//creo los nombres de los equipos 
	int rc;
	int *equipoNombre1 =malloc(sizeof(*equipoNombre1));
	int *equipoNombre2 =malloc(sizeof(*equipoNombre2));
	int *equipoNombre3 =malloc(sizeof(*equipoNombre3));
	*equipoNombre1 = 1;
	*equipoNombre2 = 2;
	*equipoNombre3 = 3;

	//creo las variables los hilos de los equipos
	pthread_t equipo1; 
	pthread_t equipo2;
	pthread_t equipo3;
 
	//inicializo los hilos de los equipos
    rc = pthread_create(&equipo1,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre1); 

    rc = pthread_create(&equipo2,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre2);

    rc = pthread_create(&equipo3,                           //identificador unico
                            NULL,                          //atributos del thread
                                ejecutarReceta,             //funcion a ejecutar
                                equipoNombre3);

   if (rc){
       printf("Error:unable to create thread, %d \n", rc);
       exit(-1);
     } 

	//join de todos los hilos
	pthread_join (equipo1,NULL);
	pthread_join (equipo2,NULL);
	pthread_join (equipo3,NULL);


    pthread_exit(NULL);
}


//Para compilar:   gcc HellsBurgers.c -o ejecutable -lpthread
//Para ejecutar:   ./ejecutable
