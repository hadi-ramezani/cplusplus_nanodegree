#ifndef IMAGE_DISPLAY_H
#define IMAGE_DISPLAY_H

#include "image_capture.h"
#include "image_processor.h"

class ImageDisplay {
public:
    void run(ImageProcessor& imageProcessor, ImageCapture& imageCapture);
};

#endif