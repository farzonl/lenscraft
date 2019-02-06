//#pragma once

#ifndef __SOBEL_TEX_HPP__
#define __SOBEL_TEX_HPP__

#include "Effects.hpp"


class SobelTex : public Effects
{

public:
	SobelTex(void): Effects(){}
	void performEffect(cv::Mat &input) 
	{
		if(this->effect.empty()) this->effect = input.clone();

		cv::Mat src = input.clone();
		cv::Mat src_gray;

		const  int scale = 1, delta = 0, ddepth = CV_16S;

		GaussianBlur( src, src, cv::Size(3,3), 0, 0, cv::BORDER_DEFAULT );
		/// Convert it to gray
		cvtColor( src, src_gray, CV_RGB2GRAY );

		/// Generate grad_x and grad_y
		cv::Mat grad_x, grad_y;
		cv::Mat abs_grad_x, abs_grad_y;
		/// Gradient X
		Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
		convertScaleAbs( grad_x, abs_grad_x );
		/// Gradient Y
		Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
		convertScaleAbs( grad_y, abs_grad_y );
		/// Total Gradient (approximate)
		addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, effect );

	}
};
#endif //__SOBEL_TEX_HPP__
