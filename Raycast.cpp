#include "Raycast.hpp"


void Raycast::Draw() {
}
void Raycast::Move(glm::vec3 position) {
	pos += position;
}
glm::vec3 Raycast::getPos() {
	return pos;
}
glm::vec3 Raycast::getSize() {
	return size;
}
void Raycast::setPos(glm::vec3 position) {
	pos = position;
}
glm::mat4 Raycast::getTransformMatrix() {
	return transform;
}
void Raycast::setTransformMatrix(glm::mat4 matrix) {
	transform = matrix;
}
bool Raycast::Intersect(glm::vec3 boxPos, glm::vec3 boxSize) {
	bool collisionX = Raycast::getPos().x + Raycast::getSize().x >= -boxSize.x / 2 + boxPos.x && Raycast::getPos().x <= boxSize.x / 2 + boxPos.x;
	bool collisionY = Raycast::getPos().y + Raycast::getSize().y >= -boxSize.y / 2 + boxPos.y && Raycast::getPos().y <= boxSize.y / 2 + boxPos.y;
	bool collisionZ = Raycast::getPos().z + Raycast::getSize().z >= -boxSize.z / 2 + boxPos.z && Raycast::getPos().z <= boxSize.z / 2 + boxPos.z;
	return (collisionX && collisionY && collisionZ);
}