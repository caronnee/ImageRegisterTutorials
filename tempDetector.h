#pragma once

#include "opencv2/opencv.hpp"

class TempDetector : public Feature2D
{
	/** @brief Detects keypoints in an image (first variant) or image set (second variant).

	@param image Image.
	@param keypoints The detected keypoints. In the second variant of the method keypoints[i] is a set
	of keypoints detected in images[i] .
	@param mask Mask specifying where to look for keypoints (optional). It must be a 8-bit integer
	matrix with non-zero values in the region of interest.
	*/
	CV_WRAP virtual void detect(cv::InputArray image,
		CV_OUT std::vector<cv::KeyPoint>& keypoints,
		cv::InputArray mask = cv::noArray())
	{
		// TODO
	}

	/** @overload
	@param images Image set.
	@param keypoints The detected keypoints. In the second variant of the method keypoints[i] is a set
	of keypoints detected in images[i] .
	@param masks Masks for each input image specifying where to look for keypoints (optional).
	masks[i] is a mask for images[i].
	*/
	CV_WRAP virtual void detect(cv::InputArrayOfArrays images,
		CV_OUT std::vector<std::vector<cv::KeyPoint> >& keypoints,
		cv::InputArrayOfArrays masks = cv::noArray())
	{
		/*for (int i = 0; i < images.size(); i++)
		{
		std::vector<cv::KeyPoint> keypoint;
		detect(images[i], keypoint, masks);
		keypoints.push_back(keypoint);
		}*/
	}

	/** @brief Computes the descriptors for a set of keypoints detected in an image (first variant) or image set
	(second variant).

	@param image Image.
	@param keypoints Input collection of keypoints. Keypoints for which a descriptor cannot be
	computed are removed. Sometimes new keypoints can be added, for example: SIFT duplicates keypoint
	with several dominant orientations (for each orientation).
	@param descriptors Computed descriptors. In the second variant of the method descriptors[i] are
	descriptors computed for a keypoints[i]. Row j is the keypoints (or keypoints[i]) is the
	descriptor for keypoint j-th keypoint.
	*/
	CV_WRAP virtual void compute(cv::InputArray image,
		CV_OUT CV_IN_OUT std::vector<cv::KeyPoint>& keypoints,
		cv::OutputArray descriptors)
	{

	}

	/** @overload

	@param images Image set.
	@param keypoints Input collection of keypoints. Keypoints for which a descriptor cannot be
	computed are removed. Sometimes new keypoints can be added, for example: SIFT duplicates keypoint
	with several dominant orientations (for each orientation).
	@param descriptors Computed descriptors. In the second variant of the method descriptors[i] are
	descriptors computed for a keypoints[i]. Row j is the keypoints (or keypoints[i]) is the
	descriptor for keypoint j-th keypoint.
	*/
	CV_WRAP virtual void compute(cv::InputArrayOfArrays images,
		CV_OUT CV_IN_OUT std::vector<std::vector<cv::KeyPoint> >& keypoints,
		cv::OutputArrayOfArrays descriptors)
	{

	}

	/** Detects keypoints and computes the descriptors */
	CV_WRAP virtual void detectAndCompute(cv::InputArray image, cv::InputArray mask,
		CV_OUT std::vector<cv::KeyPoint>& keypoints,
		cv::OutputArray descriptors,
		bool useProvidedKeypoints = false)
	{

	}

	CV_WRAP virtual int descriptorSize() const
	{
		return 0;
	}
	CV_WRAP virtual int descriptorType() const
	{
		return 0;
	}
	CV_WRAP virtual int defaultNorm() const
	{
		return 0;
	}

	virtual void write(cv::FileStorage&) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual void read(const cv::FileNode&) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}


	virtual bool empty() const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}
};
