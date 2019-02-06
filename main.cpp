#include <iostream>
#include <sstream> // for string stream
#include <GL/glew.h>
#include <GL/glfw.h>
#include "BoothUI.hpp"


using std::cout;
using std::cerr;
using std::endl;
int WINDOW_WIDTH  = 800;
int WINDOW_HEIGHT = 600;
int SWP_L_CNT,SWP_R_CNT;

BoothUI bp;


void GLFWCALL window_resize(int width, int height)
{
	WINDOW_WIDTH  = width;
	WINDOW_HEIGHT = height;

	bp.windowResized(width, height);
}

double lastTime;
int fps = 0;
double accum = 0;
double fpsAccum = 0;
const double GAME_DT = 1.0 / 60.0; // 60 fps

void update_loop(void)
{
	lastTime = glfwGetTime();
	while (glfwGetWindowParam(GLFW_OPENED) == GL_TRUE)
	{
		if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
		{

			break;
		}

		const double currentTime = glfwGetTime();
		const double diff = currentTime - lastTime;
		lastTime = currentTime;

		int x,y;
		glfwGetMousePos(&x,&y);
		//add render function here
		bp.render();
		glfwSwapBuffers();

		// Simple FPS counter
		fpsAccum += diff;
		if (fpsAccum >= 1.0)
		{
			fpsAccum -= 1.0;
			std::stringstream ss;
			ss << "GLFW Lens Craft FPS: " << fps;
			glfwSetWindowTitle(ss.str().c_str());
			fps = 0;
		}
		++fps;
	}
}

int main(int argc, char* argv[])
{
	if (glfwInit() != GL_TRUE)
	{
		cerr << "Failed to initialize GLFW!" << endl;
		return 1;
	}

	glfwSetWindowSizeCallback(window_resize);

	// Create at minimum a 2.0+ OpenGL profile
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 0);

	if (glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 8, 8, 8, 8, 8, 0, GLFW_WINDOW) != GL_TRUE)
	{
		cerr << "Failed to create GLFW window!" << endl;
		return 1;
	}
	glewInit();
	glfwSwapInterval(0); // Change to 0 if you want to turn off VSync 1 for on

	int major = glfwGetWindowParam(GLFW_OPENGL_VERSION_MAJOR);
	int minor = glfwGetWindowParam(GLFW_OPENGL_VERSION_MINOR);
	cout << "OpenGL - " << major << "." << minor << endl;

	if (major < 2)
	{
		glfwTerminate();
	}

	glfwSetWindowTitle("GLFW Lens Craft");
	glfwSetWindowSizeCallback(window_resize);
	try {
		bp.initialize();
		bp.windowResized(WINDOW_WIDTH, WINDOW_HEIGHT);


		update_loop();
	} catch (std::exception e) {
		cerr << "Exception: " << e.what() << endl;
		std::cin.get();
	} catch (...) {
		cerr << "Exception happend!" << endl;
		std::cin.get();
	}

	return 0;
}
