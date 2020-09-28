#pragma once
#include "CCamera.h"

class CPyramid
{
public:
	CPyramid();
	~CPyramid();

	GLuint* GetVAO();
	int GetIndiceCount();

private:
	GLuint VAO;
	float indiceCount;
};

