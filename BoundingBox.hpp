//#pragma once
#ifndef __BOUNDING__BOX_HPP__
#define __BOUNDING__BOX_HPP__
#include <glm/glm.hpp>

class BoundingBox // Axis aligned (but we don't bother updating yet...)
{
public:
	BoundingBox(const glm::vec3& dimensions, const glm::vec3& position, glm::mat4* modelMatrix);
	~BoundingBox(void);

	bool intersects(const BoundingBox& other) const;

	bool contains(const BoundingBox& other) const;

private:
	void updatePoints(glm::vec3& tlOut, glm::vec3& brOut) const;

private:
	glm::vec3 topLeft;
	glm::vec3 bottomRight;
	glm::mat4* modelMatrix;
};
#endif //__BOUNDING__BOX_HPP__
