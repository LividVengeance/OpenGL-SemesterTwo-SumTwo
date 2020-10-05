#pragma once
#include "CCamera.h"

class CGeometryModel
{
public:
	CGeometryModel(GLint _program, CCamera* _camera);
	~CGeometryModel();

	void Render();
	void SetPosition(glm::vec3 _newPos);
	void Update();

	// Object Location
	vec3 objPosition;
	vec3 objScale;
	vec3 objRotaion;
	float objAngleRotation;
	mat4 objModelMatrix;

private:
	CCamera* camera;
	GLint program;

	GLuint VAO, VBO;

	glm::vec3 position;
};