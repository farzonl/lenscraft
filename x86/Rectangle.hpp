#pragma once

#include "Shape.hpp"
//#include "shapes2d.h"
#include <string>
#include "Effects.hpp"

namespace QUAD_DEF
{
//template <typename T>
class Rectangle : public Shape
{
public:
	Rectangle();
	//Rectangle(const Point* const p1, const Point* const p2);
	//Rectangle::Rectangle(T x0, T y0, T x1, T y1);
	Rectangle(float x0, float y0, float x1, float y1);
	//Rectangle(const Rect* const r);
	Rectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
	//const Rect* getRectD();
	std::string getName();
	double getFreq();
	void setIsRender(bool ir);
	bool getIsRender();
	Rectangle(const glm::vec3& p1,float h, float w);
	void StorePoints(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
	void render(int positionHandle, int modelHandle, int textureHandle);
	void render(int positionHandle, int modelHandle,int colorHandle,float *color);
	virtual ~Rectangle(void);
	void setEffect(std::unique_ptr<Effects> eff);
	std::unique_ptr<Effects> eff;
	

private:
	void spc_dat_init(float x0, float y0, float x1, float y1);
	void initialize(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4);
	float *vertexAttributes;
	//const Rect *Rd;
	double freq;
	bool isRender;
	std::string name;
	//T *vertexAttributes;
};
}
