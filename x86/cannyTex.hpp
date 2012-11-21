#pragma once

#include "Effects.hpp"


class CannyTex : public Effects
{

public:
	CannyTex(void): Effects(){}
	void performEffect(cv::Mat &input) 
	{
		if(this->effect.empty()) this->effect = input.clone();
		const int thresh = 40;
		//GaussianBlur(input, effect, cv::Size(3,3), 2,2, cv::BORDER_DEFAULT );
		blur( input, effect, cv::Size(3,3) );
		Canny(effect, effect,thresh,thresh*2, 3 );
		
	}
};