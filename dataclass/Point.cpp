# ifndef POINT_CPP_DEFINED
# define POINT_CPP_DEFINED

# include "../includes/includes.hpp"


template<typename T>
class Point {
  
public:
    T x, y, sx, sy;
    T mass, radius;
    cv::Vec3b color;
    
    Point<T>(T x = T(), T y = T(), T sx = T(), T sy = T(),
             T mass = T(), T radius = T(),
             cv::Vec3b color=(0, 0, 0)
        ): x(x), y(y), sx(sx), sy(sy),
           mass(mass), radius(radius),
           color(color)
        {}
    
    
# define OP(sym) inline Point<T> operator sym (Point<T> other) {        \
        return Point<T> (x sym other.x, y sym other.y); }               \
    inline Point<T> operator sym##= (Point<T> other) {                  \
        return (*this = *this sym other); }
    OP(+);
    OP(-);
    OP(*);
    OP(/);
# undef OP
    
# define OP(sym) inline Point<T> operator sym (T other) {       \
        return Point<T> (x sym other, y sym other); }           \
    inline Point<T> operator sym##= (T other) {                 \
        return (*this = *this sym other); }
    OP(+)
    OP(-)
    OP(*)
    OP(/)
# undef OP
    
        inline T dist(Point<T> other) {
        return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
    }

    
};


template<typename T>
inline std::ostream &operator<<(std::ostream &out, Point<T> _this) {
    return out << typeid(T).name() << "(" << _this.x << ", " << _this.y << ")";
}



# ifndef NO_DATA_SERIALIZATION

template<typename T>
Data &operator<<(Data &out, Point<T> &_this) {
    return out                                   \
        << _this.x << ","                        \
        << _this.y << ","                        \
        << _this.sx << ","                       \
        << _this.sy << ";";
}


template<typename T>
Data &operator>>(Data &in, Point<T> &_this) {
    return in                                 \
        >> _this.x >> Data::skip::prop        \
        >> _this.y >> Data::skip::prop        \
        >> _this.sx >> Data::skip::prop       \
        >> _this.sy >> Data::skip::obj;
}

# endif /* NO_DATA_SERIALIZATION */



# ifndef NO_OPENCV

template<typename T>
void draw(Point<T> _this, cv::Mat mat) {
    for (T y = -_this.radius; y <= _this.radius && y < mat.cols; y++) {
        if (y < 0) continue;
        for (T x = -_this.radius; x <= _this.radius && x < mat.rows; x++) {
            if (x < 0) continue;
            mat.at<cv::Vec3b>(_this.x+x, _this.y+y) = _this.color;
        }
    }
}

# endif /* NO_OPENCV */



# endif /* POINT_CPP_DEFINED */
