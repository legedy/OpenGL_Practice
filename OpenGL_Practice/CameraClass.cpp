#include"CameraClass.h"


Camera::Camera(GLFWwindow* window, int width, int height, glm::vec3 position) {Camera::width = width;
	Camera::height = height;
	Position = position;

	glfwSetCursorPosCallback(window, _OnMouseMoved);
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + LookVector, UpVector);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}



void Camera::Inputs(GLFWwindow* window, float deltaTime) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		Position += speed * (LookVector * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Position += speed * -(glm::normalize(glm::cross(LookVector, UpVector)) * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Position += speed * -(LookVector * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
		Position += speed * (glm::normalize(glm::cross(LookVector, UpVector)) * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		Position += speed * (UpVector * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		Position += speed * -(UpVector * deltaTime);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) 
		speed = 1.0f;
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		speed = 2.5f;


	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(LookVector, glm::radians(-rotX * deltaTime), glm::normalize(glm::cross(LookVector, UpVector)));

		if (abs(glm::angle(newOrientation, UpVector) - glm::radians(90.0f)) <= glm::radians(85.0f))
			LookVector = newOrientation;

		LookVector = glm::rotate(LookVector, glm::radians(-rotY * deltaTime), UpVector);

		glfwSetCursorPos(window, (width / 2), (height / 2));
	} else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}

void Camera::_OnMouseMoved(GLFWwindow* window, double xpos, double ypos) {
	std::cout << xpos << "	" << ypos << "\n";
}