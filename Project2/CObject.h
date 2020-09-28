#pragma once

#include "CCamera.h"
#include "CInput.h"
#include "CSkybox.h"

class CObject
{
public:
	CObject(GLint* _program, GLuint* _VAO, int _indiceCount, CCamera* _gameCamera, GLuint* _texture);
	~CObject();

	void Update();
	void Render();
	void Render2D();
	void RenderReflection(CSkybox* skyboxObj);

	// Object Location
	vec3 objPosition;
	vec3 objScale;
	vec3 objRotaion;
	float objAngleRotation;
	float objScaleAmount;
	mat4 objModelMatrix;

	float collisionRadus = 0.5;

protected:
	GLint* program;
	GLuint* VAO;
	float indiceCount;
	CCamera* gameCamera;
	GLuint* texture;
};

