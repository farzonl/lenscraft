#include "Xray.hpp"

/*void Xray::performEffect(cv::Mat &input)
{  
	cv::Vec4b min(255,255,255, 0);
	cv::Vec4b max(  0,  0,  0, 255);

	//this->effect = cv::Mat::zeros(input.cols,input.rows, CV_8UC4);
	if(this->effect.empty()) this->effect = input.clone();

	
	//std::vector <cv::Mat> planes;
	//cv::split(input, planes); // Partition image into three channel planes
	
	//for(int i = 0; i < 3; i++)
	//{
	//	double minVal, maxVal; 
	//	cv::minMaxLoc(planes[0], &minVal, &maxVal, NULL, NULL);
	//	min[i] = (char)(int)minVal;
	//	max[i] = (char)(int)maxVal;
	//}
	
	for (int row  = 0; row < input.rows; row++)
	{
		for (int col = 0; col < input.cols; col++)
		{
			const cv::Vec4b& src = input.at<cv::Vec4b>(row, col);

			min[0] = std::min(min[0], src[0]);
			min[1] = std::min(min[1], src[1]);
			min[2] = std::min(min[2], src[2]);
			//min[3] = std::min(min[3], src[3]);

			max[0] = std::max(max[0], src[0]);
			max[1] = std::max(max[1], src[1]);
			max[2] = std::max(max[2], src[2]);
			//max[3] = std::max(max[3], src[3]);
		}
	}

	for (int row  = 0; row < input.rows; row++)
	{
		for (int col = 0; col < input.cols; col++)
		{
			cv::Vec4b result = (max - input.at<cv::Vec4b>(row, col)) + min;
			//result[3] = 0xFF;
			this->effect.at<cv::Vec4b>(row, col)	= result;
		}
	}
	//cv::imshow("xray", effect);
}*/