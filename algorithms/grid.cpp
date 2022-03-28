# ifndef ALGO_GRID_GENERATE_CPP_DEFINED
# define ALGO_GRID_GENERATE_CPP_DEFINED

# include "../includes/includes.hpp"
# include "generate.cpp"




namespace Algo::Grid {

    

    // l2 for [l]ength, [2] parameters
    namespace l2 {

        
        template<typename T>
        ArrayP<T> grid2(T dx, T dy) {
            ArrayP<T> out(dx*dy);
            for (T y = 0; y < dy; y++)
                for (T x = 0; x < dx; x++)
                    out[y*dx+x] = Point<T>(x, y);
            return out;
        }

        template<typename T>
        ArrayP<T> grid2(T dx, T dy, T step) {
            ArrayP<T> out(dx*dy/step);
            for (T y = 0; y < dy; y += step)
                for (T x = 0; x < dx; x += step)
                    out[y*dx+x] = Point<T>(x, y);
            return out;
        }

        template<typename T>
        ArrayP<T> grid2(T dx, T dy, T sx, T sy) {
            ArrayP<T> out(dx*dy/sx/sy);
            for (T y = 0; y < dy; y += sy)
                for (T x = 0; x < dx; x += sx)
                    out[y*dx+x] = Point<T>(x, y);
            return out;
        }

    }


    
    // lf1 for [l]ength, [f]unction, [1] parameter
    namespace lf1 {

        
        template<typename T>
        ArrayP<T> grid1lf(T dx, Point<T> (*func) (T) ) {
            ArrayP<T> out(dx);
            for (T x = 0; x < dx; x++)
                out[x] = func(x);
            return out;
        }
    
        template<typename T>
        ArrayP<T> grid1lf(T dx, T step, Point<T> (*func) (T) ) {
            ArrayP<T> out(dx/step);
            for (T x = 0; x < dx; x += step)
                out[x] = func(x);
            return out;
        }

    }



    // rf1 for [r]ange, [f]unction, [1] parameter
    namespace rf1 {
    
        template<typename T>
        ArrayP<T> grid1rf(T x0, T x1, Point<T> (*func) (T) ) {
            ArrayP<T> out(x1-x0);
            for (T x = x0; x < (x1-x0); x++)
                out[x] = func(x);
            return out;
        }

        template<typename T>
        ArrayP<T> grid1rf(T x0, T x1, T step, Point<T> (*func) (T) ) {
            ArrayP<T> out((x1-x0)/step);
            for (T x = x0; x < (x1-x0)/step; x += step)
                out[x] = func(x);
            return out;
        }

    }
    
}

# endif /* ALGO_GRID_GENERATE_CPP_DEFINED */
