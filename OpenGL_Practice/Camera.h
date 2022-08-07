#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<map>
#include<vector>

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"
#include"Inputs.h"

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 LookVector = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	std::vector<int> keys{
		GLFW_KEY_W,
		GLFW_KEY_A,
		GLFW_KEY_S,
		GLFW_KEY_D,
		GLFW_KEY_SPACE,
		GLFW_KEY_LEFT_CONTROL,
		GLFW_KEY_LEFT_SHIFT
	};

	bool mousePressed = false;
	std::map<int, bool> activeKeys;

	int width;
	int height;

	float speed = 0.1f;
	float sensitivity = 5000.0f;

	Camera(GLFWwindow* window, Input& input, int width, int height, glm::vec3 position);

	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);
	void Update(GLFWwindow* window, float deltaTime);
};

#endif