# pragma once

# ifndef NO_OPENCV

# include "../includes/includes.hpp"



template<class T>
inline void draw(const Point<T> &_this, cv::Mat &mat) {
    cv::circle(mat, cv::Point(_this.x, _this.y), _this.radius-1, _this.color, -1);
}


template<class T>
void draw(Array<T> &_this, cv::Mat &mat) {
    for (size_t i = 0; i < _this.size; i++)
        draw(_this[i], mat);
}


template<class T>
void draw(const std::vector<T> &_this, cv::Mat &mat) {
    for (const T &it: _this)
        draw(it, mat);
}


# endif /* NO_OPENCV */
