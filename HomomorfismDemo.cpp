#include "stdafx.h"
#include "HomomorfismDemo.h"
#include "helper.h"

cv::Mat HomomorfismDemo::ApplySimpleImage(cv::Mat image, cv::Mat manImage, cv::Point2f * pqrs)
{
    cv::Mat ret = image.clone();

    cv::Mat hom = cv::Mat::zeros(cv::Size(3, 3), CV_32FC1);
    hom.create(3, 3, CV_32FC1);
    // a1 a2 pqrs[0].x 0 
    // a3 a4 pqrs[0].y 1 
    // 0  0  1         1
    hom.at<float>(0, 0) = (pqrs[3].x - pqrs[0].x) / manImage.size().width;
    hom.at<float>(0, 1) = (pqrs[1].x - pqrs[0].x) / manImage.size().height;
    hom.at<float>(0, 2) = pqrs[0].x;
    hom.at<float>(1, 0) = (pqrs[3].y - pqrs[0].y) / manImage.size().width;
    hom.at<float>(1, 1) = (pqrs[1].y - pqrs[0].y) / manImage.size().height;
    hom.at<float>(1, 2) = pqrs[0].y;
    hom.at<float>(2, 0) = 0;
    hom.at<float>(2, 1) = 0;
    hom.at<float>(2, 2) = 1;
    return hom;
}

cv::Mat HomomorfismDemo::FindHomomorphism(cv::Mat image, cv::Mat second, cv::Point2f * x, cv::Point2f * p)
{
    // find homography between 
    cv::Mat eh, image2, b;
    eh.create(8, 8, CV_32FC1);
    b.create(8, 1, CV_32FC1);
    for (int i = 0; i < 4; i++)
    {
        eh.at<float>(2 * i, 0) = x[i].x;
        eh.at<float>(2 * i, 1) = x[i].y;
        eh.at<float>(2 * i, 2) = 1;
        eh.at<float>(2 * i, 3) = 0;
        eh.at<float>(2 * i, 4) = 0;
        eh.at<float>(2 * i, 5) = 0;
        eh.at<float>(2 * i, 6) = -x[i].x*p[i].x;
        eh.at<float>(2 * i, 7) = -x[i].y*p[i].x;

        eh.at<float>(2 * i + 1, 0) = 0;
        eh.at<float>(2 * i + 1, 1) = 0;
        eh.at<float>(2 * i + 1, 2) = 0;
        eh.at<float>(2 * i + 1, 3) = x[i].x;
        eh.at<float>(2 * i + 1, 4) = x[i].y;
        eh.at<float>(2 * i + 1, 5) = 1;
        eh.at<float>(2 * i + 1, 6) = -x[i].x*p[i].y;
        eh.at<float>(2 * i + 1, 7) = -x[i].y*p[i].y;

        b.at<float>(2 * i) = p[i].x;
        b.at<float>(2 * i + 1) = p[i].y;
    }

    eh = eh.inv();
    cv::Mat h = eh * b;
    cv::Mat ret;
    ret.create(3, 3, CV_32FC1);
    float a = ret.at<float>(0,0) = h.at<float>(0);
    a = ret.at<float>(0,1) = h.at<float>(1);
    a = ret.at<float>(0,2) = h.at<float>(2);
    a = ret.at<float>(1,0) = h.at<float>(3);
    a = ret.at<float>(1,1) = h.at<float>(4);
    a = ret.at<float>(1,2) = h.at<float>(5);
    a = ret.at<float>(2,0) = h.at<float>(6);
    a = ret.at<float>(2,1) = h.at<float>(7);
    a = ret.at<float>(2,2) = 1;
    return ret;
}

HomomorfismDemo::HomomorfismDemo()
{
    // 
    std::string folder("data\\Homomorfism\\");
    const char * names[] =
    {
        "1.jpg" ,
        "2.jpg",
        "3.jpg",
        "Seinfeld.jpg"
    };

    // three for testing, one for projection
    for (int i = 0; i < 4; i++)
    {
        cv::Mat img = cv::imread(folder + names[i], CV_LOAD_IMAGE_COLOR);
        float f = 500.f / img.size().width;
        float newH = img.size().height *f;
        cv::resize(img, img, cv::Size(500, (int)newH));
        _images[i] = img;
        
        for (int a = 0; a < 4; a++)
        {
            _pqrs[i][a] *= f;
        }
    }
}

void HomomorfismDemo::hw1()
{
    // projection of the fourth image into the pqrs squares
    for (int i = 0; i < 3; i++)
    {
        cv::Mat hom = ApplySimpleImage(_images[i], _images[3], _pqrs[i]);
        cv::Mat img = _images[i].clone();
        ApplyHomomorfism(img, _images[3], hom);
        float f = 500.f / img.size().width;
        float newH = img.size().height *f;
        cv::resize(img, img, cv::Size(500, (int)newH));;
        cv::imshow("output", img);
        cv::waitKey();
    }
}

#define FIRST 3
#define SECOND 0

void HomomorfismDemo::hw2()
{
    cv::Mat hom = FindHomomorphism(_images[FIRST], _images[SECOND], _pqrs[FIRST], _pqrs[SECOND]);
    
    cv::Mat img;
    img.create(_images[FIRST].size(), CV_8UC3);
    ApplyHomomorfism(img, _images[FIRST], hom);

    cv::imshow("Second", _images[SECOND]);

    cv::imshow("Source", _images[FIRST]);

    cv::imshow("Transformed", img);
    cv::waitKey();
}
