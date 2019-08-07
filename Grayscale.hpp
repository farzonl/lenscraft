//#pragma once
#ifndef __GRAY_SCALE_HPP__
#define __GRAY_SCALE_HPP__
#include "Effects.hpp"

class Grayscale : public Effects
{

	public:
		Grayscale(void): Effects(){}
		void performEffect(cv::Mat &input);
};

#endif //__GRAY_SCALE_HPP__
