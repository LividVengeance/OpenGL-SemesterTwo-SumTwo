#pragma once

#include <glew.h>
#include <freeglut.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class CSphere
{
public:
	CSphere();
	~CSphere();

	void Render();

	GLuint* GetVAO();
	GLuint GetIndiceCount();

private:
	GLuint VAO;

	GLuint IndiceCount;
	int DrawType;
};

