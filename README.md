# triangles3D
Computational task aimed to get intersections of triangles
in 3D space.

![image](img/triangles.jpg)

## Prerequisites
To build you need the following installed:
* Git
* CMake
* Any C++ compiler supported by CMake

## Build
TO build:
1. Clone repo:
```sh
git clone https://github.com/victorbaldin56/triangles3D.git
```
2. Generate build files:
```sh
cmake -S . -B build
```
3. Build:
```sh
cmake --build build
```

## Usage
In `build` subdirectory you will get an executable named `main` which you
will need to run.

Input:
* $N$ - the number of triangles
* $3N$ points, coordinates are single-precision floating point numbers
(type `float` in C++).
