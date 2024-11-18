# Ejemplo de CMAKE para el TP Final

**Importante:** el primer commit de este repositorio tiene el setup
básico para el TP Final que incluye la instalación de la lib
`libSDL2pp` (el wrapper de C++).

El resto de los commits son a modo de ejemplo de como se pueden
agregar mas código fuente al proyecto.

Este ejemplo **no** incluye instalarse la librería `SDL2` ni tampoco
instala otras librerías que puedan ser necesarias ni tampoco un
instalador (aunque **si** incluye Google Tests)

**Se deben agregar las librerias necesarias y el instalador.**

También el ejemplo usa una estructura de carpetas muy simple:

```
client/
server/
editor/
common/
```

Bien se puede mejorar (cambiando el cmakefile) agregando mas
sub-carpetas.

Asi tambien **deben** ser cambiados los *targets* del cmake (`taller_client`,
`taller_server`, ...) por nombres mas acordes al TP que se este
haciendo.

Tambien, por default solo se compila una version *debug* sin
optimizar. Si se quiere compilar binarios optimizados
(lo que cmake llama *release*) se puede, solo hay modificar
cmake.

Aprender del ejemplo para saber como extenderlo!

**Importante:** este repositorio **no** incluye pre-commits hooks,
ni scripts adicionales (como correr valgrind).

**Eso esta a cargo de los estudiantes,** tal como fue mostrado
en los tps individuales, recaps y hands-on.

**Instalar Yaml**
```
sudo apt-get install libyaml-cpp-dev
```

**Correr los pre-commits**
```
pre-commit run --all-files
```
** Si quieren ignorar los pre-commits para poder commitear**
```
git commit -m "Mensaje" --no-verify
```

## **Instalación**
Para instalar las dependencias necesarias para el correcto funcionamiento del juego se debe correr el comando:
```
chmod +x download.sh
./download.sh
```

Luego para compilar, correr los tests e instalar lo necesario en el sistema se debe correr el comando:
```
chmod +x install.sh
./install.sh
```