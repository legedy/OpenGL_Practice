#ifndef VERTEX_ARRAY_CLASS_H
#define VERTEX_ARRAY_CLASS_H

#include<glad/glad.h>
#include"VertBuffer.h"

class VertArr {
	public:
		GLuint ID;
		VertArr();

		void LinkAttrib(VertBuffer VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
};

#endif