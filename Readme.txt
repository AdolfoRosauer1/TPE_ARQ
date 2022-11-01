

Environment setup:
1- Install the following packages before building the Toolchain and Kernel:

nasm qemu gcc make docker

For the folowing instructions one must first setup Docker:
  i-    user@linux:$  docker pull agodio/itba-so:1.0
  ii-   user@linux:$  docker run -v ${PWD}:/root --security-opt seccomp:unconfined -ti agodio/itba-so:1.0
  iii-  now from the docker GUI complete the rest of Instructions

2- Build the Toolchain

Execute the following commands on the project directory:

  user@linux:$ cd Toolchain
  user@linux:$ make all

3- Build the Kernel

From the project directory run:

  user@linux:$ make all

4- Run the kernel

From the project directory run:

  user@linux:$ ./run.sh

En caso de no funcionar apropiadamente el audio en el sistema operativo debido a errores en los parametros del qemu
pruebe cambiar dentro de run.sh el parametro
  -soundhw pcspk
y reemplazarlo por
  -audiodev <driver>,id=audio0 -machine pcspk-audiodev=audio0
donde driver hace referencia al controlador de sonido adecuado para la configuracion de sistema utilizada
las opciones tipicas recomendadas son:
  coreaudio (Mac)
  dsound,pa (Windows)
  sld,alsa (Linux)
aunque puede ser que su configuracion utilice un driver que no este presente en la lista
para mas informacion recomendamos leer la documentacion de qemu en: https://qemu.readthedocs.io/en/latest/system/qemu-manpage.html


