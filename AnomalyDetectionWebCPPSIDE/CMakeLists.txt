cmake_minimum_required(VERSION 3.15.3)
project(AnomalyDetectionWebCPPSIDE)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )

add_executable(AnomalyDetectionWebCPPSIDE main.cpp anomaly_detection_util.cpp timeseries.cpp SimpleAnomalyDetector.cpp minCircle.cpp HybridAnomalyDetector.cpp CLI.cpp Server.cpp)
