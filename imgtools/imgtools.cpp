/*
 * Info: https://docs.opencv.org/2.4.13.7/doc/tutorials/introduction/display_image/display_image.html
 */

# include "../includes/includes.hpp"


int main(int argc, char **argv) {
    if(argc == 1 || !strcmp(argv[1], "help")) {
        std::cout << " Usage: imgtools command [args]" << std::endl
                  << " Commands:" << std::endl
                  << "  help" << std::endl
                  << "  view IMG" << std::endl
                  << "  copy IMG" << std::endl
            ;
        return -1;
    }

    
    if (!strcmp(argv[1], "view")) {
        if (argc != 3) {
            std::cerr << argv[0] << ": \033[38;5;1mExpected an image path\033[38;5;15m" << std::endl;
            return 1;
        }
        
        cv::Mat image;
        image = cv::imread(argv[2], CV_LOAD_IMAGE_COLOR);
        
        if(!image.data) {
            std::cerr << "\033[38;5;1mCould not open the image\033[38;5;15m" << std::endl;
            return 1;
        }
        
        cv::namedWindow("Display window", cv::WINDOW_NORMAL);
        cv::imshow("Display window", image);
        
        cv::waitKey(0);

        
    } else if (!strcmp(argv[1], "copy")) {
        if (argc != 4) {
            std::cerr << argv[0] << ": \033[38;5;1mExpected the source and target paths\033[38;5;15m" << std::endl;
            return 1;
        }
        cv::Mat input;
        try {
            input = cv::imread(argv[2], CV_LOAD_IMAGE_COLOR);
            cv::imwrite(argv[3], input);
        } catch (cv::Exception &e) {
            std::cerr << argv[0] << ": \033[38;5;1mCaught error from OpenCV: \033[38;5;15m" << e.what() << std::endl;
            return 2;
        }

        
    } else {
        std::cerr << argv[0] << ": '" << argv[1] << "': \033[38;5;1mInvalid command\033[38;5;15m" << std::endl;
    }
    
    return 0;
}
