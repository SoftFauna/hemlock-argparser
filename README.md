# hemlock-argparser

A generic arguement parser written for HEMLOCK.

## Build

### CMake build

Build requires:
- CMake >= 3.10

~~~
mkdir build
cd build
cmake ..
cmake --build .
./src/hemlock_argparser_ex
~~~

### Meson build

Build requires:
- Meson

~~~
meson setup build
cd build
ninja
sudo ninja install
./src/example/hemlock_argparser_ex
~~~

## License

[MIT License](/LICENSE)
Copyright (c) 2025 [The SoftFauna Team](/AUTHORS.md)
