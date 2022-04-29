# cpp-opencv-things

## Description

The goal of this program is to create art with algorithms and calculus.

It uses the [OpenCV](https://opencv.org/) C++ library for the images.

## Structure

- [`includes`](includes) contains includes included in all my C++ file.
- [`algorithm`](algorithm) contains various algorithms, often to use with `std::vector`.
- [`dataclass`](dataclass) contains classes to store data. Actually there is only one, `Point`.

## Issues

seen with valgrind:

- segfault after main when videoOutput is released
- something's wrong when it's created, but I don't know why

I don't trust Algo::apply, it may be coupable

## Build

To build the project, you must have CMake, a C++ compiler and OpenCV installed.

When the dependencies are installed, you have 2 choices:

1. Run my shell script [`make`](make), which do everything for you:
   ```bash
   ./make
   ```

   It creates the cmake configuration files in `build/` then build the project.

   The produced executables are also put in `build/`:
   - [`main.cpp`](main.cpp) -> `build/project`

2. Run yourself the commands to build the project:
   ```bash
   cd '<directory where CMake will put the files>'
   cmake '<path to the root directory of the repo>'
   make
   ```
