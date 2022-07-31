#include "VertBuffer.h"

VertBuffer::VertBuffer(GLfloat* vertices, GLintptr size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
 }

void VertBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertBuffer::Delete() {
	glDeleteBuffers(1, &ID);
}