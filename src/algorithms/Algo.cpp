# pragma once

# include "../includes/includes.hpp"



namespace Algo {



    template<class T>
    inline T sum(const std::vector<T> &_this) {
        return std::accumulate(_this.begin(), _this.end(), T());
    }
    
    
    template<class T>
    inline T mean(const std::vector<T> &_this) {
        T out = sum(_this) / (int) _this.size();
        return out;
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
        std::for_each(_this.begin(), _this.end(), [&] (const T1 &val) -> void {
            res.push_back(val.*data_ptr);
        });
        return res;
    }
    
    
    template <typename T1, typename T2>
    T2 mean(const std::vector<T1> &_this, T2 T1::*data_ptr) {
        return mean(getData(_this, data_ptr));
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
