#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include"shaderClass.h"
#include"VertArr.h"
#include"ElemBuffer.h"

int main() {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,		0.8f, 0.3f,  0.2f,
		-0.5f,  0.5f, 0.0f,		0.8f, 0.3f,  0.2f,
		 0.5f,  0.5f, 0.0f,		1.0f, 0.6f,  0.32f,
		 0.5f, -0.5f, 0.0f,		0.9f, 0.45f, 0.17f
	};

	GLuint indices[] = {
		0, 2, 1,
		0, 3, 2
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "Leg", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);

	Shader shaderProgram("vertex.glsl", "fragment.glsl");

	VertArr VAO;
	VAO.Bind();

	VertBuffer VBO(vertices, sizeof(vertices));
	ElemBuffer EBO(indices, sizeof(indices));

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.1f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		VAO.Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}