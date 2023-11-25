# Taller1-2023-2c-Worms
Repositorio para entrega del ultimo trabajo practico de la materia Taller I.

Para compilar el proyecto:

## Instalación de SDL

Ejecutar en la consola:
```shell
sudo apt-get install libsdl2-2.0-0  libsdl2-dev
libsdl2-image-2.0-0 libsdl2-image-dev
libsdl2-mixer-2.0-0 libsdl2-mixer-dev
libsdl2-ttf-2.0-0 libsdl2-ttf-dev
```

## Compilar
build command line: 

```
mkdir build
cd build
cmake ..
make
cd bin
```

Para correr los ejecutables del server y del cliente 

Servidor:

- ./server_app [port]
  
Ejemplo:
```
./server_app 1111
```

Cliente:

- ./client_app [serv] [port]

Ejemplo:

```
./client_app localhost 1111
```

Una vez que los clientes se hayan conectado, en el server correr en linea de comandos:
- start

## Instrucciones del juego:

- Flechas iquierda/derecha: Desplazarse
- Enter: Salto hacia adelante
- Delete: Salto hacia atras
- Flechas arriba/abajo: Apuntar hacia arriba/abajo
- Q: Bazooka
- W: Mortar
- E: Green grenade
- Espacio: disparar

