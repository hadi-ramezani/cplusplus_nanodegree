#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include <queue>
#include "image_capture.h"
#include "configuration.h"
#include "opencv2/opencv.hpp"
#include "opencv2/dnn.hpp"
#include "opencv2/dnn/all_layers.hpp"

using namespace cv;
using namespace dnn;

class ImageProcessor {
public:
    ImageProcessor(std::shared_ptr<Configuration> conf, std::vector<std::string> classNames, int numThreads)
        : conf(conf), classNames(classNames), numThreads(numThreads) {};

    void processImages(ImageCapture& imageCapture);
    cv::Mat getNextProcessedImage();
    bool isFinished() const; // Getter for isProcessingFinished

private:
    int numThreads;
    std::queue<cv::Mat> outputImageQueue;
    std::mutex outputImageQueueMutex;
    std::shared_ptr<Configuration> conf;
    std::vector<std::string> classNames;
    std::atomic<bool> isProcessingFinished{ false };
};

#endif