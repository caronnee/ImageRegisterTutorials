// Hw.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/opencv.hpp"

#define FIRST_NAME "c:\\work\\DP1\\Hw\\testData\\pair1\\1.jpg"
#define SECOND_NAME "c:\\work\\DP1\\Hw\\testData\\pair1\\2.jpg"

#include "detectors.h"

int hwx()
{
	// opencv load images
	cv::Mat image1 = cv::imread(FIRST_NAME, CV_LOAD_IMAGE_COLOR);
	if (image1.empty())
	{
		printf("Unable to load image");
		return -1;
	}
	cv::cvtColor(image1, image1, CV_BGR2GRAY);

	ShowHarrisOriginal(image1);
	ShowDetector(image1);
	ShowHarrisNew(image1);
	// check for points ( or find )
	//cv::Feature2D  * detector  = new cv::cornerHarris();
	// check correspondences

	// SSD
	return 0;
}

#include "HomomorfismDemo.h"
#include "RemoveDistorionDemo.h"
#include "DetectorDemo.h"

int main(const char * argc, int argv)
{
    DetectorDemo demo;
    
    demo.Perform();
    //wait for key
    cv::waitKey();
    return 0;
}

