#include "stdafx.h"
#include "HarrisDetector.h"
#include "helper.h"

HarrisDetector::HarrisDetector(BorderType type, float sigma, float threshold)
{
    _threshold = threshold;
	_type = type;
    _sigma = sigma;
    if (type == Haar)
    {
        // create haar matric for detecting
        int size = ceil(sigma * 4 );
        if (size & 1)
            size++;
        _filter.create(cv::Size(size, size), CV_32FC1);
        for (int i = 0; i < size/2; i++)
            for (int j = 0; j < size; j++)
            {
                _filter.at<float>( j, i) = 1;
            }
        for (int i = size / 2 ; i < size; i++)
            for (int j = 0 ; j < size; j++)
            {
                _filter.at<float>(j, i) = -1;
            }
    }
}

#define SHOW_MATS 0
#define DEBUG_DET 0
#if DEBUG_DET
#define TEST_ROW 1245
#define TEST_COL 461
#define TEST_COEF 20
#endif 

CV_WRAP void HarrisDetector::detect(cv::InputArray im, CV_OUT std::vector<cv::KeyPoint>& keypoints, cv::InputArray mask /*= cv::noArray()*/)
{
    cv::Mat image = im.getMat();
    //apply the filter to the image in the x direction
    cv::Mat xDirection;
    // convolve
    cv::Rect rect;
    int startX = _filter.size().width / 2;
    int startY = _filter.size().height / 2;
    int endX = image.size().width - _filter.size().width;
    int endY = image.size().height - _filter.size().height;

    rect.x = startX;
    rect.y = startY;
    rect.width = _filter.size().width;
    rect.height = _filter.size().height;

    cv::Mat dirX = cv::Mat::zeros(image.size(), CV_32FC1);
    cv::Mat dirY = cv::Mat::zeros(image.size(), CV_32FC1);
    // perform convolution
    cv::Mat dxx, dxy, dyy;
    dxx = cv::Mat::zeros(image.size(), CV_32FC1);
    dxy = cv::Mat::zeros(image.size(), CV_32FC1);
    dyy = cv::Mat::zeros(image.size(), CV_32FC1);

    cv::Mat tFilter;
    cv::transpose(_filter, tFilter);
#ifdef TEST_COEF
    startX = TEST_ROW - TEST_COEF;
    endX = TEST_ROW + TEST_COEF;
    startY = TEST_COL - TEST_COEF;
    endY = TEST_COL + TEST_COEF;
#endif

    for (int j = startX; j < endX; j++)
    {
        for (int i = startY; i < endY; i++)
        {
            rect.x = j;
            rect.y = i;
            cv::Mat m = image(rect);
#if SHOW_MATS
            DebugMat(m);
#endif
            cv::Mat test = m.mul(_filter);
            cv::Mat tTest = m.mul(tFilter);
#if SHOW_MATS
            DebugMat(tTest);
            DebugMat(test);
#endif
            float dx = cv::sum(test)[0];
            float dy = cv::sum(tTest)[0];
#if TEST_COEF
            printf("%.2f, %.2f ( %d %d )\n", dx, dy, j, i);
#endif
            // build integral image
            dxx.at<float>(i, j) = dx * dx;//+ dxx.at<float>(i, j - 1) + dxx.at<float>(i - 1, j) + dxx.at<float>(i - 1, j - 1);
            dxy.at<float>(i, j) = dx * dy;// +dxy.at<float>(i, j - 1) + dxy.at<float>(i - 1, j) + dxy.at<float>(i - 1, j - 1);
            dyy.at<float>(i, j) = dy * dy;// +dyy.at<float>(i, j - 1) + dyy.at<float>(i - 1, j) + dyy.at<float>(i - 1, j - 1);
        }
    }
    int n = ceil(_sigma * 5 +0.5)/2;

    startX += n;
    startY += n;
    endX -= n;
    endY -= n;
    // calculate C
    cv::Rect rct;
    rct.width = 2 * n;
    rct.height = 2 * n;
    cv::Mat C = cv::Mat::zeros(2, 2, CV_32FC1);
    float maxT = -FLT_MAX;
    float minT = FLT_MIN;
    for (int j = startX ; j < endX; j++)
    {
        for (int i = startY; i < endY; i++)
        {
            rct.x = j - n;
            rct.y = i - n;
            C.at<float>(0, 0) = cv::sum( dxx(rct) )[0];
            float xy = cv::sum(dxy(rct))[0];
            C.at<float>(0, 1) = xy;
            C.at<float>(1, 0) = xy;
            C.at<float>(1, 1) = cv::sum(dyy(rct))[0];
            /* C.at<float>(0, 0) = dxx.at<float>(i + n, j + n) - dxx.at<float>(i-n, j + n) - dxx.at<float>(i + n, j-n) + dxx.at<float>(i-n, j - n);
             float xy = dxy.at<float>(i + n, j + n) - dxy.at<float>(i-n, j + n) - dxy.at<float>(i + n, j -n) + dxy.at<float>(i-n, j - n);
             C.at<float>(0, 1) = xy;
             C.at<float>(1,0) = xy;
             C.at<float>(1, 1) = dyy.at<float>(i + n, j + n) - dyy.at<float>(i -n, j + n) - dyy.at<float>(i + n, j-n) + dyy.at<float>(i, j + n);*/
            // calculate ratio
            float tr = cv::trace(C)[0];
            float testThreshold = cv::determinant(C) / (tr*tr);

#if TEST_COEF
            DebugMat(C);
            printf(" Threshold: %f ( %d %d )\n", testThreshold, j - n, i - n);

#endif        
                // add to the interesting point
                cv::KeyPoint keypoint;
                keypoint.octave = 0;
                keypoint.pt.x = j;
                keypoint.pt.y = i;
                keypoint.response = testThreshold;
                keypoints.push_back(keypoint);
            if (minT > testThreshold)
                minT = testThreshold;
            if (maxT < testThreshold)
                maxT = testThreshold;
        }
    }
    int iKey = 0;
    while (iKey < keypoints.size())
    {
        if (keypoints[iKey].response < minT + (maxT - minT) * _threshold)
        {
            keypoints[iKey] = keypoints.back();
            keypoints.pop_back();
        }
        else
        {
            iKey++;
        }
    }
}
