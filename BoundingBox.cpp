#include "BoundingBox.hpp"

using glm::vec3;

BoundingBox::BoundingBox(const glm::vec3& dimensions, const glm::vec3& position, glm::mat4* matModel) :
	modelMatrix(matModel)
{
	const float halfDimX = dimensions.x / 2.0f;
	const float halfDimY = dimensions.y / 2.0f;
	const float halfDimZ = dimensions.z / 2.0f;

	vec3 halfDims(halfDimX, -halfDimY, halfDimZ);

	topLeft = position - halfDims;
	bottomRight = position + halfDims;
}

BoundingBox::~BoundingBox(void)
{

}

void BoundingBox::updatePoints(glm::vec3& tlOut, glm::vec3& brOut) const
{
	// Very hacky, fixable later
	glm::vec4 tl4 = glm::vec4(topLeft, 1.0f);
	glm::vec4 br4 = glm::vec4(bottomRight, 1.0f);

	tl4 = (*modelMatrix) * tl4;
	br4 = (*modelMatrix) * br4;

	tlOut.x = tl4.x; tlOut.y = tl4.y; tlOut.z = tl4.z;
	brOut.x = br4.x; brOut.y = br4.y; brOut.z = br4.z;
}

/*
!
r2->left > r1->right ||
r2->right < r1->left || 
r2->top > r1->bottom || 
r2->bottom < r1->top ||

*/

bool BoundingBox::intersects(const BoundingBox& o) const
{
	// Hack
	glm::vec3 myTL;
	glm::vec3 myBR;
	this->updatePoints(myTL, myBR);

	glm::vec3 oTL;
	glm::vec3 oBR;
	o.updatePoints(oTL, oBR);

	return !
		((oTL.x > myBR.x) // x
		|| (oBR.x < myTL.x)

		|| (oTL.y < myBR.y) // y
		|| (oBR.y > myTL.y)

		|| (oTL.z > myBR.z) // z
		|| (oBR.z < myTL.z));
}

bool BoundingBox::contains(const BoundingBox& o) const
{
	// Hack
	glm::vec3 myTL;
	glm::vec3 myBR;
	this->updatePoints(myTL, myBR);

	glm::vec3 oTL;
	glm::vec3 oBR;
	o.updatePoints(oTL, oBR);

	return myTL.x < oTL.x
		&& myTL.y > oTL.y
		&& myTL.z < oTL.z
		&& myBR.x > oBR.x
		&& myBR.y < oBR.y
		&& myBR.z > oBR.z;
}
