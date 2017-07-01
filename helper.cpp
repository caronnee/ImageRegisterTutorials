#include "stdafx.h"
#include "helper.h"

void DebugMat(cv::Mat & matrix)
{
    for (int i = 0; i < matrix.size().width; i++)
    {
        for (int j = 0; j < matrix.size().height; j++)
        {
            printf("%.5f ", matrix.at<float>(i,j));
        }
        printf("\n");
    }
    printf("\n");
}

cv::Rect ApplyHomomorfism(cv::Mat &dest, cv::Mat sourceImage, cv::Mat hom)
{
    cv::Mat point;
    point.create(3, 1, CV_32FC1);
    float total = sourceImage.size().width * sourceImage.size().height;
    float pgr = 0;
    int w = sourceImage.size().width;
    int h = sourceImage.size().height;

    cv::Point2f corners[] = {
        cv::Point2f(0,0),
        cv::Point2f(0, h),
        cv::Point2f(w, 0),
        cv::Point2f(w,h)
    };
    cv::Rect ret(0, 0, 0, 0);

    for (int a = 0; a < 4; a++)
    {
        // forward mapping
        point.at<float>(0, 0) = corners[a].x;
        point.at<float>(1, 0) = corners[a].y;
        point.at<float>(2, 0) = 1;
        cv::Mat proj = hom * point;
        cv::Point3f projected = proj;
        projected /= projected.z;
        if (projected.x < ret.x)
            ret.x = projected.x;
        if (projected.y < ret.y)
            ret.y = projected.y;
        if (projected.x > ret.width)
            ret.width = projected.x;
        if (projected.y > ret.height)
            ret.height = projected.y;
    }
    // final check
    if (ret.x < 0)
        ret.x = 0;
    if (ret.y < 0)
        ret.y = 0;
    if (ret.width > sourceImage.size().width)
        ret.width = sourceImage.size().width;
    if (ret.height > sourceImage.size().height)
        ret.height = sourceImage.size().height;
    hom = hom.inv();

    int destW = dest.size().width;
    int destH = dest.size().height;
    for (int i = 0; i < destW; i++)
        for (int j = 0; j < destH; j++)
        {
            pgr = (i*destH + j)/ (float) (destH * destW);
            printf("Progress: %.7f\n", pgr);

            // forward mapping
            point.at<float>(0, 0) = (float)i;
            point.at<float>(1, 0) = (float)j;
            point.at<float>(2, 0) = 1;
            cv::Mat proj = hom * point;
            cv::Point3f projected = proj;
            projected /= projected.z;

            if (projected.x >= w || projected.y >= h)
                continue;

            if (projected.x < 0 || projected.y < 0)
                continue;

            dest.at<cv::Vec3b>(j, i) = sourceImage.at<cv::Vec3b>((int)projected.y, (int)projected.x);
        }

    return ret;
}

cv::Mat ResizeToWidth(cv::Mat img, int width)
{
    float scale = width /(float) img.size().width;
    int height = scale * img.size().height;
    cv::resize(img, img, cv::Size(width,height));
    return img;
}
