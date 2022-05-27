# pragma once

# include "../includes/includes.hpp"



namespace Generator {


    
    // rf1 for [r]ange, [f]unction, [1] parameter
    
    template<class T, typename F>
    std::vector<Point<T>> rf1(T startx, T endx, T stepx, F func, Point<T> tmp=Point<T>()) {
        std::vector<Point<T>> out;
        out.reserve(endx - startx, tmp);
        for (T x = startx; x < endx; x += stepx) {
            out.emplace_back(func(x));
        }
        return out;
    }


    
    // r2 for [r]ange, [2] parameters
    
    template<class T>
    std::vector<Point<T>> r2(T startx, T endx, T stepx, T starty, T endy, T stepy, const Point<T> &tmp=Point<T>()) {
        std::vector<Point<T>> out;
        out.reserve((endx - startx) * (endy - starty) / (stepx * stepy));
        for (T x = startx; x < endx; x += stepx) {
            for (T y = starty; y < endy; y += stepy) {
                out.emplace_back(tmp);
                out.back().x = x;
                out.back().y = y;
            }
        }
        return out;
    }


    // rf2 for [r]ange, [f]unction, [2] parameters
    
    template<class T, typename F>
    std::vector<Point<T>> rf2(T startx, T endx, T stepx, T starty, T endy, T stepy, F func, Point<T> tmp=Point<T>()) {
        std::vector<Point<T>> out((endx - startx) * (endy - starty) / (stepx * stepy));
        for (T x = startx; x < endx; x += stepx) {
            for (T y = starty; y < endy; y += stepy) {
                out.emplace_back(func(tmp, x, y));
            }
        }
        return out;
    }

    


    template<class T>
    Array<Point<T>> disk(T x, T y, T r, T dt, T di, Point<T> tmp=Point<T>()) {
        Array<Point<T>> out = (Math::TAU/dt+1) * (r/di+1);
        size_t id = 0;
        for (T t = 0; t < Math::TAU; t += dt)
            for (T i = 0; i < r; i += di, id++) {
                out.ptr[id] = tmp;
                out.ptr[id].x = x+sin(t)*i;
                out.ptr[id].y = y+cos(t)*i;
            }
        return out;
    }


    template<class T, class F>
    Array<Point<T>> disk_fn(T r, T dt, T dr, F func, Point<T> tmp=Point<T>()) {
        /* I had hard time by fixing this function, it didn't work
         * well because of floating point arithmetic which is inexact.
         */
        size_t t_n = Math::TAU/dt, r_n = r/dr;
        Array<Point<T>> out = t_n*r_n;
        size_t id = 0;
        T _i, _t;
        for (size_t t = 0; t < t_n; t++)
            for (size_t i = 0; i < r_n; i++, id++) {
                _i = i*dr, _t = t*dt;
                func(_i, _t);
                out.ptr[id] = tmp;
                out.ptr[id].x += sin(_t)*_i;
                out.ptr[id].y += cos(_t)*_i;
            }
        std::cout << out.size << "; " << id << std::endl;
        /* The loop below is faster than the one above,
         * even though it does 2 more tests `id < out.size` in each loop:
         * for (T t = dt; t < Math::TAU && id < out.size; t += dt)
         *     for (T i = 0; i < r && id < out.size; i += di, id++)
         *         out.ptr[id] = func(tmp, t, i);
         * Average time per frame with the 1st loop (without the 2 tests): 0.541930
         * Average time per frame with the 2nd, and nothing else changed: 0.530915
        */
        return out;
    }
    
    
}
