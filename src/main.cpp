# include "includes/includes.hpp"


using namespace PointAlgo;


int main(int argc, char **argv) {

    
    const std::string OUTPUT_FILE = "out.avi";
    
    if (std::filesystem::exists(OUTPUT_FILE)) {

        std::string ans;
        std::cout
            << "Output video file at '" << OUTPUT_FILE << "' already exists." << std::endl
            << "Would you like to copy it (s) (default), overwrite it (o) or exit (q or Ctrl+c) ?" << std::endl;
        std::cin >> ans;
        
        if (ans == "o") {
            std::cout << "'" << OUTPUT_FILE << "' will be overwritten." << std::endl;
            
        } else if (ans == "q") {
            std::cout << "Exiting" << std::endl;
            exit(1);
            
        } else {
            std::cout << "Enter the new path: ";
            std::filesystem::path newPath;
            std::cin >> newPath;
            std::filesystem::rename(OUTPUT_FILE, newPath);
        }
        
    }

    const int X = 1920, Y = 1080, TOTAL_FRAMES = 1000;
    const cv::Size SIZE(X, Y);

    cv::VideoWriter videoOutput;
    if (!videoOutput.open(
            OUTPUT_FILE,
            cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), // codec
            30, // fps
            SIZE,
            true // the video will contain colors
            )) {
        std::cerr << "Failed to open video." << std::endl;
    }

    
    typedef double T;
    typedef Point<T> Pt;
    const Pt POINT_TEMPLATE(X/2, Y/2, 0, 0, 1, 1, cv::Vec3b(255, 255, 255));
    T RADIUS = sqrt(X*X+Y*Y);
    
    // generate points
    std::vector<Pt> pts = Generator::disk_fn<T>(
        RADIUS/4, Math::TAU/150, RADIUS/4/100,
        [&] (Pt pt, T theta, T r) -> Pt {
            pt.x += sin(theta)*r*pow(r/RADIUS*4, 4);
            pt.y += cos(theta)*r*pow(r/RADIUS*4, 4);
            return pt;
        },
        POINT_TEMPLATE);
    
    std::cout << pts.size() << " points created." << std::endl << std::fixed;
    

    std::chrono::duration<double> t_sum = std::chrono::duration<double>();
    
    int time = 0, frameCount = 1;
    while (frameCount <= TOTAL_FRAMES) {

        // write the frame to the video
        cv::Mat frame(SIZE, CV_8UC3, cv::Vec3b(0, 0, 0));
        draw(pts, frame);
        videoOutput.write(frame);

        std::cout << "\033[2KFrame " << frameCount << " / " << TOTAL_FRAMES << "... ";
        
        // to get the time needed to make a frame
        std::chrono::time_point t_begin = std::chrono::high_resolution_clock::now();
        
        PointAlgo::doAll_meanFull(pts,
                                  [&] (const Pt &p1, const Pt &p2) -> Pt {
                                      Pt ret = p1;
                                      T dx = p2.x-p1.x, dy = p2.y-p1.y, d = sqrt(dx*dx + dy*dy);
                                      d += d<1;
                                      T _sin = dx/d, _cos = dy/d,
                                          surf_dist = d-p1.radius-p2.radius,
                                          direct = (surf_dist<0) * surf_dist/2,
                                          force = (p1.mass*p2.mass) / (d*d);
                                      ret.x += direct*_sin, ret.y += direct*_cos;
                                      ret.sx += force*_sin, ret.sy += force*_cos;
                                      return ret;
                                  }
            );

        std::chrono::time_point t_end = std::chrono::high_resolution_clock::now();
        // https://stackoverflow.com/a/30849282/18598705
        std::chrono::duration<double> t_diff = std::chrono::duration_cast<std::chrono::duration<double>> (t_end-t_begin);
        t_sum += t_diff;
        
        std::cout << " "
                  << t_diff.count() << "s, mean "
                  << (t_sum/frameCount).count() << "s, "
                  << (t_sum/frameCount * (TOTAL_FRAMES-frameCount)).count() << " remaining."
                  << std::endl << "\033[1F"; // Thanks to fnky on github for the ANSI escape code! https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#cursor-controls
        
        time++;
        frameCount++;
    }

    std::cout << std::endl;
    
}
