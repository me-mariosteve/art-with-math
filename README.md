# cpp-opencv-things

## Description

The goal of this program is to create art with algorithms and calculus.

It uses the [OpenCV](https://opencv.org/) C++ library for the images.

## Structure of the C++ sources files

- [`includes`](includes) contains includes included in all my C++ file.
- [`algorithm`](algorithm) contains various algorithms, often to use with `std::vector`.
- [`dataclass`](dataclass) contains classes to store data. Actually there is only one, `Point`.

## Bugs

I fixed the functions in [`algorithm/Algo.cpp`](algorithm/Algo.cpp), the points are correctly generated with `Generator::r2` and updated with `Algo::apply`.
The only thing that doesn't work is the output.
The arguments are passed to [`draw`](algorithm/cv.cpp), then even if there are the right values nothing is written to the video after the first frame.

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

## Tools

If you have [cppcheck](https://cppcheck.sourceforge.io/) installed, the configuration file is [`project.cppcheck`](project.cppcheck). The directory [`cppcheck.d`](cppcheck.d) will contains the produced files.
I made a small script to call it more easily from command line: [`./cppcheck [optionnal cppcheck args]`](cppcheck)
