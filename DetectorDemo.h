#pragma once
#include "opencv2/opencv.hpp"

class DetectorDemo

{
    cv::Mat _images[6];
    cv::Mat _pairs[6];
public:
    enum DetectionType
    {
        HARRIS,
        SIFT
    };
    cv::Feature2D * featureDetector = NULL;
    DetectorDemo();
    // 
    void hw1(DetectionType type = HARRIS, float sigma = 1.41);
};