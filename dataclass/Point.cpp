# pragma once

# include "../includes/includes.hpp"


template<class T>
class Point {
  
public:
    T x=0, y=0, sx=0, sy=0;
    T radius=1, mass=1;
    cv::Vec3b color=(0, 0, 0);


    Point<T>() {}
    
    Point<T>(T x, T y):
        x(x), y(y)
        {}
    
    Point<T>(T x, T y, T sx, T sy):
        x(x), y(y), sx(sx), sy(sy)
        {}

    Point<T>(T x, T y, T sx, T sy, T radius, T mass):
        x(x), y(y), sx(sx), radius(radius), mass(mass)
        {}

    Point<T>(T x, T y, T sx, T sy, T radius, T mass, cv::Vec3b color):
        x(x), y(y), sx(sx), radius(radius), mass(mass), color(color)
        {}
    
    explicit Point<T>(cv::Vec3b color):
        color(color)
        {}

    Point<T>(T x, T y, cv::Vec3b color):
        x(x), y(y), color(color)
        {}

    
    
# define OP(sym)                                        \
    inline Point<T> operator sym (const Point<T> &other) {     \
        return Point<T> (x sym other.x, y sym other.y); \
    }                                                   \
    inline Point<T> operator sym##= (const Point<T> &other) {  \
        return (*this = *this sym other);               \
    }                                                   \
        inline Point<T> operator sym (const T &other) {        \
            return Point<T> (x sym other, y sym other); \
        }                                               \
        inline Point<T> operator sym##= (const T &other) {     \
            return (*this = *this sym other);           \
        }
    OP(+);
    OP(-);
    OP(*);
    OP(/);
# undef OP
    
    
    inline T dist(const Point<T> &other) {
        return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
    }

    
};


template<class T>
inline std::ostream &operator<<(std::ostream &out, const Point<T> &_this) {
    return out << typeid(T).name() << "(" << _this.x << "," << _this.y << ")";
}


// predef for some types
using PointI = Point<int>;
using PointS = Point<short>;
using PointL = Point<long>;
using PointF = Point<float>;
using PointD = Point<double>;
