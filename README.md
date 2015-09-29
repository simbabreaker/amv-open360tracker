# amv-open360tracker v0.5C
---------------------
# Novedades en esta versión:

* Se ha sustituido el sistema de control de PID del movimiento de servo PAN por un sistema de corrección de error proporcional, que mapea el error entre 

##define MIN_DELTA     0.1   //Angulo mínimo en grados entre el heading del tracker y el del aeromodelo, si es mayor que este ángulo movemos el tracker.
##define MIN_PAN_SPEED  15   //Cantidad mínima en milisegundos que hay que incrementar el pulso del pan para que se mueva.
##define MAX_PAN_SPEED 300   //Cantidad máxima en milisegundos que hay que incrementar el pulso del pan para que se mueva.
##define MAP_ANGLE      90   //Ángulo en grados a partir del cual se empieza a mapear el error del ángulo a gradiente de velocidades.

* Se ha corregido el OFFSET para la crius se, ya no es necesario indicar un OFFSET DE 2700 cuando está mirando hacia el frente. Si se cambia de posición la controladora, habrá que indicar un offest en función de los grados desplazados, sin multiplicar por 10.

* Las correcciones realizadas en esta versión son únicamente experimentales, esta versión no debe sustituir en ningún momento a la versión master. Úsala bajo tu propio riesgo.


---------------------
# Seguidor de Antena de 360º Open Source

Seguidor de antena para FPV con rotaicón contínua de 360º de la [comunidad española de AMV](http://www.aeromodelismovirtual.com/showthread.php?t=34530)

Este proyecto, que se deriva de la [versión master](https://github.com/raul-ortega/amv-open360tracker/) con la intención de implementar un sistema de control del heading más intuitivo y fácil de configurar, además de solventar algunos problemas derivados del actual sistema PIDs


