#include "stdafx.h"
#include "detectors.h"

void ShowDetected(cv::Mat image, std::vector< cv::KeyPoint> keys, const char * title)
{
	cv::cvtColor(image, image, CV_GRAY2BGR);

	for (int i = 0; i < keys.size(); i++)
	{
		cv::KeyPoint & key = keys[i];
		circle(image, key.pt, 5, cv::Scalar(0xff, 0, 0), 1, 8, 0);
	}

	cv::resize(image, image, cv::Size(300, 300));

	cv::namedWindow(title, cv::WINDOW_AUTOSIZE);
	cv::imshow(title, image);
}

void ShowSift(cv::Mat greyImage)
{
	
}

void ShowDetector(cv::Mat greyImage)
{
	cv::Ptr<cv::Feature2D> detector = cv::FastFeatureDetector::create();
	std::vector< cv::KeyPoint> points;
	detector->detect(greyImage, points);
	ShowDetected(greyImage, points, "Fast Feature Detector");
}

void ShowHarrisNew(cv::Mat greyImage)
{
 //   cv::Ptr<cv::Feature2D> detector = cv::Ptr::nul;// MyHarris::create();
	//std::vector< cv::KeyPoint> points;
	//detector->detect(greyImage, points);
	//ShowDetected(greyImage, points, "Orb Detector");
}

void ShowHarrisOriginal(cv::Mat greyImage)
{
	cv::Mat output;
	int blockSize = 2;
	int apertureSize = 3;
	double k = 0.04;

	cv::Mat dst_norm, dst_norm_scaled;

	/// Detecting corners
	cv::cornerHarris(greyImage, output, blockSize, apertureSize, k, cv::BORDER_DEFAULT);

	/// Normalizing
	cv::normalize(output, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
	cv::convertScaleAbs(dst_norm, dst_norm_scaled);

	float thresh = 100;
	std::vector<cv::KeyPoint> keys;
	for (int j = 0; j < dst_norm.rows; j++)
	{
		for (int i = 0; i < dst_norm.cols; i++)
		{
			if ((int)dst_norm.at<float>(j, i) > thresh)
			{
				cv::KeyPoint key;
				key.pt.x = i;
				key.pt.y = j;
				keys.push_back(key);
				
			}
		}
	}
	ShowDetected(greyImage, keys, "CornersHarris");
}
