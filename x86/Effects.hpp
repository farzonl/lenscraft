#pragma once
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <GL/glew.h>
#include <GL/glfw.h>

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
