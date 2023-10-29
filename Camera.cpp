#include "Camera.hpp"


void Camera::processInput(double deltaTime) {
	const float cameraSpeed = 16.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += (fpsCameraMode) ? (cameraFront - glm::vec3(0.0f, cameraFront.y, 0.0f)) * cameraSpeed : cameraFront * cameraSpeed;
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= (fpsCameraMode) ? (cameraFront - glm::vec3(0.0f, cameraFront.y, 0.0f)) * cameraSpeed : cameraFront * cameraSpeed;
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cameraPos += glm::vec3(0.0f, 16.0f, 0.0f) * cameraSpeed;
}

void Camera::CameraRotate(double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
	//std::cout << cameraFront.x << "|" << cameraFront.y << "|" << cameraFront.z << '\n';
}

void Camera::CameraZoom(double yoffset) {
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}

void Camera::FPSMode(bool mode) {
	fpsCameraMode = mode;
}

void Camera::Update(double deltaTime) {
	processInput(deltaTime);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	int viewLoc = glGetUniformLocation(_ourShader->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	projection = glm::perspective(glm::radians((float)fov), (float)800 / (float)600, 0.1f, 1000.0f);
	int projLoc = glGetUniformLocation(_ourShader->ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void Camera::BindShader(Shader* shader) {
	_ourShader = shader;
}

void Camera::BindWindow(GLFWwindow* window) {
	_window = window;
}

glm::vec3 Camera::getPos() {
	return cameraPos;
}

void Camera::translate(glm::vec3 pos) {
	cameraPos += pos;
}