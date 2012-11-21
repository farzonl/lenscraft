#include "Effects.hpp"

class Contrast : public Effects
{
	float contrast;
	int brightness;
	public:
		Contrast(void): Effects(),contrast(1.9f),brightness(5){}
		void performEffect(cv::Mat &input);
};