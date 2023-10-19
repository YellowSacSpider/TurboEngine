#include "Shape.hpp"

void Triangle::draw() 
{
	ourShader.use();
	glBindVertexArray(VAO);

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Rectangle::draw()
{
	ourShader.use();
	glBindVertexArray(VAO);

	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
	transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


