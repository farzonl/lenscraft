#include "Sepia.hpp"

void Sepia::performEffect(cv::Mat &input)
{
	if(this->effect.empty()) this->effect = input.clone();
	this->effect = cv::Mat::zeros(input.rows,input.cols, CV_32FC4);

	cv::transform(input, this->effect, m_sepiaKernel);
	//cv::imshow("sepia", effect);
	//cv::waitKey(0);
}