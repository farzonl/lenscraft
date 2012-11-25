//#pragma once
#ifndef __X_RAY_HPP__
#define __X_RAY_HPP__
#include "Effects.hpp"

class Xray : public Effects
{

	public:
		Xray(void): Effects(){}
		void performEffect(cv::Mat &input)
		{
			if(this->effect.empty()) this->effect = input.clone();
			
			bitwise_not(input, effect);
		}
};
#endif //__X_RAY_HPP__
