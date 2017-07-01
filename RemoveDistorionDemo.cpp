#include "stdafx.h"
#include "RemoveDistorionDemo.h"
#include "helper.h"

RemoveDistorionDemo::RemoveDistorionDemo()

{
    // 
    std::string folder("data\\projection\\");
    const char * names[] =
    {
        "flatiron.jpg" ,
        "monalisa.jpg" ,
        "wideangle.jpg",
    };

    // three for testing, one for projection
    for (int i = 0; i < 3; i++)
    {
        cv::Mat img = cv::imread(folder + names[i], CV_LOAD_IMAGE_COLOR);
        //float f = 500.f / img.size().width;
        //float newH = img.size().height *f;
        //cv::resize(img, img, cv::Size(500, (int)newH));
        /*for (int a = 0; a < 4; a++)
        {
            cv::circle(img, debugpoints[a], 7, cv::Scalar(255, 255, 0),4);
        }*/
        _images[i] = img;
    }
}

// two step method 
#define IMAGE 0
void RemoveDistorionDemo::hw1()
{
    // show images and lines
   
    // find projective distortion
    // find line at infinity
    cv::Point3f infinityPoint1 = _lines[IMAGE][0].cross(_lines[IMAGE][1]);
    cv::Point3f infinityPoint2 = _lines[IMAGE][2].cross(_lines[IMAGE][3]);
    cv::Point3f infinityLine = infinityPoint2.cross(infinityPoint1);
    infinityLine /= sqrt(infinityLine.dot(infinityLine));
    cv::Mat homomorfism = cv::Mat::zeros(3, 3, CV_32FC1);
   
    homomorfism.at<float>(0, 0) = 1;
    homomorfism.at<float>(1, 1) = 1;
    homomorfism.at<float>(2, 0) = infinityLine.x;
    homomorfism.at<float>(2, 1) = infinityLine.y;
    homomorfism.at<float>(2, 2) = infinityLine.z;

    cv::Mat image = cv::Mat::zeros(_images[IMAGE].size(), CV_8UC3);
    //cv::Rect r = ApplyHomomorfism(image, _images[IMAGE], homomorfism);
    //image = image(r);

   // cv::Mat projective = ResizeToWidth(image.clone(), 500);

    // we have two line ortogonal
// calculate matrix S from conic ( 1,0
    // 0,1,
    // 0,0
    cv::Mat m;
    m.create(2, 2, CV_32FC1);
    m.at<float>(0, 0) = _lines[IMAGE][0].x*_lines[IMAGE][2].x;
    m.at<float>(0, 1) = _lines[IMAGE][0].x*_lines[IMAGE][2].y + _lines[IMAGE][0].x*_lines[IMAGE][2].y;
    m.at<float>(1, 0) = _lines[IMAGE][1].x*_lines[IMAGE][3].x;
    m.at<float>(1, 1) = _lines[IMAGE][1].x*_lines[IMAGE][3].y + _lines[IMAGE][1].x*_lines[IMAGE][3].y;

    cv::Mat b = cv::Mat::zeros(2, 1, CV_32FC1);
    b.at<float>(0) = -_lines[IMAGE][0].y * _lines[IMAGE][2].y;
    b.at<float>(1) = -_lines[IMAGE][1].y * _lines[IMAGE][3].y;
    m = m.inv();
    b = m * b; // s22 is 1
    
    m.at<float>(0, 0) = b.at<float>(0);
    m.at<float>(0, 1) = b.at<float>(1);
    m.at<float>(1, 0) = b.at<float>(1);
    m.at<float>(1, 1) = 1.0;
    cv::Mat u, vt, d;
    cv::SVD::compute(m, d, u, vt, cv::SVD::FULL_UV );
    cv::transpose(u,vt);
   
    cv::Mat w= cv::Mat::zeros(2, 2, CV_32FC1);
    float ddd = d.at<float>(0);
    float ddd2 = d.at<float>(1);
    w.at<float>(0, 0) = sqrt(d.at<float>(0));
    w.at<float>(1, 1) = sqrt(d.at<float>(1));
    cv::Mat a = u*w*vt;
    cv::Rect rect(0, 0, 2, 2);
    homomorfism(rect) = a;
    float aa = a.at<float>(0, 0);
    float ab = a.at<float>(1, 0);
    float ac = a.at<float>(0, 1);
    float ad = a.at<float>(1, 1);

    ApplyHomomorfism(image, _images[IMAGE], homomorfism);
    cv::Mat affine = ResizeToWidth(image.clone(), 500);
    cv::imshow("Source", _images[IMAGE]);
    //cv::imshow("Transformed projective", projective);
    cv::imshow("Transformed affine", affine);


}

// one step method
void RemoveDistorionDemo::hw2()
{

}
