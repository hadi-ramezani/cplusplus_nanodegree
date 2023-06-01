cmake_minimum_required(VERSION 2.8)
project( DNN )
find_package( OpenCV 4.1 REQUIRED )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

#json
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(src/json)


# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

add_executable( ObjectDetection ${project_SRCS} )
target_link_libraries( ObjectDetection ${OpenCV_LIBS} nlohmann_json::nlohmann_json)