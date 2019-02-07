#include <iostream>
#include <sstream> // for string stream
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "BoothUI.hpp"


using std::cout;
using std::cerr;
using std::endl;
int WINDOW_WIDTH  = 800;
int WINDOW_HEIGHT = 600;
int SWP_L_CNT,SWP_R_CNT;
std::string title = "Lens Craft";
BoothUI bp;
GLFWwindow* window = nullptr;

void window_resize(GLFWwindow* window, int width, int height)
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
	while (window != nullptr)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{

			break;
		}

		const double currentTime = glfwGetTime();
		const double diff = currentTime - lastTime;
		lastTime = currentTime;

		double x,y;
		glfwGetCursorPos(window, &x,&y);
		//add render function here
		bp.render();
		glfwSwapBuffers(window);

		// Simple FPS counter
		fpsAccum += diff;
		if (fpsAccum >= 1.0)
		{
			fpsAccum -= 1.0;
			std::stringstream ss;
			ss << "GLFW Lens Craft FPS: " << fps;
			glfwSetWindowTitle(window, ss.str().c_str());
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
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, title.c_str(), NULL, NULL);

	if (window == nullptr)
	{
		cerr << "Failed to create GLFW window!" << endl;
		return 1;
	}

	glfwSetWindowSizeCallback(window, window_resize);

	// Create at minimum a 2.0+ OpenGL profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	
	glewInit();
	glfwSwapInterval(0); // Change to 0 if you want to turn off VSync 1 for on

	int major = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
	int minor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
	cout << "OpenGL - " << major << "." << minor << endl;

	if (major < 2)
	{
		glfwTerminate();
	}

	glfwSetWindowTitle(window, title.c_str());
	glfwSetWindowSizeCallback(window, window_resize);
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
