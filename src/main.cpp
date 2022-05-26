# include "includes/includes.hpp"

using namespace PointAlgo;



int main(int argc, char **argv) {

    
    typedef double T;
    typedef Point<T> Pt;


    // Parameters which can be given through command line options
    struct {
        std::string output = "./out.avi";
        int width = 1920, height = 1080,
            fps = 10,
            length = 300;
        cv::Size size = cv::Size(1920, 1080);
        Pt point = Pt(0, 0, 0, 0, 1, 10, cv::Vec3b(255, 255, 255));
    } params;

    {
        // Parse command-line arguments
        int i;
        auto seti = [&] (auto &ref) {
            ref = std::stoi(argv[++i]);
        };
        for (i = 0; i < argc; i++) {
        std::string arg = argv[i];
            
            if (arg == "-h" || arg == "--help") {
                std::cout <<
                    "Usage:\n"
                    "  " << argv[0] << " [OPTIONS ...]\n"
                    "Short options cannot be combined into one, for example '-o -s' is not '-os'.\n"
                    "\n"
                    "Options with default value surrounded by brackets:\n"
                    "\n"
                    "  -h, --help      Show the help for this program.\n"
                    "  -u, --usage     Show a shorter help message.\n"
                    "  -L, --license   Show the license.\n"
                    "\n"
                    "  -o, --output FILE         Write the video to FILE. [./out.avi]\n"
                    "  -w, --width WIDTH         Set the video width. [1920]\n"
                    "  -h, --height HEIGHT       Set the video height. [1080]\n"
                    "  -s, --size WIDTH HEIGHT   Set the video width and height. [1920] [1080]\n"
                    "  --fps FPS                 Set the frames per seconds. [10]\n"
                    "  -l, --length LENGTH       Set the number of frames in the video. [300]\n"
                    "\n"
                    "  -psx, --point-sx SX          Set the x points speed at start. [0]\n"
                    "  -psy, --point-sy SY          Set the y points speed at start. [0]\n"
                    "  -pr, --point-radius RADIUS   Set the points radius. [1]\n"
                    "  -pm, --point-mass MASS       Set the points mass. [10]\n"
                    "  -pc, --point-color R G B     Set the points color (decimal). [255 255 255]\n"
                          << std::endl;
                exit(0);
            } else if (arg == "-u" || arg == "--usage") {
                std::cout <<
                    "Usage:\n"
                    "  " << argv[0] << "\n"
                    "    [-h | --help] [-u | --usage] [-L | --license]\n"
                    "    [{-o | --output} FILE]\n"
                    "    [{-w | --width} WDITH] [{-h | --height} HEIGHT] [{-s | --size} WIDTH HEIGHT]\n"
                    "    [--fps FPS] [{-l | --length} LENGTH]\n"
                    "    [{-psx | --point-sx} SX] [{-psy | --point-sy} SY]\n"
                    "    [{-pr | --point-radius} RADIUS] [{-pm | --point-mass} MASS]\n"
                    "    [{-pc | --point-color} R G B]"
                          << std::endl;
                exit(0);
            } else if (arg == "-L" || arg == "--license") {
                std::cout <<
                    "MIT License\n"
                    "\n"
                    "Copyright (c) 2022 me-mariosteve\n"
                    "\n"
                    "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
                    "of this software and associated documentation files (the \"Software\"), to deal\n"
                    "in the Software without restriction, including without limitation the rights\n"
                    "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
                    "copies of the Software, and to permit persons to whom the Software is\n"
                    "furnished to do so, subject to the following conditions:\n"
                    "\n"
                    "The above copyright notice and this permission notice shall be included in all\n"
                    "copies or substantial portions of the Software.\n"
                    "\n"
                    "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
                    "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
                    "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
                    "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
                    "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
                    "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
                    "SOFTWARE.\n"
                          << std::endl;
                exit(0);
                
            } else if (arg == "-o" || arg == "--output") {
                params.output = argv[++i];
            } else if (arg == "-w" || arg == "--width") {
                seti(params.width);
            } else if (arg == "-h" || arg == "--height") {
                seti(params.height);
            } else if (arg == "-s" || arg == "--size") {
                seti(params.width);
                seti(params.height);
            } else if (arg == "--fps") {
                seti(params.fps);
            } else if (arg == "-l" || arg == "--length") {
                seti(params.length);

            } else if (arg == "-psx" || arg == "--point-sx") {
                seti(params.point.sx);
            } else if (arg == "-psy" || arg == "--point-sy") {
                seti(params.point.sy);
            } else if (arg == "-pr" || arg == "--point-radius") {
                seti(params.point.radius);
            } else if (arg == "-pm" || arg == "--point-mass") {
                seti(params.point.mass);
            } else if (arg == "-pc" || arg == "--point-color") {
                // cv::Vec3b(B, G, R)
                seti(params.point.color[2]);
                seti(params.point.color[1]);
                seti(params.point.color[0]);
            }
        }
    }
    params.size = cv::Size(params.width, params.height);
    params.point.x = params.width/2, params.point.y = params.height/2;

    
    cv::VideoWriter videoOutput;
    if (!videoOutput.open(
            params.output,
            cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), // codec
            params.fps, // fps
            params.size,
            true // the video will contain colors
            )) {
        std::cerr << "Failed to open video." << std::endl;
        exit(1);
    }
    
    
    // generate points
    T radius = sqrt(pow(params.width, 2)+pow(params.height, 2));
    Array<Pt> pts = Generator::disk_fn<T>(
        radius/20, Math::TAU/100, radius/20/100,
        [&] (Pt pt, T theta, T r) -> Pt {
            pt.x += sin(theta)*r*pow(r/radius*20, 4);
            pt.y += cos(theta)*r*pow(r/radius*20, 4);
            return pt;
        },
        params.point);
    
    std::cout << pts.size << " points created." << std::endl << std::fixed;

    std::chrono::duration<double> t_sum = std::chrono::duration<double>();
    
    int time = 0, frameCount = 1;
    while (frameCount <= params.length) {
        
        // write the frame to the video
        cv::Mat frame(params.size, CV_8UC3, cv::Vec3b(0, 0, 0));
        draw(pts, frame);
        videoOutput.write(frame);

        std::cout << "\033[2KFrame " << frameCount << " / " << params.length << "... ";
        
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
                  << (t_sum/frameCount * (params.length-frameCount)).count() << " remaining."
                  << std::endl << "\033[1F"; // Thanks to fnky on github for the ANSI escape code! https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797#cursor-controls
        
        time++;
        frameCount++;
    }

    std::cout << "\nmain() finished." << std::endl;
    
}
