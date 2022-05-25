# include "../includes/includes.hpp"



namespace PointAlgo {
    
    /**
       Algorithms specific to Point.
     */
    
    
    
    // Like Algo::mean, but applied to every data members of Point.
    template<class T>
    Point<T> meanFull(const std::vector<Point<T>> &_this) {
        const size_t size = _this.size();
        int color0 = int(), color1 = int(), color2 = int();
        T x = T(), y = T(), sx = T(), sy = T(), radius = T(), mass = T();
        std::for_each(_this.begin(), _this.end(), [&] (const Point<T> &pt) -> void {
            color0 += pt.color[0];
            color1 += pt.color[1];
            color2 += pt.color[2];
            x += pt.x; y += pt.y;
            sx += pt.sx; sy += pt.sy;
            radius += pt.radius; mass += pt.mass; 
        });
        return Point<T>(
            x/size, y/size, sx/size, sy/size,
            radius/size, mass/size,
            cv::Vec3b(color0/size, color1/size, color2/size)
            );
    }
    
    
    // Apply some functions and algorithms to a sequence of a points.
    template<class T>
    inline void update(std::vector<Point<T>> &_this) {
        std::for_each(_this.begin(), _this.end(), [&] (Point<T> &_pt) {
            _pt.x += _pt.sx;
            _pt.y += _pt.sy;
        });
    }
    

    template<class T, class BinaryOperation, class R>
    inline void doAll(std::vector<Point<T>> &_this, BinaryOperation binary_op, R reduce) {
        Algo::apply(_this, binary_op, reduce);
        update(_this);
    }


    // Equivalent of doAll with reduce=meanFull, optimised.
    template<class T, class BinaryOperation>
    void doAll_meanFull(std::vector<Point<T>> &_this, BinaryOperation binary_op) {
        size_t size = _this.size(), size1 = size-1;
        std::vector<Point<T>> res;
        res.reserve(size);
        for (const Point<T> &v1: _this) {
            T x = T(), y = T(), sx = T(), sy = T(), mass = T(), radius = T();
            int col0 = 0, col1 = 0, col2 = 0;
            std::vector<Point<T>> temp;
            temp.reserve(size1);
            for (const Point<T> &v2: _this) {
                if (&v1 != &v2) {
                    Point<T> pt = binary_op(v1, v2);
                    x = x+pt.x, y = y+pt.y, sx = sx+pt.sx, sy = sy+pt.sy;
                    radius = radius+pt.radius, mass = mass+pt.mass;
                    col0 = col0+pt.color[0], col1 = col1+pt.color[1], col2 = col2+pt.color[2];
                    temp.push_back(pt);
                }
            }
            res.emplace_back(x/size1+v1.sx, y/size1+v1.sy, sx/size1, sy/size1,
                             radius/size1, mass/size1,
                             cv::Vec3b(col0/size1, col1/size1, col2/size1)
                );
        }
        _this = res;
    }
    
    
}
