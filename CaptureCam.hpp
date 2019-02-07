//#pragma once
#ifndef __CAPTURE__CAM_HPP__
#define __CAPTURE__CAM_HPP__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <queue>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <thread>

void cameraThread(void* param);

class CaptureCam
{
	cv::VideoCapture capture;
	// Create our cv::Mat object
	cv::Mat camFrame;
	std::queue<cv::Mat> queueMat;

	std::thread *t_id;
	public:
		bool ready();
		cv::Mat getMat();
		void updateImage();
		IplImage* getImage();
		CaptureCam();
		~CaptureCam();
		cv::VideoCapture getCap() const {return capture;}
		void  getFrame();
		void initCamThread() { t_id = new std::thread(cameraThread, this);}
};
#endif //__CAPTURE_CAM_HPP__
