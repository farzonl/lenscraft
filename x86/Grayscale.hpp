//#pragma once
#ifndef __GRAY_SCALE_HPP__
#define __GRAY_SCALE_HPP__
#include "Effects.hpp"

class Grayscale : public Effects
{

	public:
		Grayscale(void): Effects(){}
		void performEffect(cv::Mat &input) 
		{
			if(this->effect.empty()) effect = input.clone();
			//cv::cvtColor(input,this->effect,CV_RGB2GRAY);
			cv::cvtColor(input,this->effect,CV_BGR2GRAY);
		}
};

#endif //__GRAY_SCALE_HPP__
