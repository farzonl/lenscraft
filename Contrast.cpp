#include "Contrast.hpp"

void Contrast::performEffect(cv::Mat &input)
{
	//this->effect = cv::Mat::zeros(input.cols,input.rows, CV_8UC4);
	if(this->effect.empty()) this->effect = input.clone();
	/*cv::Mat m_contrastKernel = cv::Mat::eye(4,4,input.depth());
	m_contrastKernel.at<float>(0,0) = m_contrastKernel.at<float>(1,1) = m_contrastKernel.at<float>(2,2) = contrast;
	cv::transform(input, effect, m_contrastKernel);
	effect = effect + cv::Scalar(brightness, brightness, brightness, 0);*/

	/*for( int y = 0; y < input.rows; y++ )
	{ 
		for( int x = 0; x < input.cols; x++ )
		{ 
			for( int c = 0; c < 3; c++ )
			{
				this->effect.at<Vec3b>(y,x)[c] =
					saturate_cast<uchar>( contrast*( input.at<Vec3b>(y,x)[c] ) + brightness);
			}
		}
	}*/
	input.convertTo(this->effect, -1, contrast, brightness);
}