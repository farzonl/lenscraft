#include "CaptureCam.hpp"
#include <iostream>
#include <pthread.h>

//CRITICAL_SECTION _critSection;
pthread_mutex_t mutex_lock;

CaptureCam::CaptureCam():capture( CV_CAP_ANY ),queueMat()
{
	//capture = cvCaptureFromCAM( CV_CAP_ANY ); //old way
	if( !capture.isOpened() )
		std::cout << "ERROR: capture is NULL \n"<<std::endl;

	// Grab the device

	//capture.grab();
	//InitializeCriticalSection (& _critSection);
	//pthread_mutex_init(&mutex_lock, NULL);

}


CaptureCam::~CaptureCam(void)
{
	capture.release();
	t_id->join();
}

cv::Mat CaptureCam::getMat()
{
	#ifdef __WIN32__
	cv::Mat retMat = queueMat.front();
	queueMat.pop();
	return retMat;
	#else
	capture >> camFrame;
	cv::flip(camFrame,camFrame,-1 );
	return camFrame.clone();
	#endif
}

bool CaptureCam::ready()
{
	return !queueMat.empty();
}

//void *cameraThread(void* param)
void cameraThread(void* param)
{	

	CaptureCam *cc = (CaptureCam*)param;
	// Retrieve desired sensor data (in this case the standard camera image)
	while(1)
	{
		cc->getFrame();
	}
	//glfwDestroyThread(glfwGetThreadID());

}


void  CaptureCam::getFrame()
{
	//glfwLockMutex(m_mutex);
	//EnterCriticalSection (& _critSection);
	pthread_mutex_lock (&mutex_lock);
	//capture.retrieve(camFrame);
	capture >> camFrame;
	cv::flip(camFrame,camFrame,-1 );
	queueMat.push(camFrame);
	//cv::imshow("show",camFrame);
	pthread_mutex_unlock (&mutex_lock);
	//LeaveCriticalSection (& _critSection);
	
	//glfwUnlockMutex(m_mutex);
}
