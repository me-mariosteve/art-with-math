# include "includes/includes.hpp"


int main(int argc, char **argv) {
    const char *OUT = "out.png";
    const int X = 128, Y = 128;
    
    cv::Mat out(X, Y, CV_8UC3, cv::Vec3b(0, 255, 255));
    
    ArrayP<int> arr = Algo::Grid::lf2(X, Y, [](int x, int y){
        Point<int> out(x, y);
        out.radius = 1;
        out.color = cv::Vec3b(x%256, 0, 0);
        return out;
    });
    
    draw(arr, out);
    cv::imshow("out", out);
    cv::waitKey(0);
    cv::imwrite(OUT, out);
}
