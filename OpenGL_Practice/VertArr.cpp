#include"VertArr.h"

VertArr::VertArr() {
	glGenVertexArrays(1, &ID);
}

void VertArr::LinkAttrib(VertBuffer VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VertArr::Bind() {
	glBindVertexArray(ID);
}

void VertArr::Unbind() {
	glBindVertexArray(0);
}

void VertArr::Delete() {
	glDeleteVertexArrays(1, &ID);
}