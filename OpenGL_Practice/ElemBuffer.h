#ifndef ELEMENT_BUFFER_CLASS_H
#define ELEMENT_BUFFER_CLASS_H

#include <glad/glad.h>

class ElemBuffer {
	public:
		GLuint ID;
		ElemBuffer(GLuint* indices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
};

#endif