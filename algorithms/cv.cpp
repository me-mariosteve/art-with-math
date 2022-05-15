# pragma once

# ifndef NO_OPENCV

# include "../includes/includes.hpp"



template<class T>
void draw(const Point<T> &_this, cv::Mat &mat) {
    cv::circle(mat, cv::Point(_this.x, _this.y), _this.radius, _this.color, -1);
}


template<class T>
void draw(const std::vector<T> &_this, cv::Mat &mat) {
    for (const T it: _this)
        draw(it, mat);
}


# endif /* NO_OPENCV */
