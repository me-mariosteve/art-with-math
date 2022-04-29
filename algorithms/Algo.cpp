# pragma once

# include "../includes/includes.hpp"



namespace Algo {

    
    template<class T, typename UnaryOperation>
    inline void for_each(std::vector<T> &_this, UnaryOperation unary_op ) {
        std::for_each(_this.begin(), _this.end(), unary_op);
    }


    template<class T, typename UnaryOperation>
    inline void transform(std::vector<T> &_this, UnaryOperation unary_op) {
        std::transform(_this.begin(), _this.end(), _this.begin(), unary_op);
    }

    template<class T, typename BinaryOperation>
    inline void transform(std::vector<T> &_this, std::vector<T> other, BinaryOperation binary_op) {
        std::transform(
            _this.begin(), _this.end(),
            _this.begin(), other.begin(),
            binary_op);
    }


    template<class T, typename BinaryOperation, typename R>
    void apply(std::vector<T> &_this, BinaryOperation binary_op, R reduce) {
        std::vector<T> res(_this.size());
        for (auto v1 = _this.begin(); v1 != _this.end(); ++v1) {
            std::vector<T> temp(_this.size()-1);
            for (auto v2 = _this.begin(), tmp = temp.begin(); v2 != _this.end(); ++v2, ++tmp) {
                if (v1 == v2) {
                    --tmp;
                    continue;
                }
                *tmp = binary_op(*v1, *v2);
            }
            *v1 = reduce(temp);
        }
        _this = res;
    }


    template<class T>
    T sum(std::vector<T> _this) {
        T res;
        for (auto it: _this)
            res += it;
        return res;
    }
    
    
    template<class T>
    inline T mean(std::vector<T> _this) {
        return sum(_this) / _this.size();
    }
    

    
    template<class T>
    void update(std::vector<Point<T>> &_this) {
        for_each(_this, [&](Point<T> &_pt) {
            _pt += Point<T>(_pt.sx, _pt.sy);
        });
    }


    template<class T>
    Point<T> meanFull(std::vector<Point<T>> _this) {
        Point<T> res;
        for_each(_this, [&] (Point<T> obj) {
            res.x += obj.x; res.y += obj.y;
            res.sx += obj.sx; res.sy += obj.sy;
            res.radius += obj.radius; res.mass += obj.mass;
            res.color += obj.color;
        });
        res.x /= _this.size(); res.y /= _this.size();
        res.sx /= _this.size(); res.sy /= _this.size();
        res.mass /= _this.size(); res.mass /= _this.size();
        res.color = cv::Vec3b(res.color[0]/_this.size(), res.color[1]/_this.size(), res.color[2]/_this.size());
        return res;
    }
    

};


template<class T>
std::ostream &operator<<(std::ostream &out, std::vector<T> _this) {
    out << "[";
    for_each(_this.begin(), _this.end(), [&](T obj){ out << obj << ", "; });
    return out << "]";
}
