#include "Grayscale.hpp"

void Grayscale::performEffect(cv::Mat &input) 
{
    if(this->effect.empty()) effect = input.clone();
    //cv::cvtColor(input,this->effect,CV_RGB2GRAY);
    cv::cvtColor(input,this->effect,CV_BGR2GRAY);
}