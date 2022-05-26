# include "../includes/includes.hpp"



template<class T>
class Array {
    
public:
    
    size_t size;
    T *ptr;
    
    Array<T> (const size_t &size):
        size(size), ptr(static_cast<T *> (malloc( sizeof(T) * size )))
        {}
    
    
    inline T &operator[](const size_t &index) {
        return ptr[index];
    }


    template<class F>
    void foreach(F op) {
        for (size_t i = 0; i < size; i++)
            op(ptr[i]);
    }
    
    template<class F>
    void foreach_i(F op) {
        for (size_t i = 0; i < size; i++)
            op(i);
    }

    template<class F>
    void foreach_vi(F op) {
        for (size_t i = 0; i < size; i++)
            op(ptr[i], i);
    }

};
