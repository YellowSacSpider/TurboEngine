#include "Sprite.hpp"

void Sprite::draw() {
	ourShader.use();
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture.texture);

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(_pos, 0.0f));
	transform = glm::scale(transform, glm::vec3(_size.x/(800/4), _size.y/(600/4), 0.0f));
	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Sprite::translate(glm::vec2 transform) {
	_pos = transform;
}
void Sprite::rotate(float angle, glm::vec2 transform) {
	_angle = angle;
	_rotation = transform;
}

void Sprite::scale(glm::vec2 transform) {
	_size = transform;
}