#pragma once
#include "opencv2/opencv.hpp"

void DebugMat(cv::Mat & matrix);

cv::Rect ApplyHomomorfism(cv::Mat &dest, cv::Mat sourceImage, cv::Mat hm);

cv::Mat ResizeToWidth(cv::Mat img, int width);