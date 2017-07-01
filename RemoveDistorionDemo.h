#pragma once
#include "opencv2/opencv.hpp"

#define IMAGES 3
class RemoveDistorionDemo
{
    cv::Mat _images[IMAGES];
    cv::Point2f _debugpoints[3][8] =
    {
        {
                cv::Point2f(328,267),cv::Point2f(418,245),
                cv::Point2f(320,342),cv::Point2f(416,324),
                cv::Point2f(328,267),cv::Point2f(320,342),
                cv::Point2f(418,245),cv::Point2f(416,324)
        },
        {
            cv::Point2f(288,108),cv::Point2f(446,104),
            cv::Point2f(253,368),cv::Point2f(418,386),
            cv::Point2f(288,108),cv::Point2f(253,368),
            cv::Point2f(446,104),cv::Point2f(418,386)
        },
        {
            cv::Point2f(250,396),cv::Point2f(335,396),
            cv::Point2f(602,196),cv::Point2f(708,196),
            cv::Point2f(250,396),cv::Point2f(165,250),
            cv::Point2f(602,196),cv::Point2f(590,326)
        }
    };

    cv::Point3f _lines[IMAGES][4] =
    {
        {
            cv::Point3f(328,267,1).cross(cv::Point3f(418,245,1)),
            cv::Point3f(320,342,1).cross(cv::Point3f(416,324,1)),

            cv::Point3f(328,267,1).cross(cv::Point3f(320,342,1)),
            cv::Point3f(418,245,1).cross(cv::Point3f(416,324,1))
        },
        {
            cv::Point3f(288,108,1).cross(cv::Point3f(446,104,1)),
            cv::Point3f(253,368,1).cross(cv::Point3f(418,386,1)),

            cv::Point3f(288,108,1).cross(cv::Point3f(253,368,1)),
            cv::Point3f(446,104,1).cross(cv::Point3f(418,386,1))
        },
        {
            cv::Point3f(250,396,1).cross(cv::Point3f(335,396,1)),
            cv::Point3f(602,196,1).cross(cv::Point3f(708,196,1)),

            cv::Point3f(250,396,1).cross(cv::Point3f(165,250,1)),
            cv::Point3f(602,196,1).cross(cv::Point3f(590,326,1))
        },
    };
public:

    RemoveDistorionDemo();

    // remove projective distortion - double step method
    void hw1();

    // remove projective distorion - single steo method
    void hw2();
};