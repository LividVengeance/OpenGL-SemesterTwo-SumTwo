#pragma once
#include "CCamera.h"

class CCube
{
public:
	CCube(float size);
	~CCube();

	GLuint* GetVAO();
	int GetIndiceCount();

private:
	GLuint VAO;
	float indiceCount;
};