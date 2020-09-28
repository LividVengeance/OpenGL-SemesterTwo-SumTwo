#include "CPyramid.h"

CPyramid::CPyramid()
{
	GLfloat vertices[]{
		// Position				// Normal			// Texture Coords
		 -1.0f,	0.0f, -1.0f,	0.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// 0
		 -1.0f,	0.0f,  1.0f,	0.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// 1
		  1.0f,	0.0f,  1.0f,	0.0f, 0.0f,	0.0f,	1.0f, 1.0f,	// 2
		  1.0f,	0.0f, -1.0f,	0.0f, 0.0f,	0.0f,	1.0f, 0.0f,	// 3

		  0.0f, 1.0f,  0.0f,	0.0f, 1.0f,	1.0f,	0.5f, 0.5f, // 4 Top Point
	};
	GLuint indices[] = {
		0, 4, 3,	// Side 1
		3, 4, 2,	// Side 2
		2, 4, 1,	// Side 3
		1, 4, 0,	// Side 4

		1, 0, 3,	// Side Bottom Triangle 1
		1, 3, 2,	// Side Bottom Triangle 2
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

CPyramid::~CPyramid()
{
}

GLuint* CPyramid::GetVAO()
{
	return(&VAO);
}

int CPyramid::GetIndiceCount()
{
	return(indiceCount);
}