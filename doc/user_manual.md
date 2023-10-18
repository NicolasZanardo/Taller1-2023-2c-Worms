# Manual de Usuario

## Instalación de SDL

Ejecutar en la consola:
```shell
sudo apt-get install libsdl2-2.0-0  libsdl2-dev \
libsdl2-image-2.0-0 libsdl2-image-dev \
libsdl2-mixer-2.0-0 libsdl2-mixer-dev \
libsdl2-ttf-2.0-0 libsdl2-ttf-dev \
```

## Compilación

Para realizar la compilación dentro de la carpeta `build/` del proyecto, ejecutar:

```shell
cmake ..
make
```

Los binarios se generan en la carpeta `build/bin/`

## Testing

Los tests se compilan como binarios ejecutables al realizar el proceso de compilación. Los ejecutables resultantes se guardan en la carpeta `build/bin/`.	
