#include"Camera.h"

Camera::Camera(GLFWwindow* window, Input& input, int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;

	input.registerMouse(GLFW_MOUSE_BUTTON_LEFT, [window, width, height, this](GLFWwindow* win, int state) {
		if (state == GLFW_PRESS) {
			glfwSetCursorPos(window, (width / 2), (height / 2));
			mousePressed = true;
		} else if (state == GLFW_RELEASE)
			mousePressed = false;
	});

	for (int keyBind : keys) {
		input.registerKey(keyBind, [keyBind, this](GLFWwindow* win, int state) {
			if (state == GLFW_PRESS)
				activeKeys[keyBind] = true;
			else if (state == GLFW_RELEASE)
				activeKeys[keyBind] = false;
		});
	}

}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane) {
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + LookVector, UpVector);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Update(GLFWwindow* window, float deltaTime) {

	if (activeKeys[GLFW_KEY_W])
		Position += speed * (LookVector * deltaTime);

	if (activeKeys[GLFW_KEY_A])
		Position += speed * -(glm::normalize(glm::cross(LookVector, UpVector)) * deltaTime);

	if (activeKeys[GLFW_KEY_S])
		Position += speed * -(LookVector * deltaTime);

	if (activeKeys[GLFW_KEY_D])
		Position += speed * (glm::normalize(glm::cross(LookVector, UpVector)) * deltaTime);

	if (activeKeys[GLFW_KEY_SPACE])
		Position += speed * (UpVector * deltaTime);

	if (activeKeys[GLFW_KEY_LEFT_CONTROL])
		Position += speed * -(UpVector * deltaTime);

	if (activeKeys[GLFW_KEY_LEFT_SHIFT])
		speed = 2.0f;
	else
		speed = 4.5f;

	if (mousePressed) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		double deltaMouseX = (mouseY - (height / 2)) / height;
		double deltaMouseY = (mouseX - (width / 2)) / width;

		double rotX = deltaMouseX * sensitivity * deltaTime;
		double rotY = deltaMouseY * sensitivity * deltaTime;
		std::cout << deltaTime << std::endl;

		glm::vec3 newOrientation = glm::rotate(LookVector, glm::radians((float)(-rotX)), glm::normalize(glm::cross(LookVector, UpVector)));

		if (abs(glm::angle(newOrientation, UpVector) - glm::radians(90.0f)) <= glm::radians(85.0f))
			LookVector = newOrientation;

		LookVector = glm::rotate(LookVector, glm::radians((float)(-rotY)), UpVector);

		glfwSetCursorPos(window, (width / 2), (height / 2));
	} else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}