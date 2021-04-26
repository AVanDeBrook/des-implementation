# DES Implementation
School related project (Applied Cryptography) to implement DES in any programming language. The actual DES algorithm is implemented here, but operation modes (CBC, CTR, CFB, ECB) are not.

**Disclaimer**: I am not a cryptographer or a mathematician, just a CS student implementing the DES algorithm for a school project. Feel free to use this code a reference for building your own project, but I maintain no liability for the reliability or security of this code. Feel free to [contact me](https://github.com/AVanDeBrook) with questions about this code.
# Build
Project is configured with [cmake](https://cmake.org/). Use the following to build the project:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
# Run
Build the project first and run one of the following:
```bash
$ ./des
Usage: ./des [encrypt|decrypt] [key] [file|string]
```
# Development Tools
## Build Tools
The following tools/versions are/were used to develop this project:
* CMake:
```
$ cmake --version
cmake version 3.19.7
```
* GCC:
```
$ gcc --version
gcc (GCC) 10.2.1 20201125 (Red Hat 10.2.1-9)
```
* Make:
```
$ make --version
GNU Make 4.3
Built for x86_64-redhat-linux-gnu
```
* GDB:
```bash
$ gdb --version
GNU gdb (GDB) Fedora 10.1-4.fc33
```
## Operating System
* OS: Fedora 33 (Workstation Edition) x86_64
* Kernel: Linux 5.11
