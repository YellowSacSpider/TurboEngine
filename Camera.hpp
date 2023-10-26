#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
class Camera {
private:
	GLFWwindow* _window = nullptr;
	Shader* _ourShader = nullptr;
	bool fpsCameraMode = false;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	bool firstMouse = true;
	double yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	double pitch = 0.0f;
	double lastX = 800.0f / 2.0;
	double lastY = 600.0 / 2.0;
	double fov = 45.0f;

public:
	Camera()
	{

	}

	void processInput(double deltaTimew);
	void BindShader(Shader* shader);
	void CameraRotate(double xpos, double ypos);
	void CameraZoom(double yoffset);
	void BindWindow(GLFWwindow* window);
	void FPSMode(bool mode);
	void Update(double deltaTime);
	glm::vec3 getPos();
	void translate(glm::vec3 transform);
};