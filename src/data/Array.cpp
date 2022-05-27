# include "../includes/includes.hpp"



template<class T>
class Array {
    
public:
    
    const size_t size;
    T *ptr;
    

    Array<T> (const size_t &size):
        size(size), ptr(static_cast<T *> (malloc( sizeof(T) * size )))
        {}
    
    Array<T> (Array<T> &other):
        size(other.size), ptr(other.ptr)
        {}
    
    Array<T> &operator=(Array<T> &other) {
        for (size_t i = 0; i < size; i++)
            ptr[i] = other.ptr[i];
        return *this;
    }
    
    
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
