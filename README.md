# physics

## Description
    
The goal of this program is to create art by using physics and mathematics.

It uses the [OpenCV](https://opencv.org/) C++ library to create images.

## Structure of the C++ sources files

All the C++ source files are in the directory [`src`](src).

- [`main.cpp`](src/main.cpp) main.cpp with the `main` definition.
- [`includes`](src/includes) contains includes included in every C++ file.
- [`algorithm`](src/algorithm) contains algorithms I made.
- [`data`](src/data) contains stuff for storing and using various data, the classes `Point` and `Array` and the namespace `Math`.

## Usage

Here is the program usage:

```text
Usage:
  ./build/project
    [-h | --help] [-u | --usage] [-L | --license]
    [{-o | --output} FILE]
    [{-w | --width} WDITH] [{-h | --height} HEIGHT] [{-s | --size} WIDTH HEIGHT]
    [--fps FPS] [{-l | --length} LENGTH]
    [{-psx | --point-sx} SX] [{-psy | --point-sy} SY]
    [{-pr | --point-radius} RADIUS] [{-pm | --point-mass} MASS]
    [{-pc | --point-color} R G B]

Warning: short options cannot be combined into one, for example '-o -s' is not '-os'.

Options description, with default value(s) in brackets:

  -h, --help      Show the help for this program.
  -u, --usage     Show a shorter help message.
  -L, --license   Show the license.

  -o, --output FILE         Write the video to FILE. [./out.avi]
  -w, --width WIDTH         Set the video width. [1920]
  -h, --height HEIGHT       Set the video height. [1080]
  -s, --size WIDTH HEIGHT   Set the video width and height. [1920] [1080]
  --fps FPS                 Set the frames per seconds. [10]
  -l, --length LENGTH       Set the number of frames in the video. [300]

  -psx, --point-sx SX          Set the x points speed at start. [0]
  -psy, --point-sy SY          Set the y points speed at start. [0]
  -pr, --point-radius RADIUS   Set the points radius. [1]
  -pm, --point-mass MASS       Set the points mass. [10]
  -pc, --point-color R G B     Set the points color (decimal). [255 255 255]
```

## Issues

Everything should work as expected.
I already said that but this time I've checked.

I have a [new problem](https://github.com/me-mariosteve/physics/blob/master/src/algorithms/Generator.cpp#L73) (not really important but really strange)

## Build

To build the project, you must have [CMake](https://cmake.org), a C++ compiler and [OpenCV at least 4.5.5](https://github.com/opencv/opencv/tree/4.5.5) installed.

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
