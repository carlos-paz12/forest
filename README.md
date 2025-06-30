# forest

## Introduction
**forest** is a implementation of AVL and Black-Red self-balancing binary search tree, using C++ programming language, to stores `User` structs.

The project supports classic operations like:
- Insertion
- Search
- Removal
- Visual representation (ASCII tree with optional color)


## Authors
This project was developed by:
- Carolina Nunes (<carolina.nunes.110@ufrn.edu.br>);
- Diego Luan (<luan.souza.134@ufrn.edu.br>);
- Flávio Júnior (<flavinhoj78@gmail.com>);
- Carlos Paz (<carlos.paz.707@ufrn.edu.br>);
- Leandro Andrade (<leandro.andrade.401@ufrn.edu.br>);
- Lucas Graziano (<lucasgraziano7@gmail.com>).

As part of the _Estrutura de Dados Básicas II_ course at **UFRN**.

## Compiling and Running
### Using cmake
> [!note]
> This method requires CMake (>= 3.22.1) to be installed on your system. CMake is a cross-platform build system generator used to configure and compile the project. If it's not already installed, you can install it using your system’s package manager (e.g., `sudo apt install cmake` on Debian/Ubuntu or `brew install cmake` on macOS).

Once CMake is set up, follow the steps:

1. Clone this repository:

```bash
git clone https://github.com/carlos-paz12/forest
```

2. Navigate to the project directory:

```bash
cd forest
```

3. Compile and build the program using `cmake`:

```bash
cmake -S . -B build
cmake --build build
```

4. Run:

```bash
./build/forest
```

### Without cmake

Alternatively, you can compile this project without cmake, manually using C++ compilers, such as c++ or clang, to do so

1. Clone this repository:

```bash
git clone https://github.com/carlos-paz12/forest
```

2. Navigate to the project directory:

```bash
cd forest
```

3. Create a `build` directory:

```bash
mkdir build
```

4. Compile with `g++`:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 \
    src/main.cpp \
    src/forest/trees/avl/avl.cpp \
    src/forest/trees/black_red/black_red.cpp \
    src/forest/utils/rotations.cpp \
    -I include \
    -o build/forest
```

or `clang++`

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic -O2 \
    src/main.cpp \
    src/forest/trees/avl/avl.cpp \
    src/forest/trees/black_red/black_red.cpp \
    src/forest/utils/rotations.cpp \
    -I include \
    -o build/forest
```

5. Run:

```bash
./build/forest
```

---

&copy; DIMAp | Departamento de Informática e Matemática Aplicada - 2025
