# ifndef ARRAY_CPP_DEFINED
# define ARRAY_CPP_DEFINED

# include "../includes/includes.hpp"


template<typename T>
class Array {
	
public:

    typedef T (*Func1) (T);
    typedef T (*Func2) (T, T);
    typedef void (*Proc1) (T);
    typedef void (*Proc2) (T, T);
    typedef T (*FReduce) (Array<T>);
	
    size_t size;
    T *ptr;
    
    Array<T>(void): size(0), ptr(NULL) {}
    
    Array<T>(size_t size): size(size) {
        ptr = (T *) malloc(sizeof(T) * size);
    }

    Array<T>(size_t size, T tmp): size(size) {
        ptr = (T *) malloc(sizeof(T) * size);
        for (size_t id = 0; id < size; id++) {
            ptr[id] = tmp;
        }
    }
    
    inline T &operator[](size_t id) {
        return ptr[id];
    }

    inline const T &operator[](size_t id) const {
        return ptr[id];
    }

    void free(void) {
        delete ptr;
        size = 0;
    }
    
    void copy(Array *target) {
        target -> free();
        target -> size = size;
        target -> ptr = (T *) malloc(sizeof(T) * size);
        for (int id = 0; id < size; id++)
            target -> ptr[id] = ptr[id];
    }

    template<typename F>
    void map(F func) {
        for (size_t id = 0; id < size; id++) 
            ptr[id] = func(ptr[id]);
    }

    template<typename F, typename R>
    void map(F func, R reduce) {

        Array<T> _new(size);
        for (int i = 0; i < size; i++) {
            Array<T> _id(size);
            for (int j = 0; j < size; j++)
                _id[j] = func(ptr[i], ptr[j]);
            _new.ptr[i] = reduce(_id);
        }
        _new.copy(this);
    }
    
    
};


template<typename T>
std::ostream &operator<<(std::ostream &out, Array<T> _this) {
    out << "[";
    for (int id = 0; id < _this.size - 1; id++)
        out << _this.ptr[id] << ", ";
    _this.size && out << _this.ptr[_this.size-1];
    return out << "]";
}



# ifndef NO_DATA_SERIALIZATION

template<typename T>
Data &operator<<(Data &out, Array<T> &_this) {
    /*
     * Items are separated with a semicolon ';'.
     * Items' properties must be separated with a comma ','.
     */
    out << _this.size << ";";
    for (int id = 0; id < _this.size; id++) {
        out << _this[id];
    }
    return out << "\n";
}


template<typename T>
Data &operator>>(Data &in, Array<T> &_this) {
    _this.free();
    in >> _this.size;
    Data::skip::obj;
    _this.ptr = (T *) malloc(_this.size * sizeof(T));
    for (int id = 0; id < _this.size; id++)
        in >> _this[id];
    in >> Data::skip::array;
    return in;
}

# endif /* NO_DATA_SERIALIZATION */



# ifndef NO_OPENCV

template<typename T>
void draw(Array<T> _this, cv::Mat mat) {
    for (size_t id = 0; id < _this.size; id++) {
        draw(_this[id], mat);
    }
}

# endif /* NO_OPENCV */



# endif /* ARRAY_CPP_DEFINED */
