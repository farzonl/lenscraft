#ifndef __CONTRAST_HPP__
#define __CONTRAST_HPP__
#include "Effects.hpp"

class Contrast : public Effects
{
	float contrast;
	int brightness;
	public:
		Contrast(void): Effects(),contrast(1.9f),brightness(5){}
		void performEffect(cv::Mat &input);
};
#endif //__CONTRAST_HPP__
