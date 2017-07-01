#pragma once

#include "opencv2/opencv.hpp"

class HomomorfismDemo
{
    cv::Mat ApplySimpleImage(cv::Mat image, cv::Mat manImage, cv::Point2f * pqrs);
    cv::Mat FindHomomorphism(cv::Mat image, cv::Mat second, cv::Point2f * pqrs1, cv::Point2f * pqrs2);

    cv::Mat _images[4];

    cv::Point2f _pqrs[4][4] =
    {
        { cv::Point2f(2110, 426),
        cv::Point2f(2149, 1495),
        cv::Point2f(3312, 1357),
        cv::Point2f(3305, 535)
        },
        { cv::Point2f(1595, 792),
        cv::Point2f(1618, 1600),
        cv::Point2f(2990, 1520),
        cv::Point2f(2988, 768)
        },
        { cv::Point2f(998, 560),
        cv::Point2f(1019, 1411),
        cv::Point2f(2408, 1478),
        cv::Point2f(2433, 408)
        },
    { cv::Point2f(0, 0),
        cv::Point2f(0, 1536),
        cv::Point2f(2560, 1536),
        cv::Point2f(2560, 0)
    }
    };
public:
    HomomorfismDemo();

    // picture on the wall
    void hw1();
    // homomorfism between two images
    void hw2();
    // custom images
    void hw3()
    {

    }
};
