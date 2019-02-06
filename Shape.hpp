//#pragma once
#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__

#include "BoundingBox.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>

class Shape
{
public:
	Shape(void);

	virtual ~Shape(void);

	float* getAttributes() { return vertexAttributes; }

	int getVertsToDraw() { return vertsToDraw; }

	int getStride() { return stride; }

	void render(int positionHandle, int modelHandle, int normalHandle);

	void translate(const glm::vec3& translation);

	void translateTo(const glm::vec3& position);

	void rotate(float angle, const glm::vec3& axis);

	bool intersects(const Shape& other) 
	{
		if (boundingBox != 0 && other.boundingBox != 0)
		{
			return boundingBox->intersects(*other.boundingBox);
		}

		return false;
	}

	bool contains(const Shape& other)
	{
		if (boundingBox != 0 && other.boundingBox != 0)
		{
			return boundingBox->contains(*other.boundingBox);
		}

		return false;
	}

	glm::vec3 getPosition(void);

	int getNormalsOffset(void) { return 3; }
	int getTextureCoordsOffset(void) { return 6; }

public:
	glm::mat4 modelMatrix;

protected:
	void addQuad(float* const vertexArray, int& index, 
		const glm::vec3& vertex1,
		const glm::vec3& vertex2,
		const glm::vec3& vertex3,
		const glm::vec3& vertex4,
		const glm::vec3& normal);

	void addTriangle(float* const vertexArray, int& index,
		const glm::vec3& vertex1,
		const glm::vec3& vertex2,
		const glm::vec3& vertex3,
		const glm::vec3& normal);

protected:
	BoundingBox* boundingBox;
	float* vertexAttributes;
	int vertsToDraw;
	int stride;
};

#endif //__SHAPE_HPP__
