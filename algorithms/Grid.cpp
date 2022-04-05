# ifndef ALGO_GRID_GENERATE_CPP_DEFINED
# define ALGO_GRID_GENERATE_CPP_DEFINED

# include "../includes/includes.hpp"
# include "generate.cpp"



namespace Algo::Grid {

    

    // l2 for [l]ength, [2] parameters
    namespace _l2 {

        
        template<typename T>
        ArrayP<T> l2(T dx, T dy, Point<T> tmp=(0, 0)) {
            ArrayP<T> out(dx*dy);
            for (T y = 0; y < dy; y++)
                for (T x = 0; x < dx; x++)
                    out[y*dx+x] = Point<T>(x, y);
            return out;
        }

        template<typename T>
        ArrayP<T> l2(T dx, T dy, T step) {
            ArrayP<T> out(dx*dy/step);
            for (T y = 0; y < dy; y += step)
                for (T x = 0; x < dx; x += step)
                    out[y*dx+x] = Point<T>(x, y);
            return out;
        }

        template<typename T>
        ArrayP<T> l2(T dx, T dy, T sx, T sy) {
            ArrayP<T> out(dx*dy/sx/sy);
            for (T y = 0; y < dy; y += sy)
                for (T x = 0; x < dx; x += sx)
                    out[y*dx+x] = Point<T>(x, y);
            return out;
        }

    }
    using namespace _l2;


    
    // lf1 for [l]ength, [f]unction, [1] parameter
    namespace _lf1 {

        
        template<typename T, typename F>
        ArrayP<T> lf1(T dx, F func ) {
            ArrayP<T> out(dx);
            for (T x = 0; x < dx; x++)
                out[x] = func(x);
            return out;
        }
    
        template<typename T, typename F>
        ArrayP<T> lf1(T dx, T step, F func ) {
            ArrayP<T> out(dx/step);
            for (T x = 0; x < dx; x += step)
                out[x] = func(x);
            return out;
        }

    }
    using namespace _lf1;



    // rf1 for [r]ange, [f]unction, [1] parameter
    namespace _rf1 {
    
        template<typename T, typename F>
        ArrayP<T> rf1(T x0, T x1, F func) {
            ArrayP<T> out(x1-x0);
            for (T x = x0; x < (x1-x0); x++)
                out[x] = func(x);
            return out;
        }

        template<typename T, typename F>
        ArrayP<T> rf1(T x0, T x1, T step, F func) {
            ArrayP<T> out((x1-x0)/step);
            for (T x = x0; x < (x1-x0)/step; x += step)
                out[x] = func(x);
            return out;
        }

    }
    using namespace _rf1;
    
}

# endif /* ALGO_GRID_GENERATE_CPP_DEFINED */

