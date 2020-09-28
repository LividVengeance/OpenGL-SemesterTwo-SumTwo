#include "CCube.h"

CCube::CCube(float size)
{
	GLfloat vertices[] = { // Cube

		// Front
		-size, size, size,     0.0f, 1.0f, 0.0f,      0.0f , 0.0f,
		-size, -size,size,     0.0f, 1.0f, 0.0f,      0.0f , 1.0f,
		 size, -size,size,     0.0f, 1.0f, 0.0f,      1.0f , 1.0f,
		 size, size, size,     0.0f, 1.0f, 0.0f,      1.0f , 0.0f,

		 // Back
		-size, size, -size,  0.0f, 1.0f, 0.0f,      1.0f , 0.0f,
		-size, -size, -size, 0.0f, 1.0f, 0.0f,      1.0f , 1.0f,
		 size, -size, -size, 0.0f, 1.0f, 0.0f,      0.0f , 1.0f,
		 size, size, -size,  0.0f, 1.0f, 0.0f,      0.0f , 0.0f,

		 // Left
		-size, size, -size,  0.0f, 1.0f, 0.0f,      0.0f , 0.0f,
		-size, -size, -size, 0.0f, 1.0f, 0.0f,      0.0f , 1.0f,
		-size, -size, size,  0.0f, 1.0f, 0.0f,      1.0f , 1.0f,
		-size, size, size,   0.0f, 1.0f, 0.0f,      1.0f , 0.0f,

		// Right
		size, size, size,    0.0f, 1.0f, 0.0f,      0.0f , 0.0f,
		size, -size, size,   0.0f, 1.0f, 0.0f,      0.0f , 1.0f,
		size, -size, -size,  0.0f, 1.0f, 0.0f,      1.0f , 1.0f,
		size, size, -size,   0.0f, 1.0f, 0.0f,     1.0f , 0.0f,

		// Top
		-size, size, -size,  0.0f, 1.0f, 0.0f,      0.0f , 0.0f,
		-size, size,  size,  0.0f, 1.0f, 0.0f,      0.0f , 1.0f,
		 size, size,  size,  0.0f, 1.0f, 0.0f,      1.0f , 1.0f,
		 size, size, -size,  0.0f, 1.0f, 0.0f,      1.0f , 0.0f,

		 // Bottom
		-size, -size,  size, 0.0f, 1.0f, 0.0f,      0.0f , 0.0f,
		-size, -size, -size, 0.0f, 1.0f, 0.0f,      0.0f , 1.0f,
		 size, -size, -size, 0.0f, 1.0f, 0.0f,      1.0f , 1.0f,
		 size, -size,  size, 0.0f, 1.0f, 0.0f,      1.0f , 0.0f,

	};
	GLuint indices[] = {
		0, 1, 2, // Front
		0, 2, 3, // Front

		7, 6, 5, // Back
		7, 5, 4, // Back

		8, 9, 10, // Left
		8, 10, 11, // Left

		12, 13, 14, // Right
		12, 14, 15, // Right

		16, 17, 18, // Top
		16, 18, 19, // Top

		20, 21, 22, // Bottom
		20, 22, 23, // Bottom
	};

	indiceCount = sizeof(indices) / sizeof(int);

	GLuint EBO, VBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),	// Stride of the single vertex (pos + color)
		(GLvoid*)0);			// Offset from beginning of Vertex
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),				// Stride of the single vertex (pos + color)
		(GLvoid*)(3 * sizeof(GLfloat)));	// Offset from beginning of Vertex
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

CCube::~CCube()
{
}

GLuint* CCube::GetVAO()
{
	return(&VAO);
}

int CCube::GetIndiceCount()
{
	return(indiceCount);
}