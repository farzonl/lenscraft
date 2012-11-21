#include "Shape.hpp"

#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Shape::Shape(void) : 
		modelMatrix(1.0f), // Identity
		vertexAttributes(NULL),
		boundingBox(NULL),
		vertsToDraw(0),
		stride(0)
{
}

Shape::~Shape(void)
{
	if (vertexAttributes != NULL)
	{
		delete [] vertexAttributes;
	}

	if (boundingBox != NULL)
	{
		delete boundingBox;
	}
}

glm::vec3 Shape::getPosition(void)
{
	const float* const matrix = glm::value_ptr(modelMatrix);
	return glm::vec3(matrix[12], matrix[13], matrix[14]);
}

void Shape::translateTo(const glm::vec3& position)
{
	float* matrix = glm::value_ptr(modelMatrix);
	matrix[12] = position.x;
	matrix[13] = position.y;
	matrix[14] = position.z;
}

void Shape::translate(const glm::vec3& translation)
{
	modelMatrix = glm::translate(modelMatrix, translation);
}

void Shape::rotate(float angle, const glm::vec3& axis)
{
	modelMatrix = glm::rotate(modelMatrix, angle, axis);
}

// TODO - fix with something better
void Shape::render(int positionHandle, int modelHandle, int normalHandle)
{
	glUniformMatrix4fv(modelHandle, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE, stride, vertexAttributes);
	glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, stride, vertexAttributes+3);
	glDrawArrays(GL_TRIANGLES, 0, vertsToDraw);
}

void Shape::addTriangle(float* const vertArray, int& index,
	const glm::vec3& vertex1,
	const glm::vec3& vertex2,
	const glm::vec3& vertex3,
	const glm::vec3& normal)
{
	// First Triangle
	// Top Left
	vertArray[index++] = vertex1.x;
	vertArray[index++] = vertex1.y;
	vertArray[index++] = vertex1.z;

	vertArray[index++] = normal.x;
	vertArray[index++] = normal.y;
	vertArray[index++] = normal.z;

	vertArray[index++] = 0; // TODO Fix
	vertArray[index++] = 0;

	// Bottom Left
	vertArray[index++] = vertex2.x;
	vertArray[index++] = vertex2.y;
	vertArray[index++] = vertex2.z;

	vertArray[index++] = normal.x;
	vertArray[index++] = normal.y;
	vertArray[index++] = normal.z;

	vertArray[index++] = 0;
	vertArray[index++] = 0;

	// Bottom Right
	vertArray[index++] = vertex3.x;
	vertArray[index++] = vertex3.y;
	vertArray[index++] = vertex3.z;

	vertArray[index++] = normal.x;
	vertArray[index++] = normal.y;
	vertArray[index++] = normal.z;

	vertArray[index++] = 0;
	vertArray[index++] = 0;
}

void Shape::addQuad(float* const vertArray, int& index, 
	const glm::vec3& vertex1,
	const glm::vec3& vertex2,
	const glm::vec3& vertex3,
	const glm::vec3& vertex4,
	const glm::vec3& normal)
{
	addTriangle(vertArray, index, vertex1, vertex2, vertex3, normal);
	addTriangle(vertArray, index, vertex1, vertex3, vertex4, normal);

	// TODO edit texture coords
}