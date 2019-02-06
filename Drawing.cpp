#include "Drawing.hpp"

void Drawing::performEffect(cv::Mat &input)
{
	//if(this->effect.empty()) this->effect = input.clone();
	this->effect = cv::Mat(input.size(),CV_8UC4);
	cv::Mat gray(input.rows,input.cols,CV_8UC1);
	cv::Mat edges(input.rows,input.cols,CV_8UC1);
	cv::Mat edgesBgr(input.rows,input.cols,CV_8UC3);
	cv::Mat bgr(input.rows,input.cols,CV_8UC3);

	cv::cvtColor(input, bgr, CV_BGRA2BGR);
	cv::pyrMeanShiftFiltering(bgr.clone(), bgr, sp, sr);

	cv::cvtColor(input,gray,CV_BGR2GRAY);

	cv::Canny(gray, edges, 150, 150);
	cv::cvtColor(edges, edgesBgr, CV_GRAY2BGR);
	bgr = bgr - edgesBgr;
	cv::cvtColor(bgr, this->effect, CV_BGR2BGRA);
	volatile int depth = effect.depth();
	//std::cout <<"depth: "<<depth<<std::endl;
	//cv::imshow("draw", effect);
	//cv::waitKey(0);
}