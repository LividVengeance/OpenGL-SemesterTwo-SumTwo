#pragma once
#include <glew.h>

class CPlane
{
public:
	CPlane(float scaleX = 1.0f, float scaleY = 1.0f);
	~CPlane();

	GLuint* GetVAO();
	int GetIndiceCount();

	GLuint VAO;
	int indiceCount;

private:

};