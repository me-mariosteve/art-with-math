# pragma once

# include "../includes/includes.hpp"



namespace Algo {


    // std::for_each, but simplified
    template<class T, class UnaryOperation>
    void for_each(std::vector<T> &_this, UnaryOperation unary_op ) {
        for (auto it: _this)
            unary_op(it);
    }


    // same for std::transform
    // unary operation
    template<class T, class UnaryOperation>
    inline auto transform(std::vector<T> &_this, UnaryOperation unary_op) {
        return std::transform(_this.begin(), _this.end(), _this.begin(), unary_op);
    }
    
    // binary operation
    template<class T, class BinaryOperation>
    inline auto transform(std::vector<T> &_this, std::vector<T> &other, BinaryOperation binary_op) {
        return std::transform(
            _this.begin(), _this.end(),
            _this.begin(), other.begin(),
            binary_op);
    }


    template<class T, class BinaryOperation, class R>
    void apply(std::vector<T> &_this, BinaryOperation binary_op, R reduce) {
        std::vector<T> res;
        res.reserve(_this.size());
        for (T &v1: _this) {
            std::vector<T> temp;
            temp.reserve(_this.size()-1);
            for (T &v2: _this)
                if (&v1 != &v2)
                    temp.push_back(binary_op(v1, v2));
            res.push_back(reduce(temp));
        }
        _this = res;
    }


    template <typename T1, typename T2>
    std::vector<T2> getData(const std::vector<T1> &_this, T2 T1::*data_ptr) {
        std::vector<T2> res;
        res.reserve(_this.size());
        for (const T1 &val: _this)
            res.push_back(val.*data_ptr);
        return res;
    }
    
    
    template<class T>
    inline T sum(const std::vector<T> &_this) {
        return std::accumulate(_this.begin(), _this.end(), T());
    }
    
    
    template<class T>
    inline T mean(const std::vector<T> &_this) {
        T out = sum(_this) / (int) _this.size();
        return out;
    }


    // Algorithms specific to the class Point
    
    // Updates the points coordinates by using their speed.
    template<class T>
    inline void update(std::vector<Point<T>> &_this) {
        for_each(_this, [&] (Point<T> &_pt) {
            _pt += Point<T>(_pt.sx, _pt.sy);
        });
    }


    // Like Algo::mean, but applied to every data members of Point.
    template<class T>
    Point<T> meanFull(const std::vector<Point<T>> &_this) {
        return Point<T>(
            mean(getData(_this, &Point<T>::x)),
            mean(getData(_this, &Point<T>::y)),
            mean(getData(_this, &Point<T>::sx)),
            mean(getData(_this, &Point<T>::sy)),
            mean(getData(_this, &Point<T>::radius)),
            mean(getData(_this, &Point<T>::mass)),
            mean(getData(_this, &Point<T>::color))
            );
    }
    

};


// Print vector in python style
template<class T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &_this) {
    out << "[";
    for (T obj: _this)
        out << obj << ",";
    return out << "]";
}
