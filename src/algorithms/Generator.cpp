# pragma once

# include "../includes/includes.hpp"



namespace Generator {


    
    // rf1 for [r]ange, [f]unction, [1] parameter
    
    template<class T, typename F>
    std::vector<Point<T>> rf1(T startx, T endx, T stepx, F func, Point<T> tmp=Point<T>()) {
        std::vector<Point<T>> out(endx - startx, tmp);
        size_t i = 0;
        for (T x = startx; x < endx; x += stepx) {
            out[i++] = func(x);
        }
        return out;
    }


    
    // r2 for [r]ange, [2] parameters
    
    template<class T>
    std::vector<Point<T>> r2(T startx, T endx, T stepx, T starty, T endy, T stepy, const Point<T> &tmp=Point<T>()) {
        std::vector<Point<T>> out((endx - startx) * (endy - starty) / (stepx * stepy), tmp);
        size_t i = 0;
        for (T x = startx; x < endx; x += stepx) {
            for (T y = starty; y < endy; y += stepy) {
                out[i].x = x;
                out[i++].y = y;
            }
        }
        return out;
    }


    // rf2 for [r]ange, [f]unction, [2] parameters
    
    template<class T, typename F>
    std::vector<Point<T>> rf2(T startx, T endx, T stepx, T starty, T endy, T stepy, F func, Point<T> tmp=Point<T>()) {
        std::vector<Point<T>> out((endx - startx) * (endy - starty) / (stepx * stepy), tmp);
        size_t i = 0;
        for (T x = startx; x < endx; x += stepx) {
            for (T y = starty; y < endy; y += stepy) {
                out.at(i) = func(tmp, x, y);
            }
        }
        return out;
    }

    


    template<class T>
    std::vector<Point<T>> disk(T x, T y, T r, T dt, T di, Point<T> tmp=Point<T>()) {
        std::vector<Point<T>> out(Math::TAU/dt*r/di, tmp);
        size_t id = 0;
        for (T t = 0; t+dt < Math::TAU; t += dt)
            for (T i = 0; i+di < r; i += di) {
                out.at(id).x = x+sin(t)*i;
                out.at(id++).y = y+cos(t)*i;
            }
        return out;
    }

}
