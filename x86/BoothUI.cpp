#include "BoothUI.hpp"

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sepia.hpp"
#include "Grayscale.hpp"
#include "Drawing.hpp"
#include "Contrast.hpp"
#include "Xray.hpp"
#include "radialBlur.hpp"
#include "mirror.hpp"
#include "SobelTex.hpp"

#include <omp.h>

//#include <tbb/parallel_for.h>
//#include <ppl.h>//parallel_for

#include "texture.hpp" //TODO replace this

using namespace glm;
using namespace QUAD_DEF;

//CaptureCam *cc = nullptr;

BoothUI::BoothUI() : uiShader(),cc(),width(0),height(0),uicolorHandle(0),uiResolution(0),
	uiTextureSampler(0),uiTextureHandle(0),uiPositionHandle(0),useColorHandle(0)
{
	//TODO add codpe to create squares
	//cc = new CaptureCam();
	int frame = 0;
	for(int i = 0; i < HEIGHT;i+= HEIGHT/COL_REC)
	{
		for(int j = 0; j < WIDTH; j+= WIDTH/ROW_REC)
		{
			layout.push_back(std::unique_ptr<QUAD_DEF::Rectangle>(new QUAD_DEF::Rectangle(j,i,j+ (WIDTH/ROW_REC),i + (HEIGHT/COL_REC))));
			if(frame == 1) layout.back()->setEffect(EffectGenerator(5));
			else if(frame == 5) layout.back()->setEffect(EffectGenerator(2));
			else if(frame == 8) layout.back()->setEffect(EffectGenerator(1));
			else if(frame == 2) layout.back()->setEffect(EffectGenerator(3));
			else if(frame == 6) layout.back()->setEffect(EffectGenerator(6));
			else if(frame == 7) layout.back()->setEffect(EffectGenerator(7));
			else if(frame == 4) layout.back()->setEffect(EffectGenerator(8));
			else layout.back()->setEffect(EffectGenerator(0));
			frame++;
			j+=5;
		}
		i+=5;
	}
}

std::unique_ptr<Effects> BoothUI::EffectGenerator(int i)
{
	switch(i)
	{
	    case 0:
			return std::unique_ptr<Effects>(new Original());
		case 1:
			return std::unique_ptr<Effects>(new Sepia());
		case 2:
			return std::unique_ptr<Effects>(new Grayscale());
		case 3:
			return std::unique_ptr<Effects>(new Contrast());
		case 4:
			return std::unique_ptr<Effects>(new Drawing());
		case 5:
			return std::unique_ptr<Effects>(new Xray());
		case 6:
			return std::unique_ptr<Effects>(new RadialBlur()); 
		case 7:
			return std::unique_ptr<Effects>(new Mirror()); 
		case 8:
			return std::unique_ptr<Effects>(new SobelTex()); 
	}
}

BoothUI::~BoothUI(void)
{
}

void BoothUI::windowResized(int width, int height)
{
	this->width  = width;
	this->height = height;
	glViewport(0, 0, width, height);
	float ratio = (float) width / height;
	//mProjMatrix = glm::perspective(45.0f, ratio, 0.1f, 100.0f);
	//mVMatrix = glm::lookAt(glm::vec3(1.5f, 4.5f, 4.5f), glm::vec3(0, 2, 0), glm::vec3(0, 1, 0));
	resolution[0] = (float)width;
	resolution[1] = (float)height;
	int frame = 0;
	for(int i = 0; i < height;i+= height/COL_REC)
	{
		for(int j = 0; j < width; j+= width/ROW_REC)
		{
			//(j,i,j+ (WIDTH/ROW_REC),i + (HEIGHT/COL_REC)
			layout[frame]->StorePoints(glm::vec3(j, i, 0), glm::vec3(j+width/ROW_REC, i, 0),
				glm::vec3(j+width/ROW_REC,i+height/COL_REC, 0), glm::vec3(j,i+height/COL_REC, 0));
			frame++;
			j+=5;
		}
		i+=5;
	}
}

void BoothUI::initialize(void)
{
	glClearColor(0, 0, 0, 0);
	glfwCreateThread(cameraThread, &cc);
	glEnable(GL_TEXTURE_2D);
	//aTexture = loadBMP_custom("pics/face.bmp");
	uiShader.loadShaders("shaders/uiShader.vert", "shaders/uiShader.frag");
	uiPositionHandle = uiShader.getAttribLocation("a_position");
	uiTextureHandle  = uiShader.getAttribLocation("a_texture");
	uiTextureSampler = uiShader.getUniformLocation("u_texture");
	uiResolution     = uiShader.getUniformLocation("u_resolution");
	uicolorHandle    = uiShader.getUniformLocation("color");
	useColorHandle   = uiShader.getUniformLocation("use_color");

	/*basicShader.loadShaders("uiShader.vert", "uiShader.frag");
	positionHandle = basicShader.getAttribLocation("a_position");
	colorHandle    = basicShader.getUniformLocation("color");*/
}


void BoothUI::render(void)
{

	if(cc.ready())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Texture code
		glUseProgram(uiShader.getProgram());

		//glActiveTexture(GL_TEXTURE0);
		glUniform2fv(uiResolution, 1, resolution);

		cur_mat = cc.getMat().clone();

		/*if(TryEnterCriticalSection(&_critSection))
		{
		cur_mat = cc.getMat().clone();
		LeaveCriticalSection (& _critSection);
		}*/
		//#pragma unroll ROW_REC*COL_REC
        #pragma omp parallel for num_threads(2) 
		for(int i = 0; i < layout.size();i++)
		{
			layout[i]->eff->performEffect(cur_mat);
		}

		for(unsigned int i = 0; i < layout.size();i++)
		{
			layout[i]->render(uiPositionHandle, -1, uiTextureHandle);
		}
		// Cleanup
		glUseProgram(0);
		cur_mat.release();
		//cc.updateImage();
	}
}

