#include <iostream>
#include <fstream>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <deque>
#include <queue>

#include "opencv2/opencv.hpp"
#include "opencv2/dnn.hpp"
#include "opencv2/dnn/all_layers.hpp"
#include "configuration.h"
#include "utilities.h"
#include "image_capture.h"
#include "image_processor.h"
#include "image_display.h"

using namespace std;
using namespace cv;
using namespace dnn;


int main(int, char* argv[]) {
    // prepare the conf object and capture potential issues
    if (argv[1] == nullptr) {
        std::cout << "No configuration file was provided. Please provide a configuration file. Exiting...\n";
        return 1;
    }

    std::shared_ptr<Configuration> conf;
    try {
        conf = std::make_shared<Configuration>(argv[1]);
    } catch (const std::exception& e) {
        std::cerr << "Unable to parse the configuration file. The error is: " << e.what() << " Exiting...\n";
        return 1;
    }
    
    // get the class names
    std::vector<std::string> classNames = readFileIntoVector(conf->classesPath);

    // instantiate capture, processor, and display objects
    ImageCapture imageCapture;
    ImageProcessor imageProcessor(conf, classNames, 4);
    ImageDisplay imageDisplay;

    // start reading the images in its own thread 
    imageCapture.readImage();
    std::cout << "Capturing the video has started. Press Ctrl+c to stop anytime.\n";

    // start processing the images in a separate thread
    std::thread processingThread([&]() {
        imageProcessor.processImages(imageCapture);
    });

    imageDisplay.run(imageProcessor, imageCapture);

    imageCapture.joinCaptureThread();
    processingThread.join();
}