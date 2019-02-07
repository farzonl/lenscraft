//#pragma once
#ifndef __EFFECTS_HPP__
#define __EFFECTS_HPP__

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <opencv2/imgproc/imgproc.hpp> 

class Effects
{
   protected:
	GLuint texture;
	cv::Mat effect;
	public:
		Effects(void):visited(false) {};
		GLuint genTexture();
		virtual ~Effects(void) { glDeleteTextures(1, &this->texture);}
		virtual void performEffect(cv::Mat &input) = 0;
	private:
		GLuint matToTexture(cv::Mat &mat, GLenum minFilter, GLenum magFilter, GLenum wrapFilter);
		bool visited;
};

class Original : public Effects
{

	public:
		Original(void): Effects(){}
		void performEffect(cv::Mat &input)
		{
			this->effect = input;
		}
};
#endif //__EFFECTS_HPP__
