# Sistemas Operativos y Redes

## Trabajo Práctico de hilos y semáforos

Prueba de Escritorio:

Cortar cebolla perejil y ajo
Mezclar con carne
Salar mezcla
Armar Medallones
Cocinar medallones
Cortar lechuga y tomate
Hornear Pan
Armar Hamburguesa

  
	cortarCPA ()                  cortarLYT()
	v(s_mezclarCPAyCarne)         v(s_LYT)


	p(s_mezclarCPAyCarne)         p(s_hornoLibre)
	mezclarCPAyCarne()            hornearPan()
	v(s_salarMezcla)              v(s_panListo
					v(s_hornoLibre)

	p(s_salarMezcla)
	p(s_saleroLibre)
	salarMezcla() 
	v(s_armarMedallones)
	v(s_saleroLibre)


	p(s_armarMedallones)
	armarMedallones()
	v(s_cocinarMedallones)


	p(s_cocinarMedallones)          p(s_armarHamburguesa)
	p(s_cocinaLibre)                p(s_panListo)
	cocinarMedallones()             p(s_LYT)
	v(s_armarHamburguesa)           armarHamburguesa()
	p(s_cocinaLibre)


Prueba:

EI= Estado Inicial

                    EI
s_hornoLibre        1	  0	0	0	1	1	1	1

s_saleroLibre       1	  1	1	0	1	1	1	1

s_cocinaLibre       1	  1	1	1	1	0	1	1

s_mezclarCPAyCarne  0	  1	0	0	0	0	0	0

s_salarMezcla       0	  0	1	0	0	0	0	0

s_armarMedallones   0	  0	0	1	0	0	0	0

s_cocinarMedallones 0	  0	0	0	1	1	0	0

s_LYT               0	  0	0	0	0	1	1	0

s_panListo          0	  0	0	0	1	1	1	0

s_armarHamburguesa  0	  0	0	0	0	0	1	0

1. cortarCPA no requiere ningun semaforo y habilita s_mezclarCPAyCarne. Al mismo tiempo se pregunta si s_hornoLibre, al estar en 1, se pone en 0.
2. Se pregunta si s_mezclarCPAyCarne esta en 1. Como lo esta, se pone en 0. Luego se envia signal a s_salarMezcla.
3. Se verifica el estado de s_salarMezcla, estando en1, se pone en 0. Asimismo se verifica si s_saleroLibre esta en 1. Al estarlo se pone en 0. Se da signal a s_armarMedallones y se
vuelve a dar signal a s_saleroLibre.
4. Se termina de cocinar el pan. Se da signal a s_panListo y a s_hornoLibre. Se arman verifica s_armarMedallones, al estar en 1, se pueden armar. se da signal a s_cocinarMedallones.
5. cortarLYT no requiere ningun semaforo da signal a s_LYT. Se verifica s_cocinarMedallones, al estar en 1 se pone en 0. Se verifica s_cocinaLibre, al estar en 1 se pone en 0. 
6. Una vez cocinados se da señal a s_armarHamburguesa y s_cocinaLibre.
7. Se verifica s_armarHamburguesa, s_panListo y s_LYT. Al estar todos en 1, se arma la hamburguesa y todos vuelven a 0.
