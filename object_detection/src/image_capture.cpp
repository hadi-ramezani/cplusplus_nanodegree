#include <thread>
#include "image_capture.h"

void ImageCapture::readImageFromWebcam()
{
    captureThread = std::thread([this]() {
        cv::VideoCapture cap(0);
        if (!cap.isOpened()) {
            std::cerr << "Failed to open the webcam\n";
            isCaptureFinished = true;
            return;
        }
        while (true) {
            cv::Mat currentImage;
            cap.read(currentImage);

            if (currentImage.empty()) {
                break;
            }

            {
                std::unique_lock<std::mutex> lock(imageQueueMutex);
                imageAvailableCondition.wait(lock, [this]() { return imageQueue.size() < maxQueueSize; });
                imageQueue.push_back(currentImage);
            }

            imageAvailableCondition.notify_one();
        }
        isCaptureFinished = true;
        imageAvailableCondition.notify_all();
    });
}

void ImageCapture::readImage()
{
    readImageFromWebcam();
}

void ImageCapture::joinCaptureThread()
{
    if (captureThread.joinable())
        captureThread.join();
}

bool ImageCapture::isFinished() const
{
    return isCaptureFinished;
}

cv::Mat ImageCapture::getNextImage()
{
    std::unique_lock<std::mutex> lock(imageQueueMutex);
    imageAvailableCondition.wait(lock, [this]() { return !imageQueue.empty() || isCaptureFinished; });

    if (imageQueue.empty() && isCaptureFinished)
        return cv::Mat();

    cv::Mat currentImage = imageQueue.front();
    imageQueue.pop_front();

    lock.unlock();
    imageAvailableCondition.notify_one();

    return currentImage;
}