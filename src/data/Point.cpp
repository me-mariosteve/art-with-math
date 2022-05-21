# pragma once

# include "../includes/includes.hpp"


template<class T>
class Point {
  
public:

    typedef Point<T> _Pt;
    typedef const T &const_ref;
    
    T x=0, y=0, sx=0, sy=0;
    T radius=1, mass=1;
    cv::Vec3b color=(0, 0, 0);


    Point<T>() {}
    
    Point<T>(const_ref x, const_ref y):
        x(x), y(y)
        {}
    
    Point<T>(const_ref x, const_ref y, const_ref sx, const_ref sy):
        x(x), y(y), sx(sx), sy(sy)
        {}

    Point<T>(const_ref x, const_ref y, const_ref sx, const_ref sy, const_ref radius, const_ref mass):
        x(x), y(y), sx(sx), sy(sy), radius(radius), mass(mass)
        {}

    Point<T>(const_ref x, const_ref y, const_ref sx, const_ref sy, const_ref radius, const_ref mass, const cv::Vec3b &color):
        x(x), y(y), sx(sx), sy(sy), radius(radius), mass(mass), color(color)
        {}
    
    explicit Point<T>(const cv::Vec3b &color):
        color(color)
        {}

    Point<T>(const_ref x, const_ref y, const cv::Vec3b &color):
        x(x), y(y), color(color)
        {}

    
    
# define OP(sym)                                                        \
    inline _Pt operator sym (const _Pt &other) {                        \
        return _Pt(x sym other.x, y sym other.y);                       \
    }                                                                   \
    inline _Pt operator sym##= (const _Pt &other) {                     \
        return (*this = *this sym other);                               \
    };                                                                  \
    inline _Pt operator sym (const_ref other) {                         \
        return _Pt (x sym other, y sym other);                          \
    }                                                                   \
    inline T operator sym##= (const T &other) {                         \
        return (*this = *this sym other);                               \
    }
    OP(+);
    OP(-);
    OP(*);
    OP(/);
# undef OP

    inline T length(void) {
        return sqrt(x*x + y*y);
    }
    
    inline T dist(const _Pt &other) {
        return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
    }

    
};


template<class T>
inline std::ostream &operator<<(std::ostream &out, const Point<T> &_this) {
    return out << typeid(T).name() << "(" << _this.x << "," << _this.y << ")";
}


template<class T>
inline T sin(Point<T> &_this) {
    return _this.x/_this.length();
}
template<class T>
inline T cos(Point<T> &_this) {
    return _this.y/_this.length();
}

template<class T>
inline T sin(Point<T> &_this, Point<T> &other) {
    return (other.x-_this.x)/_this.dist(other);
}
template<class T>
inline T cos(Point<T> &_this, Point<T> &other) {
    return (other.y-_this.y)/_this.dist(other);
}


// predef for some types
using PointI = Point<int>;
using PointS = Point<short>;
using PointL = Point<long>;
using PointF = Point<float>;
using PointD = Point<double>;
