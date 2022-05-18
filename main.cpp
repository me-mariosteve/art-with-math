# include "includes/includes.hpp"



int main(int argc, char **argv) {

    const int X = 480, Y = 360, FPS = 1, TOTAL_FRAMES = 3;
    const std::string OUTPUT_FILE = "out.avi";
    const int CODEC = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    const cv::Size SIZE(X, Y);
    const bool IS_COLOR = true;
    
    // setup the video output
    cv::VideoWriter videoOutput;
    if (!videoOutput.open(
            OUTPUT_FILE,
            CODEC,
            FPS,
            SIZE, // dimensions
            IS_COLOR // colors
            )) {
        std::cerr << "Failed to open video." << std::endl;
    }
    
    // generate points
    // r2(x0, x1, stepx, y0, y1, stepy, Point(x, y, sx, sy, radius, mass, color))
    std::vector<PointI> pts = Generator::r2(0, X, 60, 0, Y, 60, PointI(0, 0, 0, 0, 4, 1, cv::Vec3b(0, 0, 255)));
    
    int time = 0;
    while (time < TOTAL_FRAMES) {

        // write the frame to the video
        cv::Mat frame(Y, X, CV_8UC3, cv::Vec3b(0, 0, 0));
        draw(pts, frame); // something goes wrong here, the points aren't drawn after the first frame
        videoOutput.write(frame);

        // display the frame
        /*
          cv::destroyAllWindows();
          cv::imshow("Frame " + std::to_string(time), frame);
          cv::waitKey(0);
        */
        
        std::cerr << "Frame " << time << std::endl;

        // update the points
        // apply(std::vector<T>, (T, T) -> T, (std::vector<T>) -> T)
        Algo::apply(pts,
                    [&] (PointI &p1, PointI &p2) -> PointI {
                        return p1;
                    },
                    [&] (std::vector<PointI> vec) -> PointI {
                        return Algo::meanFull(vec);
                    });
        time++;

    }
    
}
