# pragma once


//# define NO_DATA_SERIALIZATION
//# define NO_OPENCV


// STL
# include <iostream> // for basic I/O on the terminal
# include <fstream> // for I/O with files
# include <string> // for operations on std::strings
# include <cmath> // for various math functions that could be used
# include <vector> // for std::vector
# include <ctime> // for sleep
# include <functional> // for std::invoke

// Linux library
# include <unistd.h>

# ifndef NO_OPENCV
// OpenCV library
# include <opencv2/opencv.hpp>
# endif /* NO_OPENVC */

# include "user_includes.hpp"
