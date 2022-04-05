# include "includes/includes.hpp"


int main(int argc, char **argv) {
    const char *OUT = "out.png";
    const int X = 1000, Y = 1000;
    
    cv::Mat out = cv::Mat(X, Y, CV_8UC3, cv::Vec3b(0, 0, 255));

    ArrayP<int> arr = Algo::Grid::l2(X, Y);
    std::cerr << "main: passed Grid::l2" << std::endl;
    
    draw(arr, out);
    std::cerr << "main: passed draw" << std::endl;
    
    cv::imwrite(OUT, out);
    std::cerr << "main: passed imwrite" << std::endl;
}
