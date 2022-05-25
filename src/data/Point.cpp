# pragma once

# include "../includes/includes.hpp"


template<class T>
class Point {
  
public:

    typedef T value_type;
    typedef cv::Point_<value_type> _Pt;
    typedef const value_type &const_ref;
    
    T x = T(), y = T(), sx = T(), sy = T(), radius = T(), mass = T();
    cv::Vec3b color=(0, 0, 0);


    Point<T>() {}
    
    Point<T>(const T &x, const T &y, const T &sx = T(), const T &sy = T()):
        x(x), y(y), sx(sx), sy(sy)
        {}
    
    Point<T>(const T &x, const T &y, const T &sx, const T &sy,
             const T &radius, const T &mass,
             const cv::Vec3b color=cv::Vec3b(0, 0, 0)
        ): x(x), y(y), sx(sx), sy(sy), radius(radius), mass(mass), color(color)
        {}
    
    explicit Point<T>(const cv::Vec3b &color):
        color(color)
        {}

    Point<T>(const T &x, const T &y, const cv::Vec3b &color):
        x(x), y(y), color(color)
        {}

    Point<T>(const _Pt &other):
        x(other.x), y(other.y), sx(other.sx), sy(other.sy),
        radius(other.radius), mass(other.mass), color(other.color)
        {}
    
    
    inline T length(void) {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    inline T speed(void) {
        return sqrt(pow(sx, 2) + pow(sy, 2));
    }
    
    inline T dist(const _Pt &other) {
        return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
    }

    inline T surface_Distance(const _Pt &other) {
        return dist(other) - radius - other.radius;
    }

    
};


// predef for some types
using PointI = Point<int>;
using PointS = Point<short>;
using PointL = Point<long>;
using PointF = Point<float>;
using PointD = Point<double>;


# define OP(sym)                                                        \
    template<class T>                                                   \
    inline Point<T> operator sym (const Point<T> &_this, const Point<T> &other) { \
        return Point<T>(_this.x sym other.x, _this.y sym other.y);      \
    }                                                                   \
    template<class T>                                                   \
    inline Point<T> &operator sym##= (const Point<T> &_this, const Point<T> &other) { \
        return (_this = _this sym other);                               \
    };                                                                  \
    template<class T>                                                   \
    inline Point<T> operator sym (const Point<T> &_this, const T &other) { \
        return Point<T>(_this.x sym other, _this.y sym other);          \
    }                                                                   \
    template<class T>                                                   \
    inline Point<T> operator sym##= (const Point<T> &_this, const T &other) { \
        return (_this = _this sym other);                               \
    }
OP(+);
OP(-);
OP(*);
OP(/);
# undef OP


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



template<class T>
inline std::ostream &operator<<(std::ostream &out, const Point<T> &_this) {
    return out << typeid(T).name() << "(" << _this.x << "," << _this.y << ")";
}
