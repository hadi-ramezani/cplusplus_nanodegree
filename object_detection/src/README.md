# CPPND: Deploy an Object Detection DNN Model

## Overview

In this project, I chose option 1 and implemented a program to deploy a pre-trained object detection deep neural network (DNN) model. The program captures a live video using the computer's webcam, processes the frames by passing them to the DNN model, identifies the objects and draws a box around each object, and displays the video in real time. Below are some of the features currently implemented:

- The program uses separate threads to capture and process the frames while maintaining the order of original frames.
- The program include several classes namely:
    + Configuration: To parse the configuration file provided by the user
    + ImageCapture: To capture the images coming through the webcam
    + ImageProcessor: To process the images by passing them through the DNN model.
    + ImageDisplay: To display the processed video/images.
- The programs accepts a json file from the user to customize its behavior. Currently, the following fields are supported:
    + model_path: The full path to the model file in .pb format
    + metadata_path: The full path to the model metadata
    + class_path: The full path to the list of classes the model is able to detect
    + min_confidence_score: The minimum confidence score for program to detect an object.


## Dependencies 
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 3.81
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)


## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Prepare a json configuration file - see the "config" folder for an example
4. Run it: `./ObjectDetection <full path to a json file>`.


## Project Rubic
The project meets all the required rubic points. Additionally, the following rubic points are met:

**Loops, Functions, I/O**
- The project demonstrates an understanding of C++ functions and control structures.
    - The program uses functions and methods throughout the code base
- The project reads data from a file and process the data, or the program writes data to a file.
    - The program reads a configuration file in json format (see configuration.cpp)
    - The program reads a DNN model along with metadata and classes from files (see main.cpp line 41 and image_processor.cpp)
- The project accepts user input and processes the input.
    - The program accepts a configuration file from the users to customize its behavior (see configuration.h and configuration.cpp)

**Object Oriented Programming**
- The project uses Object Oriented Programming techniques.
    - The program is designed to use several classes with simple interfaces 
- Classes use appropriate access specifiers for class members.
    - See any .h files for class member declaration  
- Class constructors utilize member initialization lists.
    - See image_processor.h line 16

**Memory Management**
- The project uses move semantics to move data, instead of copying it, where possible.
    - See image_processor.cpp line 57 

**Concurrency**
- The project uses multithreading.
    - The program uses a separate thread to capture and process the images. See main.cpp lines 43-60.
- A mutex or lock is used in the project.
    - I have used mutex and lock in several places. For an example, see image_processor.cpp line 56 
- A condition variable is used in the project
    - For an example see image_capture.cpp lines 22-25.


## References
https://www.youtube.com/watch?v=tjzJs9rOeEM&ab_channel=NicolaiNielsen
