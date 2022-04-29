# include "includes/includes.hpp"


int main(int argc, char **argv) {
    
    const int X = 4, Y = 4, TOTAL_FRAMES = 10;
    // setup the video output
    cv::VideoWriter videoOutput(
        "out.avi", // file name
        cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), // codec
        2, // fps
        cv::Size(X, Y), // dimensions,
        1 // colors
        );
    
    // generate points
    std::vector<PointI> pts = Generator::r2(0, X, 1, 0, Y, 1, PointI(cv::Vec3b(0, 0, 255)));

    int time = 0;
    while (time < TOTAL_FRAMES) {
        
        cv::Mat frame(X, Y, CV_8UC3, cv::Vec3b(0, 0, 0));
        draw(pts, frame);
        videoOutput << frame;
        
        Algo::apply(pts,
                    [&] (PointI &p1, PointI &p2) -> PointI {
                        return p1 + p2;
                    },
                    [&] (std::vector<PointI> vec) {
                        return Algo::meanFull(vec);
                    });
        
        time++;

    }

    std::cout << std::endl << std::endl << "main finished." << std::endl << std::endl;

}
