#pragma once

#include "Effects.hpp"
#include <algorithm>

class RadialBlur : public Effects
{

public:
	RadialBlur(void): Effects(){}
	void performEffect(cv::Mat &input) 
	{
		if(this->effect.empty()) this->effect = input.clone();
		int radius = std::max(input.rows/4,1);
		
		cv::Mat res(input.size(),CV_8UC3);
		cv::Mat roi(input.size(),CV_8UC3);
		cv::Mat outer(input.size(),CV_8UC3);
		input.copyTo(outer);
		GaussianBlur( outer, outer, cv::Size(25,25), 64,64, cv::BORDER_DEFAULT );
		roi.setTo(0);
		//cv::cvtColor(input,src,CV_BGR2GRAY);

		circle(roi,cv::Point2f(roi.rows/2, roi.cols/2),radius,cv::Scalar(255, 255, 255),-1, 8, 0);
		circle(outer,cv::Point2f(roi.rows/2, roi.cols/2),radius,cv::Scalar(0, 0, 0),-1, 8, 0);


		/* extract subimage */
		bitwise_and(roi,input,res);
		//bitwise_and(src, src, res, roi);

		/*
		* do the main processing with subimage here.
		* in this example, we simply invert the subimage
		*/
		//bitwise_not(res, res);
		bitwise_or(res, outer, res);
		//bitwise_and(res, roi, res);

		effect = res;


	}
};