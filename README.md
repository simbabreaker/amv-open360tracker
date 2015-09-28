# amv-open360tracker v0.5B
---------------------
# Novedades en esta versión:

* Se ha sustituido el sistema de control de PID del movimiento de servo PAN por un sistema de corrección de error proporcional. El heading del tracker tiene un rango en el ángulo de 0 180 grados (en valor absoluto) con respecto al heading del objetivo, que se ha mapeado contra un rango de valores entre MIN_PAN_SPEED a MAX_PAN_SPEED, que representa el incremento mínimo y máxiom que se suma al pulso central que mantiene el servo en reposo para que este se mueva. Cuando la diferencia entre los dos heading se aproxima a cero, el mapeo provoca que el servo se mueva lo más lentamente posible, y cuando el error crece, aumenta la velocidad. Una vez se alcanza el objetivo, con un margen de error fijado por el parámetro MIN_DELTA, el tracker se detiene, hasta que la diferencia vuelva a crecer.

* Se ha corregido el OFFSET para la crius se, ya no es necesario indicar un OFFSET DE 2700 cuando está mirando hacia el frente. Si se cambia de posición la controladora, habrá que indicar un offest en función de los grados desplazados, sin multiplicar por 10.

* Las correcciones realizadas en esta versión son únicamente experimentales, esta versión no debe sustituir en ningún momento a la versión master. Úsala bajo tu propio riesgo.


---------------------
# Seguidor de Antena de 360º Open Source

Seguidor de antena para FPV con rotaicón contínua de 360º de la [comunidad española de AMV](http://www.aeromodelismovirtual.com/showthread.php?t=34530)

Este proyecto, que se deriva de la [versión master](https://github.com/raul-ortega/amv-open360tracker/) con la intención de implementar un sistema de control del heading más intuitivo y fácil de configurar, además de solventar algunos problemas derivados del actual sistema PIDs


