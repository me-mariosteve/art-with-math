# pragma once

# include "../includes/includes.hpp"



namespace Algo {


    // std::for_each, but simplified
    template<class T, typename UnaryOperation>
    inline void for_each(std::vector<T> &_this, UnaryOperation unary_op ) {
        std::for_each(_this.begin(), _this.end(), unary_op);
    }


    // same for std::transform
    // unary operation
    template<class T, typename UnaryOperation>
    inline void transform(std::vector<T> &_this, UnaryOperation unary_op) {
        std::transform(_this.begin(), _this.end(), _this.begin(), unary_op);
    }
    
    // binary operation
    template<class T, typename BinaryOperation>
    inline void transform(std::vector<T> &_this, std::vector<T> &other, BinaryOperation binary_op) {
        std::transform(
            _this.begin(), _this.end(),
            _this.begin(), other.begin(),
            binary_op);
    }


    template<class T, typename BinaryOperation, typename R>
    void apply(std::vector<T> &_this, BinaryOperation binary_op, R reduce) {
        std::vector<T> res(_this.size());
        for (
            auto v1 = _this.begin();
            v1 != _this.end();
            ++v1) {
            std::vector<T> temp(_this.size()-1);
            for (
                auto v2 = _this.begin();
                v2 != _this.end();
                ++v2) {
                if (v1 == v2) continue;
                temp.push_back(binary_op(*v1, *v2));
            }
            res.push_back(reduce(temp));
        }
        _this = res;
    }


    /*
    template <typename T, typename F>
    auto getData(const std::vector<T>& _this, F data_fn) {
        std::vector<std::invoke_result_t<F, const T&>> res;
        res.reserve(_this.size());
        for (const auto& obj : _this)
            res.push_back(std::invoke(data_fn, obj));
            return res;
    }
    */
    
    
    template<class T>
    T sum(std::vector<T> &_this) {
        T res;
        for (auto it: _this)
            res += it;
        return res;
    }
    
    
    template<class T>
    inline T mean(std::vector<T> &_this) {
        return sum(_this) / (int) _this.size();
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
    Point<T> meanFull(std::vector<Point<T>> &_this) {
        Point<T> res(0, 0, 0, 0, 0, 0, cv::Vec3b(0, 0, 0));
        for_each(_this, [&] (Point<T> obj) {
            res.x += obj.x; res.y += obj.y;
            res.sx += obj.sx; res.sy += obj.sy;
            res.radius += obj.radius; res.mass += obj.mass;
            res.color += obj.color;
        });
        res.x /= _this.size(); res.y /= _this.size();
        res.sx /= _this.size(); res.sy /= _this.size();
        res.radius /= _this.size(); res.mass /= _this.size();
        res.color = res.color/(int) _this.size();
        return res;
    }
    

};


// Print out in python style
template<class T>
std::ostream &operator<<(std::ostream &out, std::vector<T> _this) {
    out << "[";
    Algo::for_each(_this, [&](T obj){ out << obj << ", "; });
    return out << "]";
}
