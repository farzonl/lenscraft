
#include <GL/glew.h>   //OGL ext lib
#include <GLFW/glfw3.h>    //OGL windowing lib
#include <glm/glm.hpp> //OGL matrix library
#include <glm/gtc/type_ptr.hpp>
#include "Rectangle.hpp"

using namespace QUAD_DEF;


Rectangle::Rectangle(float x0, float y0, float x1, float y1): Shape()
{
	spc_dat_init(x0,y0,x1,y1);
}


double Rectangle::getFreq()
{
	return freq;
}

std::string Rectangle::getName()
{
	return name;
}

void Rectangle::spc_dat_init(float x0, float y0, float x1, float y1)
{
	Rectangle::initialize(glm::vec3(x0, y0, 0), glm::vec3(x1, y0, 0),glm::vec3(x1, y1, 0), glm::vec3(x0, y1, 0));
}

Rectangle::Rectangle(const glm::vec3& p1,float h, float w): Shape()
{
	Rectangle::initialize(p1, glm::vec3(p1.x+w, p1.y, 0),glm::vec3(p1.x+w,p1.y-h, 0), glm::vec3(p1.x, p1.y-h, 0));
}
Rectangle::Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4): Shape()
{
	initialize(p1,p2,p3,p4);
}

void Rectangle::initialize(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
{	
	this->stride = 5*sizeof(float);
	this->vertsToDraw = 4;
	this->vertexAttributes = new float[4*5];
	StorePoints(p1,p2,p3,p4);

}

void Rectangle::setIsRender(bool ir)
{
	this->isRender = ir;
}

bool Rectangle::getIsRender()
{
	return this->isRender;
}

void Rectangle::StorePoints(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
{
	int index = 0;
	// Top Left
	vertexAttributes[index++] = p1.x;
	vertexAttributes[index++] = p1.y;
	vertexAttributes[index++] = p1.z;

	
	vertexAttributes[index++] = 0; // TODO Fix
	vertexAttributes[index++] = 1;
	
	// Top Right
	vertexAttributes[index++] = p2.x;
	vertexAttributes[index++] = p2.y;
	vertexAttributes[index++] = p2.z;
	
	vertexAttributes[index++] = 1; // TODO Fix
	vertexAttributes[index++] = 1;

	//Bottom Right
	vertexAttributes[index++] = p3.x;
	vertexAttributes[index++] = p3.y;
	vertexAttributes[index++] = p3.z;

	vertexAttributes[index++] = 1; // TODO Fix
	vertexAttributes[index++] = 0;

	//Bottom Left
	vertexAttributes[index++] = p4.x;
	vertexAttributes[index++] = p4.y;
	vertexAttributes[index++] = p4.z;

	vertexAttributes[index++] = 0; // TODO Fix
	vertexAttributes[index++] = 0;
}

Rectangle::~Rectangle(void)
{
	delete vertexAttributes;
}

//template <GLfloat>
//void Rectangle::render(int positionHandle, int modelHandle, int textureHandle,int useColorHandle)
void Rectangle::render(int positionHandle, int modelHandle, int textureHandle)
{
	// Bind texture
	glBindTexture(GL_TEXTURE_2D, eff->genTexture());
	//glUniform1i(useColorHandle,0);
	glEnableVertexAttribArray(positionHandle);
	glEnableVertexAttribArray(textureHandle);
	glDisableVertexAttribArray(modelHandle);
	//glUniformMatrix4fv(modelHandle, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE, stride, vertexAttributes);
	glVertexAttribPointer(textureHandle,  2, GL_FLOAT, GL_FALSE, stride, vertexAttributes+3);
	glDrawArrays(GL_QUADS, 0, vertsToDraw);
}

//void Rectangle::render(int positionHandle, int modelHandle,int colorHandle, float *color,int useColorHandle)
void Rectangle::render(int positionHandle, int modelHandle,int colorHandle, float *color)
{
	//glUniform1i(useColorHandle,1);
	glEnableVertexAttribArray(positionHandle);
	glUniform4fv(colorHandle, 1, color);
	//glUniformMatrix4fv(modelHandle, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE, stride, vertexAttributes);
	glDrawArrays(GL_QUADS, 0, vertsToDraw);
}

void Rectangle::setEffect(std::unique_ptr<Effects> eff)
{
	this->eff =  std::move(eff);
}

