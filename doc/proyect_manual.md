# Manual de proyecto

### Introducción

La idea de este manual es documentar en que trabajó cada integrante del equipo, como se organizaron por semana y cuanto difirió del plan inicial.
Cuales fueron los puntos problematicos,
hasta donde llegamos con el enunciado,
que cambiaríamos y comentar que documentaciones usamos.


#### Juan Duzac:

Personalmente, trabaje principalmente en la lógica del juego en el servidor.
Del lado del servidor en: 

El loop del juego, todo lo relacionado a box2d, la implementación de los modelos y sistemas
de Armas/Projectiles/Worms del server, implemente la configuración por YAML.
Manejo de turnos, a quien debería seguir la camara, agregado/removido de las entidades.

En base a la arquitectura de NetMessages que armo nico, para las feature que implemente, fui creando los mensajes necesarios y
agregue los eventos de sdl que deberían desembocar en mandar ese NetMessage al server.
Aun que tambien metí un poco de mano en agregar ciertos pocos elementos de UI en base a las clases que creo Nico.

No hubo una organización semanal muy clara, fui tomando lo que considere mas de mayor prioridad para ir iterando y avanzando el juego a un producto mas jugable.


Puntos problematicos que vi:

El tiempo no me fue suficiente, a pesar de haberle dedicado un montón de tiempo, igualmente quedaron cosas por implementar/mejorar
y errores.
No se llego con todas las armas por que había cosas que corregir, cambios que integrar y otras prioridades.
Faltaron las cajas de suministros, agregar sonidos, arreglar los threads y memoria.
La primera semana tuvimos mala comunicación, y siento que no hubo tanta proactividad.

Documentación que use:

- La documentación oficial de box2d: https://box2d.org/documentation/

- Iforce2d me sirvió mucho tambien: https://www.iforce2d.net/

- The double dispatch pattern (article 31 in Meyer's more effective C++)
para la resolución de colisiones.

Trabaje en MacOS de sistema operativo y con CLion de IDE:

Justo tuve un cambio de laburo y cambio de compu, y me vino con algunas desventajas por la diferencia de arquitectura y ciertos soportes de librerias.
