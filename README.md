# HTTP Routing Library for POCO

Extension library for [libhttproute](https://github.com/mfreiholz/libhttproute-cpp) to provide bindings for POCO's HTTP Server request handlers.

## Build

All dependencies will be downloaded and build by CMake, what makes it very easy to build.
Note that multi-target builds (Visual Studio) are not supported.
You always have to specify the `-DCMAKE_BUILD_TYPE=` argument with `Release` or `Debug` as value.

### Windows

```bash
mkdir build
cd build
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release ..
nmake
```

### Linux (64-Bit)

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Legal

The project uses a dual-licensing system.

It is free for all non-commercial/non-profit use cases.
If you want to use the library in a commercial/profit use case you should contact the project owner (info (at) mfreiholz (dot) de).
