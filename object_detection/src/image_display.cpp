#include "image_display.h"
#include "image_processor.h"

void ImageDisplay::run(ImageProcessor& imageProcessor, ImageCapture& imageCapture)
{
    while (true) {
        cv::Mat currentImage = imageProcessor.getNextProcessedImage();
        if (currentImage.empty() && imageCapture.isFinished() && imageProcessor.isFinished()) // Use the isFinished() getter
            break;

        if (currentImage.size().width > 0 && currentImage.size().height > 0)
            cv::imshow("Video", currentImage);

        // Check for key press
        int key = cv::waitKey(10);
        if (key == 'q' || key == 27) { // 'q' or escape key
            break;
        }
    }

    cv::destroyAllWindows();
}