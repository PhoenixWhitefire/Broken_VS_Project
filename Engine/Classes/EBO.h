#ifndef CLASS_EBO
#define CLASS_EBO

#include<glad/glad.h>
#include<vector>

class EBO {
	public:
		GLuint ID;

		EBO();

		void SetBufferData(std::vector<GLuint>& Indices);

		void Bind();
		void Unbind();
		void Destroy();
};

#endif
