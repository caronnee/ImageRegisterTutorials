#include "stdafx.h"
#include "DetectorDemo.h"
#include "helper.h"

DetectorDemo::DetectorDemo()
{
    std::string folder("data\\detector\\");
    const char * names[] =
    {
    "pair1\\1.jpg",
    "pair1\\2.jpg",
    "pair2\\1.jpg",
    "pair2\\2.jpg",
    "pair3\\1.jpg",
    "pair3\\2.jpg"
    };
    for (int i = 0; i < 6; i++)
    {
        _images[i] = cv::imread(folder + names[i], CV_LOAD_IMAGE_COLOR);
        cv::Mat grey;
        cv::cvtColor(_images[i], grey, CV_BGR2GRAY);
        grey.convertTo(_pairs[i], CV_32FC1);
    }
}

#include "HarrisDetector.h"
#include "SiftDetector.h"

#define IMAGE_INDEX 0
#define THRESHOLD 0.99

void DetectorDemo::Perform(DetectionType type /*= HARRIS*/, float sigma)
{
    if (type == HARRIS)
    {
        featureDetector = new HarrisDetector(HarrisDetector::Haar, sigma, THRESHOLD );
    }
    if (type == SIFT)
    {
        featureDetector = new SiftDetector(sigma);
    }
    std::vector<cv::KeyPoint> keypoints[2];
    featureDetector->detect(_pairs[2* IMAGE_INDEX], keypoints[0]);
    // find max/min
    ////featureDetector->detect(_pairs[IMAGE_INDEX*2 +1], keypoints[1]);
    cv::Mat image = ResizeToWidth(_images[IMAGE_INDEX].clone(), 500);
    cv::Scalar color(255,255, 0);
    cv::imshow("Original image", image);
    cv::Mat simage = _images[IMAGE_INDEX].clone();
    for (int i = 0; i < keypoints[0].size(); i++)
    {
        cv::circle(simage, keypoints[0][i].pt, 5, color, 1);
    }
    //simage = ResizeToWidth(simage, 500);
    cv::imshow("Detected in first image", simage);
}
