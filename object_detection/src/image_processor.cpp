#include <queue>
#include <string>
#include "image_capture.h"
#include "image_processor.h"
using namespace cv;
using namespace dnn;

bool ImageProcessor::isFinished() const {
    return isProcessingFinished;
}

void ImageProcessor::processImages(ImageCapture& imageCapture)
{
    Net net = readNet(conf->modelPath, conf->metaDataPath, "TensorFlow");
    if (net.empty()) {
        std::cerr << "Failed to load the network model." << std::endl;
        isProcessingFinished = true;
        return;
    }

    cv::Size inputSize = cv::Size(300, 300);  // Adjust as per your model's input size
    cv::Scalar mean = cv::Scalar(127.5, 127.5, 127.5);  // Adjust the mean values if needed
    bool swapRB = true;  // Adjust if needed

    cv::Mat currentImage;
    while ((currentImage = imageCapture.getNextImage()).data) {
        auto start = cv::getTickCount();

        cv::Mat blob = cv::dnn::blobFromImage(currentImage, 1.0, inputSize, mean, swapRB, false);

        net.setInput(blob);

        cv::Mat output = net.forward();
        auto end = cv::getTickCount();
        auto totalTime = (end - start) / cv::getTickFrequency();

        cv::Mat results(output.size[2], output.size[3], CV_32F, output.ptr<float>());
        cv::putText(currentImage, "FPS: " + std::to_string(int(1 / totalTime)), cv::Point(65, 65), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2, false);

        // Loop through all the predictions
        for (int i = 0; i < results.rows; i++) {
            int class_id = int(results.at<float>(i, 1));
            float confidence = results.at<float>(i, 2);

            if (confidence > conf->minConfidenceScore) {
                int boundaryBoxX = int(results.at<float>(i, 3) * currentImage.cols);
                int boundaryBoxY = int(results.at<float>(i, 4) * currentImage.rows);
                int boundaryBoxWidth = int(results.at<float>(i, 5) * currentImage.cols - boundaryBoxX);
                int boundaryBoxHeight = int(results.at<float>(i, 6) * currentImage.rows - boundaryBoxY);
                cv::rectangle(currentImage, cv::Point(boundaryBoxX, boundaryBoxY), cv::Point(boundaryBoxX + boundaryBoxWidth, boundaryBoxY + boundaryBoxHeight), cv::Scalar(0, 255, 0), 2);
                std::string className = classNames[class_id - 1];
                cv::putText(currentImage, className + " " + std::to_string(int(confidence * 100)) + "%", cv::Point(boundaryBoxX, boundaryBoxY - 15), cv::FONT_HERSHEY_SIMPLEX, 1.5, cv::Scalar(0, 0, 255), 2);
            }
        }

        std::lock_guard<std::mutex> lock(outputImageQueueMutex);
        outputImageQueue.push(std::move(currentImage));
    }

    isProcessingFinished = true;
}

cv::Mat ImageProcessor::getNextProcessedImage()
{
    std::lock_guard<std::mutex> lock(outputImageQueueMutex);
    if (outputImageQueue.empty())
        return cv::Mat();

    cv::Mat processedImage = outputImageQueue.front();
    outputImageQueue.pop();

    return processedImage;
}

