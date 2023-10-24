#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Texture.hpp"


class Sprite {
private:
	unsigned int vao, vbo, ebo = 0;

	glm::vec2 _pos = glm::vec2(0.0f, 0.0f);
	glm::vec2 _size = glm::vec2(0.0f, 0.0f);
	glm::vec2 _rotation = glm::vec2(0.0f, 0.0f);
	float _angle = 0;

	//Shader ourShader = Shader("Deprecated/Primitive.vertexshader", "Deprecated/Primitive.fragmentshader");
	Shader ourShader = Shader("Sprite.vertexshader", "Sprite.fragmentshader");
	Texture _texture;
	
	float vertices[20] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

public:
	Sprite(Texture texture, glm::vec2 pos, glm::vec2 size) : _texture(texture), _pos(pos), _size(size) {
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	~Sprite() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
	}

	void draw();
	void translate(glm::vec2 transform);
	void rotate(float angle, glm::vec2 transform);
	void scale(glm::vec2 transform);
};