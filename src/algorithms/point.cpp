# include "../includes/includes.hpp"



namespace PointAlgo {
    
    /**
       Algorithms specific to Point.
     */
    
    
    
    // Like Algo::mean, but applied to every data members of Point.
    template<class T>
    Point<T> meanFull(const Array<Point<T>> &_this) {
        int color0 = 0, color1 = 0, color2 = 0;
        T x = T(), y = T(), sx = T(), sy = T(), radius = T(), mass = T();
        for (size_t i = 0; i < _this.size; i++) {
            Point<T> &pt = _this[i];
            color0 += pt.color[0], color1 += pt.color[1], color2 += pt.color[2];
            x += pt.x, y += pt.y, sx += pt.sx, sy += pt.sy;
            radius += pt.radius, mass += pt.mass; 
        }
        return Point<T>(
            x/_this.size, y/_this.size, sx/_this.size, sy/_this.size,
            radius/_this.size, mass/_this.size,
            cv::Vec3b(color0/_this.size, color1/_this.size, color2/_this.size)
            );
    }
    
    
    // Apply some functions and algorithms to a sequence of a points.
    template<class T>
    inline void update(Array<Point<T>> &_this) {
        for (size_t i = 0; i < _this.size; i++) {
            Point<T> &pt = _this[i];
            pt.x += pt.sx;
            pt.y += pt.sy;
        }
    }
    

    template<class T, class BinaryOperation, class R>
    inline void doAll(Array<Point<T>> &_this, BinaryOperation binary_op, R reduce) {
        Algo::apply(_this, binary_op, reduce);
        update(_this);
    }


    // Equivalent of doAll with reduce=meanFull, optimised.
    template<class T, class BinaryOperation>
    void doAll_meanFull(Array<Point<T>> &_this, BinaryOperation binary_op) {
        size_t size1 = _this.size-1;
        Array<Point<T>> res(_this.size);
        _this.foreach_vi([&] (Point<T> &v1, size_t &i) -> void {
            T x = T(), y = T(), sx = T(), sy = T(), mass = T(), radius = T();
            int col0 = 0, col1 = 0, col2 = 0;
            _this.foreach_i([&] (size_t &j) -> void {
                if (i != j) {
                    Point<T> pt = binary_op(v1, _this[j]);
                    x = x+pt.x, y = y+pt.y, sx = sx+pt.sx, sy = sy+pt.sy;
                    radius = radius+pt.radius, mass = mass+pt.mass;
                    col0 = col0+pt.color[0], col1 = col1+pt.color[1], col2 = col2+pt.color[2];
                }
            });
            res[i] = Point<T> (x/size1+v1.sx, y/size1+v1.sy, sx/size1, sy/size1,
                               radius/size1, mass/size1,
                               cv::Vec3b(col0/size1, col1/size1, col2/size1)
                );
        });
        _this = res;
        
    }
    
    
}
