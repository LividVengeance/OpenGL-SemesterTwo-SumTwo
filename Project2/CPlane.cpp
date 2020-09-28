#include "CPlane.h"

CPlane::CPlane(float scaleX, float scaleY)
{
	GLfloat vertices[]{
		// Position									// Color				// Texture Coords
		 -0.5f * scaleX,  0.5f * scaleY, 0.0f,		1.0f, 1.0f,	 1.0f,		0.0f,   0.0f,	// Top Right
		  0.5f * scaleX,  0.5f * scaleY, 0.0f,		1.0f, 1.0f,	 1.0f,		1.0f,   0.0f,	// Bot Left
		 -0.5f * scaleX, -0.5f * scaleY, 0.0f,		1.0f, 1.0f,	 1.0f,		0.0f,   1.0f,	// Top Left
		  0.5f * scaleX, -0.5f * scaleY, 0.0f,		1.0f, 1.0f,	 1.0f,		1.0f,   1.0f,	// Bot Right
	};
	GLuint indices[] = {
		1, 0, 2,	// First Triangle
		3, 1, 2,	// Second Triangle
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

CPlane::~CPlane()
{

}

GLuint* CPlane::GetVAO()
{
	return(&VAO);
}

int CPlane::GetIndiceCount()
{
	return(indiceCount);
}