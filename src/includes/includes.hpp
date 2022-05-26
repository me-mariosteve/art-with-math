# pragma once


//# define NO_DATA_SERIALIZATION
//# define NO_OPENCV


// STL
# include <iostream> // for basic I/O on the terminal
# include <string> // for std::string
# include <vector> // for std::vector
# include <fstream> // for I/O with files
# include <filesystem> // for interacting with the filesystem, eg rename, exists
//# include <cmath> // for various math functions that could be used
# include <chrono> // for time in micro, nanoseconds
# include <numeric> // std::accumulate

// Linux library
//# include <unistd.h>

# ifndef NO_OPENCV
// OpenCV library
# include <opencv2/opencv.hpp>
# endif /* NO_OPENVC */

# include "user_includes.hpp"
