# cpp-opencv-things

## Description

The goal of this program is to create art with algorithms and calculus.

It uses the [OpenCV](https://opencv.org/) C++ library for the images.

## Structure of the C++ sources files

All the C++ source files are in the directory [`src`](src).

- [`main.cpp`](src/main.cpp) main.cpp with the `main` definition.
- [`includes`](src/includes) contains includes included in every C++ file.
- [`algorithm`](src/algorithm) contains algorithms I made.
- [`data`](src/data) contains stuff for storing and using various data
  like the class `Point` and `namespace Math` for mathematic constants.

## What it does

I have put an example code in [`main.cpp`](src/main.cpp) which generate points
then applies mathematic formulas to it, and write the result to a video file `out.avi`.

## Issues

Everything should work as expected.
I already said that but this time I've checked.

## Build

To build the project, you must have [CMake](https://cmake.org), a C++ compiler and [OpenCV 4.5.5](https://github.com/opencv/opencv/tree/4.5.5) installed.

When the dependencies are installed, you have 2 choices:

1. Run my shell script [`make.sh`](make.sh) which do everything for you:
   ```bash
   ./make.sh
   ```

   It creates the cmake configuration files in `build/` then build the project.

   The produced executables are also put in `build/`:
   - [`main.cpp`](src/main.cpp) -> `build/project`

2. Run yourself the commands to build the project:
   ```bash
   cd '<directory where CMake will put the files>'
   cmake '<path to the root directory of the repo>'
   make
   ```

3. You can remove the files created by CMake and my program with the script [`clean.sh`](clean.sh):
  ```bash
  ./clean.sh
  ```

## Tools

If you have [cppcheck](https://cppcheck.sourceforge.io/) installed, the configuration file is
[`project.cppcheck`](project.cppcheck). The directory [`cppcheck.d`](cppcheck.d) will contains the produced files.
I made a small script [`cppcheck.sh`](cppcheck.sh) to use it from command line:
```bash
./cppcheck.sh [optionnal arguments for cppcheck]`
```
