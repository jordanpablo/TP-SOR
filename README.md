# Sistemas Operativos y Redes

## Trabajo Práctico de hilos y semáforos

Alumno: Jordán Pablo Gonzalo

Informe del TP

Para comenzar con el tp, requirio volver a ver las clases de semaforos para poder comprender las tareas a realizar, investigar asimismo muchas operaciones a realizar en C. Por cuestiones de tiempo no llegue a comprender e implementarlas todas. 
En el repositorio se encuentran adjuntos:
_Receta;
_Prueba de Escritorio;
_leer Receta;
_Hellsburger.c;

Receta: La receta fue pensada como se recomendo en clase, utilizando pipes para separar cada palabra del paso. La idea era luego implementar un metodo para extraer esa informacion y agregarlas a la estructura de pasos con sus acciones e ingredientes.

La Prueba de Escritorio: para la misma primero pense cuales eran los pasos a realizar. A continuacion defini las funciones correspondientes y analice que funcion dependia de otra. Aquellas que eran funciones libres, les agregue el signal directamente. A aquellas que dependieran de un paso anterior, les agregue el wait y el signal. Por ultimo verifique cuales eran los semaforos que requerian ser mutex, siendo los mismos s_saleroLibre, s_cocinaLibre y s_hornoLibre. 
Para la prueba de escritorio solo contemple un equipo y hacer 1 hamburguesa. Se encuentra detallado el razonamiento realizado. Cabe aclarar que tanto s_hornoLibre como s_cocinaLibre se mantienen en 0 durante mas de un ciclo para simular que es una tarea que lleva tiempo.
Como se puede observar, en el ultimo tiempo, todos los semaforos vuelven al estado inicial, lo que daria lugar a armar otra hamburguesa desde 0.

Leer receta: leer la receta me trajo muchos inconvenientes, los cuales no llegue a resolver para aplicar la lectura del archivo al codigo principal. Adjunto este archivo para mostrar lo que llegue a realizar. En el mismo se crea un char de longitud 200 para almacenar las cadenas, y se utiliza el delimitador "|". 
Por medio del for se recorre cada linea del archivo txt y se guarda en el char buffer lo leido. Luego en el char token se guarda cada cadena, que mientras sea diferente de null, se imprime. 
No supe como aplicar lo obtenido a lo solicitado en el tp. Debido a esto, y para poder realizar la entrega, los valores de acciones e ingredientes quedaron harcodeados.

Hellburguer.c: me llevo mucho tiempo comprender el codigo, que hacia cada parte, como y por que estaba dividido de dicha forma. Gracias a los comentarios dejados por Noelia, pude avanzar, apoyandome tambien en muchas busquedas por internet de algunas funciones utilizadas. Tuve varios inconvenientes al intentar compilar pero con paciencia y buscando los errores pude concluir con el archivo funcionando. Luego investigue como hacer que lo que se imprimia por pantalla, se guardara en un archivo tx, lo cual fue realizado con pequeñas modificaciones en la funcion imprimir, donde basicamente tome la misma impresion que se estaba realizando y la adapte a lo que yo necesitaba.

Conclusion:
Me quedan varias dudas que intentare ir resolviendo a medida que avancemos, pero debo decir que el tp fue un desafio, ya que en un principio requirio investigar bastante. Con las modificaciones que se hicieron del mismo (utilizar el template) hizo por un lado que sea un poco mas sencillo, pero en mi caso particular, me complico mucho entender el codigo ofrecido. Luego de ver el video de la clase que realizaron para el tp unas 10 veces (se agradece inmensamente) pude superar ese obstaculo.
