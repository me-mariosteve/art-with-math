# include "../includes/includes.hpp"



namespace PointAlgo {
    
    /**
       Algorithms specific to Point.
     */
    
    
    
    // Like Algo::mean, but applied to every data members of Point.
    template<class T>
    Point<T> meanFull(const std::vector<Point<T>> &_this) {
        std::vector<int> v0, v1, v2;
        v0.reserve(_this.size()); v1.reserve(_this.size()); v2.reserve(_this.size());
        std::for_each(_this.begin(), _this.end(), [&] (const Point<T> &pt) -> void {
            v0.push_back(pt.color[0]);
            v1.push_back(pt.color[1]);
            v2.push_back(pt.color[2]);
        });
        return Point<T>(
            Algo::mean(_this, &Point<T>::x),
            Algo::mean(_this, &Point<T>::y),
            Algo::mean(_this, &Point<T>::sx),
            Algo::mean(_this, &Point<T>::sy),
            Algo::mean(_this, &Point<T>::radius),
            Algo::mean(_this, &Point<T>::mass),
            // Point<T>::color is cv::Vec3b, its fields are equivalent to char so they can't be more than 255.
            //Algo::mean(_this, &Point<T>::color)
            cv::Vec3b(Algo::mean(v0), Algo::mean(v1), Algo::mean(v2))
            );
    }    

    
    // Updates the points coordinates by using their speed.
    template<class T>
    inline void update(std::vector<Point<T>> &_this) {
        std::for_each(_this.begin(), _this.end(), [&] (Point<T> &_pt) {
            _pt.x += _pt.sx;
            _pt.y += _pt.sy;
        });
    }
    

    template<class T, class BinaryOperation, class R>
    inline void doAll(std::vector<Point<T>> &_this, BinaryOperation binary_op, R reduce) {
        Algo::apply(_this, binary_op, reduce);
        update(_this);
    }
    
    
}
