# include "includes/includes.hpp"


int main(int argc, char **argv) {
    const char *OUT = "out.png";
    const int X = 1000, Y = 1000;
    const cv::Vec3b COLOR(0,0,255);
    
    cv::Mat out;
    out.create(X, Y, CV_8UC3);

    ArrayP<int> arr = Algo::Grid::l2(X, Y);
    draw(arr, out);
    
    cv::imwrite(OUT, out);
    std::cerr << "main: last in main" << std::endl;
}
