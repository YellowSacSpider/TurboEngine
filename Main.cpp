#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shader.hpp"
#include "Texture.hpp"
#include "Shape.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float i = 0.f;
float px, py, pz = 1.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "TurboEngine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	Shader ourShader("Shader.vertexshader", "Shader.fragmentshader");

	//Generate textures----------------------------------------------------------------------------------
	Texture tex1("Main Ship - Base - Full health.png", GL_CLAMP_TO_EDGE, GL_RGBA);
	Texture tex2("galaxy.jpg", GL_CLAMP_TO_EDGE, GL_RGB);
	//ourShader.use();

	//---------------------------------------------------------------------------------------------------

	float vertices[] = {
		// positions             // texture coords
		 0.5f,  0.5f, 0.0f,      1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,      1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,      0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,      0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	unsigned int VBO, VAO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		// rendering commands here
		//...
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //Default: glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		
		ourShader.use();
		glBindVertexArray(VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex2.texture);

		glm::mat4 background = glm::mat4(1.0f);
		background = glm::translate(background, glm::vec3(0.0f, 0.0f, 0.0f));
		background = glm::scale(background, glm::vec3(2.0f, 2.0f, 2.0f));
		unsigned int transformLoc2 = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(background));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindTexture(GL_TEXTURE_2D, tex1.texture);

		glm::mat4 Player = glm::mat4(1.0f);
		Player = glm::translate(Player, glm::vec3(px, py, 0.0f));
		Player = glm::scale(Player, glm::vec3(0.5f, 0.5f, 0.5f));
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(Player));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		Rectangle rectangle;

		rectangle.draw();

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_RELEASE)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_F1) != GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_F2) != GLFW_RELEASE)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_RELEASE)
	{
		if(px <= 0.8f)
			px += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_RELEASE)
	{
		if (px >= -0.8f)
			px -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) != GLFW_RELEASE)
	{
		if (py <= 0.8f)
			py += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_RELEASE)
	{
		if (py >= -0.8f)
			py -= 0.001f;
	}
}