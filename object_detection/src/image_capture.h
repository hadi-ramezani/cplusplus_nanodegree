#ifndef IMAGE_CAPTURE_H
#define IMAGE_CAPTURE_H

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include "opencv2/opencv.hpp"

class ImageCapture {
public:
    void readImage();
    void readImageFromWebcam();
    void joinCaptureThread();
    bool isFinished() const;
    cv::Mat getNextImage();

private:
    std::thread captureThread;
    std::atomic<bool> isCaptureFinished{ false };
    std::mutex imageQueueMutex;
    std::deque<cv::Mat> imageQueue;
    size_t maxQueueSize = 5;  // Maximum size of the bounded queue
    std::condition_variable imageAvailableCondition;
};
#endif
