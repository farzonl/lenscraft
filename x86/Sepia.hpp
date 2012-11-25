//#pragma once
#ifndef __SEPIA_HPP__
#define __SEPIA_HPP__

#include "Effects.hpp"

//const float sepia_data[] = {0.272,  0.534,  0.131, 0,0.349, 0.686, 0.168,0,0.393,0.769,0.189,0,0,0,0,1};

class Sepia : public Effects
{
	cv::Mat m_sepiaKernel;
	public:
		Sepia(void): Effects() , m_sepiaKernel(4, 4,CV_32F,0.0f)
		{
			m_sepiaKernel.at<float>(0,0) = 0.272f; m_sepiaKernel.at<float>(0,1) = 0.534f; m_sepiaKernel.at<float>(0,2) = 0.131f; m_sepiaKernel.at<float>(0,3) = 0.0f;
			m_sepiaKernel.at<float>(1,0) = 0.349f; m_sepiaKernel.at<float>(1,1) = 0.686f; m_sepiaKernel.at<float>(1,2) = 0.168f; m_sepiaKernel.at<float>(1,3) = 0.0f;
			m_sepiaKernel.at<float>(2,0) = 0.393f; m_sepiaKernel.at<float>(2,1) = 0.769f; m_sepiaKernel.at<float>(2,2) = 0.189f; m_sepiaKernel.at<float>(2,3) = 0.0f;
			m_sepiaKernel.at<float>(3,0) = 0.0f;   m_sepiaKernel.at<float>(3,1) = 0.0f;   m_sepiaKernel.at<float>(3,2) = 0.0f;   m_sepiaKernel.at<float>(3,3) = 1.0f;
		}
		void performEffect(cv::Mat &input);
		~Sepia() {}
};
#endif //__SEPIA_HPP__
