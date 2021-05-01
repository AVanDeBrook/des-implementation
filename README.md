# DES Implementation
School related project (Applied Cryptography) to implement DES in any programming language. The DES algorithm is implemented here, but operation modes (CBC, CTR, CFB, ECB) are not.

The entire algorithm is implemented, however the fundamental condition that `Dec(Enc(k, m)) = m` is not met, which means there is a problem somewhere in my implementation that I have not been able to find.

**Disclaimer**: I am not a cryptographer or a mathematician, just a CS student implementing the DES algorithm for a school project. Feel free to use this code a reference for building your own project, but I maintain no liability for the reliability or security of this code. However, feel free to [contact me](https://github.com/AVanDeBrook) (DM me on Twitter or email me) with questions about this repo.

Example output:
```
$ ./des
Key:            3030303030303030
Plaintext:      3030303030303030
Encrypted data: 1c5e5088b5854b52
Decrypted data: 220302fc939eecc3
```
This is the result of running the program with the hardcoded values seen in `main.c`. As you can see, the decrypted data does not match the plaintext. I did atomic testing on all parts of the algorithm to verify their correctness, but something is not working upon merging everything together (obviously).

There is a working argument parser and corresponding command line syntax, however, I made the decision that debugging would be easier with a hardcoded key and plaintext, then run the encryption and decryption functions on that data for testing.

If you are interested in trying out the command line bit of the program, just uncomment the code at the top of `main` in `main.c`, recompile and run.

Regardless of the project's functionality, I did learn a lot about encryption algorithms, how to go about building them, and what variations in implementations make them secure and/or insecure. I also learned a bit about the history of DES, for example, why the initial and final permutation tables were selected and used. I did have fun building this project (despite the pain associated with debugging C), although I am admittedly disappointed that the final version does not work. I'm sure it would have been slightly more enjoyable if I wasn't also working on 3 or 4 other projects and their reports/presentations, but this was still one of the more enjoyable projects of the semester.
# Build
Project is configured with [cmake](https://cmake.org/). Use the following to build the project:
```bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

For building the project in debug mode (for use with GDB or some other debugger):
```bash
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
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
