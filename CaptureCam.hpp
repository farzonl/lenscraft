//#pragma once
#ifndef __CAPTURE__CAM_HPP__
#define __CAPTURE__CAM_HPP__
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <GL/glew.h>
#include <GL/glfw.h>
//#include <Windows.h>
//#include <thread>
#include <queue>

//extern CRITICAL_SECTION _critSection;
//extern pthread_mutex_t mutex_lock;

//void *cameraThread(void* param);
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
#endif //__CAPTURE_CAM_HPP__
