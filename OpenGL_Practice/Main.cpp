#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VertArr.h"
#include"VertBuffer.h"
#include"ElemBuffer.h"

const unsigned int width = 800;
const unsigned int height = 800;

const float ratio = (float)(width / height);


GLfloat vertices[] =
{ //     COORDINATES             COLORS         TexCoord
	//-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	//-0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
	// 0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
	// 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,	1.0f, 0.0f

	-0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
	-0.5f,  0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	 0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
	 0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f, // Lower left corner
	-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f, // Upper left corner
	 0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,	// Upper right corner
	 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,	1.0f, 1.0f, // Lower right corner
};

GLuint indices[] = {
	//0, 2, 1,
	//0, 3, 2,

	//4, 6, 5,
	//4, 7, 6,
	
	0, 4, 5,
	5, 6, 0
};



int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "poop", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, width, height);

	Shader shaderProgram("vertex.glsl", "fragment.glsl");

	VertArr VAO;
	VAO.Bind();

	VertBuffer VBO(vertices, sizeof(vertices));
	ElemBuffer EBO(indices, sizeof(indices));

	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	Texture poop("kanye.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	poop.texUnit(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::translate(model, glm::vec3(0, 0, -2));
		view = glm::translate(view, glm::vec3(0, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);

		int modelPos = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelPos, 1, GL_FALSE, glm::value_ptr(model));
		int viewPos = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewPos, 1, GL_FALSE, glm::value_ptr(view));
		int projPos = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projPos, 1, GL_FALSE, glm::value_ptr(proj));

		glUniform1f(uniID, 0.5f);
		poop.Bind();
		VAO.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
	poop.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}