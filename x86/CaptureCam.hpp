#pragma once

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <GL/glew.h>
#include <GL/glfw.h>
//#include <Windows.h>
//#include <thread>
#include <queue>

//extern CRITICAL_SECTION _critSection;
//extern CONDITION_VARIABLE empty,full;

void cameraThread(void* param);

class CaptureCam
{
	cv::VideoCapture capture;
	// Create our cv::Mat object
	cv::Mat camFrame;
	std::queue<cv::Mat> queueMat;

	GLFWthread t_id;
	public:
		bool ready();
		cv::Mat getMat();
		void updateImage();
		IplImage* getImage();
		CaptureCam();
		~CaptureCam();
		cv::VideoCapture getCap() const {return capture;}
		void  getFrame();
		void setThreadId(GLFWthread id) { t_id = id;}
};
