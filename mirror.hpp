//#pragma once
#ifndef __MIRROR_HPP__
#define __MIRROR_HPP__
#include "Effects.hpp"


class Mirror : public Effects
{

public:
	Mirror(void): Effects(){}
	void performEffect(cv::Mat &input) 
	{
		if(this->effect.empty()) this->effect = input.clone();
		effect.setTo(0);
		cv::Mat left  = input(cv::Rect(0,0,input.cols/2,input.rows));
		cv::Mat right;
		cv::flip(left,right,1);
		left.copyTo(effect(cv::Rect(0,0, input.cols/2, input.rows)));
		right.copyTo(effect(cv::Rect(input.cols/2,0, input.cols/2, input.rows)));

	}
};
#endif // __MIRROR_HPP__
