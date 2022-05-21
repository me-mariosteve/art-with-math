# include "includes/includes.hpp"


using namespace PointAlgo;


int main(int argc, char **argv) {
    

    
    typedef double T;
    typedef Point<T> Pt;
    const Pt POINT_TEMPLATE(0, 0, 0, 0, 1, 1, cv::Vec3b(0, 0, 255));

    const int X = 480, Y = 360, FPS = 30, TOTAL_FRAMES = 300;
    
    
    const std::string OUTPUT_FILE = "out.avi";
    const int CODEC = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
    const cv::Size SIZE(X, Y);
    const bool IS_COLOR = true;

    
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

    
    cv::VideoWriter videoOutput;
    if (!videoOutput.open(
            OUTPUT_FILE,
            CODEC,
            FPS,
            SIZE,
            IS_COLOR
            )) {
        std::cerr << "Failed to open video." << std::endl;
    }
    
    // generate points
    std::vector<Pt> pts = Generator::disk<T>(X/2, Y/2, sqrt(X*X+Y*Y)/4, Math::TAU/36, 10, POINT_TEMPLATE);
    
    int time = 0;
    while (time < TOTAL_FRAMES) {

        // write the frame to the video
        // I remembered that X and Y must be reversed for cv::Mat after 2 weeks of pain
        cv::Mat frame(Y, X, CV_8UC3, cv::Vec3b(0, 0, 0));
        draw(pts, frame);
        videoOutput.write(frame);

        
        std::cout << "Frame " << time << " / " << TOTAL_FRAMES << "..." << std::endl;

        // update the points
        PointAlgo::doAll(pts,
                         [&] (Pt &p1, Pt &p2) -> Pt {
                             Pt ret = p1;
                             T
                                 dx = p2.x - p1.x, dy = p2.y - p1.y, d = sqrt(dx*dx + dy*dy),
                                 surf_dist = (d += d<=1) - p1.radius - p2.radius,
                                 _sin = dx/d, _cos = dy/d,
                                 attraction = (p1.mass * p2.mass) / pow(d, 2),
                                 //repulsion = 0,//log(dist - surf_dist),
                                 force = attraction, //- repulsion,
                                 force_x = force * _sin, force_y = force * _cos;
                             ret.sx += force_x, ret.sy += force_y;
                             return ret;
                         },
                         PointAlgo::meanFull<T>
            );

        // Thanks to fnky on github!
        // https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#cursor-controls
        std::cout << "\033[1F";
        
        time++;
    }

    std::cout << std::endl;
    
}
