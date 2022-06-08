

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

