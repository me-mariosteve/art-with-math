# pragma once


//# define NO_DATA_SERIALIZATION
//# define NO_OPENCV


// STL
# include <iostream> // for basic I/O on the terminal
# include <string> // for operations on std::strings
# include <vector> // for std::vector
# include <fstream> // for I/O with files
# include <filesystem> // for interacting with the filesystem, eg rename, exists
# include <cmath> // for various math functions that could be used
# include <ctime>
# include <functional>
# include <numeric>


// Linux library
# include <unistd.h>

# ifndef NO_OPENCV
// OpenCV library
# include <opencv2/opencv.hpp>
# endif /* NO_OPENVC */

# include "user_includes.hpp"
