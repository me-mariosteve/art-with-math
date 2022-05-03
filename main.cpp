# include "includes/includes.hpp"


int main(int argc, char **argv) {
    
    const int X = 480, Y = 360, TOTAL_FRAMES = 3;
    // setup the video output
    cv::VideoWriter videoOutput(
        "out.avi", // file name
        cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), // codec
        1, // fps
        cv::Size(X, Y), // dimensions
        1 // colors
        );
    
    // generate points
    std::vector<PointI> pts = Generator::r2(0, X, 60, 0, Y, 60, PointI(0, 0, 0, 0, 10, 1, cv::Vec3b(0, 0, 255)));

    int time = 0;
    while (time < TOTAL_FRAMES) {
        
        cv::Mat frame(X, Y, CV_8UC3, cv::Vec3b(0, 0, 0));
        draw(pts, frame);
        videoOutput << frame;
        
        std::cout << "Frame #" << time << ":" << std::endl << pts << std::endl;
        
        // I don't know if Algo::apply is working correctly...
        ///*
        Algo::apply(pts,
                    [&] (PointI &p1, PointI &p2) -> PointI{
                        return p1 + p2;
                    },
                    [&] (std::vector<PointI> vec) -> PointI {
                        return Algo::meanFull(vec);
                    });
        //*/

        /*
        std::vector<PointI> news(pts.size());
        for (auto p1 = pts.begin(); p1 != pts.end(); p1++) {
            std::vector<PointI> temp(pts.size()-1);
            for (auto p2 = pts.begin(); p2 != pts.end(); p2++) {
                temp.push_back(*p1 + *p2);
            }
            PointI mean(0, 0, 0, 0, 0, 0, cv::Vec3b(0, 0, 0));
            Algo::for_each(temp,
                           [&] (PointI p) -> void {
                               mean.x += p.x;
                               mean.y += p.y;
                               mean.sx += p.sx;
                               mean.sy += p.sy;
                               mean.radius += p.radius;
                               mean.mass += p.mass;
                               mean.color += p.color;
                           }
                );
            mean.x /= pts.size()-1;
            mean.y /= pts.size()-1;
            mean.sx /= pts.size()-1;
            mean.sy /= pts.size()-1;
            mean.radius /= pts.size()-1;
            mean.mass /= pts.size()-1;
            mean.color /= (int) pts.size()-1;
        }
        pts = std::vector<PointI>(news);
        */
        
        time++;

    }

    std::cout << std::endl << std::endl << "main finished." << std::endl << std::endl;

}
