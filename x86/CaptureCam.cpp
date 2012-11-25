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

	capture.grab();
	//InitializeCriticalSection (& _critSection);
	pthread_mutex_init(&mutex_lock, NULL);
}


CaptureCam::~CaptureCam(void)
{
	
	capture.release();
	glfwDestroyThread(this->t_id);
	//glfwDestroyMutex(this->m_mutex);
	//DeleteCriticalSection (& _critSection);
	pthread_mutex_destroy(&mutex_lock);
}

cv::Mat CaptureCam::getMat()     
{
	//while(queueMat.empty()){}
	cv::Mat retMat = queueMat.front();
	queueMat.pop();
	return retMat;
}

bool CaptureCam::ready()
{
	return !queueMat.empty();
}

void cameraThread(void* param)
{	

	CaptureCam *cc = (CaptureCam*)param;
	// Retrieve desired sensor data (in this case the standard camera image)
	cc->setThreadId(glfwGetThreadID());
	while(1)
	{
		cc->getFrame();
		//cvWaitKey(0);
	}
	//glfwDestroyThread(glfwGetThreadID());

}


void  CaptureCam::getFrame()
{
	//glfwLockMutex(m_mutex);
	//EnterCriticalSection (& _critSection);
	pthread_mutex_lock (&mutex_lock);
	capture.retrieve(camFrame);
	//cv::flip(camFrame,camFrame,-1 );
	queueMat.push(camFrame);
	pthread_mutex_unlock (&mutex_lock);
	//LeaveCriticalSection (& _critSection);
	
	//glfwUnlockMutex(m_mutex);
}
