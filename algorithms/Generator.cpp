# pragma once

# include "../includes/includes.hpp"



namespace Generator {


    
    // rf1 for [r]ange, [f]unction, [1] parameter
    template<class T, typename F>
    std::vector<Point<T>> r2(T startx, T endx, T stepx, F func, Point<T> tmp=Point<T>()) {
        std::vector<Point<T>> out(endx - startx, tmp);
        int i = 0;
        for (T x = startx; x < endx; x += stepx) {
            out[i++] = func(x);
        }
        return out;
    }
 

    // r2 for [r]ange, [2] parameters
    template<class T>
    std::vector<Point<T>> r2(T startx, T endx, T stepx, T starty, T endy, T stepy, Point<T> tmp=Point<T>()) {
        std::vector<Point<T>> out((endx - startx) * (endy - starty) / (stepx * stepy), tmp);
        int i = 0;
        for (T x = startx; x < endx; x += stepx) {
            for (T y = starty; y < endy; y += stepy) {
                out[i].x = x;
                out[i++].y = y;
            }
        }
        return out;
    }

    
    // rf2 for [r]ange, [f]unction, [2] parameter
    template<class T, typename F>
    std::vector<Point<T>> r2(T startx, T endx, T stepx, T starty, T endy, T stepy, F func, Point<T> tmp=Point<T>()) {
        std::vector<Point<T>> out((endx - startx) * (endy - starty) / (stepx * stepy), tmp);
        int i = 0;
        for (T x = startx; x < endx; x += stepx) {
            for (T y = starty; y < endy; y += stepy) {
                out[i++] = func(x, y);
            }
        }
        return out;
    }

}
