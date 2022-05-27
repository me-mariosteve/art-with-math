# pragma once

# include "../includes/includes.hpp"



namespace Algo {



    template<class T>
    inline T sum(const Array<T> &_this) {
        T res = T();
        _this.foreach([&] (const T &v) -> void {
            res = res + v;
        });
        return res;
    }
    
    
    template<class T>
    inline T mean(const Array<T> &_this) {
        T out = sum(_this) / (int) _this.size;
        return out;
    }
    


    template<class T, class BinaryOperation, class R>
    void apply(Array<T> &_this, BinaryOperation binary_op, R reduce) {
        Array<T> res( _this.size);
        _this.foreach_vi([&] (const T &v1, const size_t &i) -> void {
            Array<T> temp(_this.size-1);
            size_t temp_id = 0;
            _this.foreach_vi([&] (const T &v2, const size_t &j) -> void {
                if (i != j)
                    temp[temp_id++] = binary_op(v1, v2);
            });
            res[i] = reduce(temp);
        });
        _this = res;
    }

    
    
    template <class T1, class T2>
    Array<T2> getData(const Array<T1> &_this, T2 T1::*data_ptr) {
        Array<T2> res(_this.size);
        _this.foreach_vi([&] (const T1 &val, const size_t &i) {
            res[i] = val.*data_ptr;
        });
        return res;
    }
    
    
    template <template <class _T> class Container, class T1, class T2>
    T2 mean(const Container<T1> &_this, T2 T1::*data_ptr) {
        return mean(getData(_this, data_ptr));
    }
    
    
};



// Print vector in python style
template<class T>
std::ostream &operator<<(std::ostream &out, const std::vector<T> &_this) {
    out << "[";
    for (const T &obj: _this)
        out << obj << ",";
    return out << "]";
}

// Same with Array
template<class T>
std::ostream &operator<<(std::ostream &out, const Array<T> &_this) {
    out << "[";
    _this.foreach([&] (const T &val) {
        out << val << ",";
    });
    return out << "]";
}
