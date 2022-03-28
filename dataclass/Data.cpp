# ifndef DATA_CPP_DEFINED
# define DATA_CPP_DEFINED

# include <fstream>
//# include <ios>
# include <string>


class Data {

public:

    typedef enum { prop=0, obj, array } skip;

    std::fstream s;

    template<typename T>
    Data(T filename) {
        s.open(filename);
    }


    template<typename T>
    void open(T filename) {
        s.close();
        s.open(filename);
    }

    void close() {
        s.close();
    }
    
};


template<typename T>
Data &operator<<(Data &out, T &_this) {
    out.s << _this;
    return out;
}

Data &operator>>(Data &out, Data::skip val) {
    switch (val) {
    case Data::skip::prop : out.s.ignore(',');
    case Data::skip::obj : out.s.ignore(';');
    case Data::skip::array : out.s.ignore('\n');
    }
    return out;
}


template<typename T>
Data &operator>>(Data &in, T &_this) {
    return in >> _this;
}

# endif // DATA_CPP_DEFINED
