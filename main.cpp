# include "includes/includes.hpp"


int main(int argc, char **argv) {
    const char *OUT = "out.png";
    const int X = 1000, Y = 1000;
    const cv::Vec3b COLOR(0,0,255);
    
    cv::Mat out;
    out.create(X, Y, CV_8UC3);

    ArrayP<int> arr = Algo::Grid::l2((int) X, (int) Y);
    std::cout << "main: passed Grid::l2" << std::endl;
    draw(arr, out);
    std::cout << "main: passed draw" << std::endl;
    
    cv::imwrite(OUT, out);
    std::cout << "main: passed imwrite" << std::endl;
}
