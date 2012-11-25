//#pragma once
#ifndef __BOOTH__UI_HPP__
#define __BOOTH__UI_HPP__
#include "Shader.hpp"
#include "Rectangle.hpp"
#include "CaptureCam.hpp"
#include <vector>
#include <memory>
#include "Effects.hpp"

const float white[] = {1.0f,1.0f,1.0f};
const float red[] = {1.0f,0.0f,0.0f};
const float blue[] = {0.0f,0.0f,1.0f};
const float teal[] = {0.0f,1.0f,1.0f};
const float green[] = {0.0f,1.0f,0.0f};

const int WIDTH  = 800;
const int HEIGHT = 600;
const int ROW_REC = 3;
const int COL_REC = 3;

class BoothUI
{
	
	public:
		CaptureCam cc;
		BoothUI();
		~BoothUI(void);
		void render(void);
		void initialize(void);
		void windowResized(int width, int height);
		int getUiPositionHandle();
		int getUiColorHandle();
		std::unique_ptr<Effects> EffectGenerator(int i);
	private:
	Shader uiShader;

	int useColorHandle;
	int uiPositionHandle;
	int uiTextureHandle;
	int uiTextureSampler;
	int uiResolution;
	int uicolorHandle;

	float resolution[2];

	//int aTexture;

	int width,height;

	glm::mat4 mVMatrix;
	std::vector< std::unique_ptr<QUAD_DEF::Rectangle> > layout;
	cv::Mat cur_mat;
};
#endif //__BOOTH__UI_HPP__
