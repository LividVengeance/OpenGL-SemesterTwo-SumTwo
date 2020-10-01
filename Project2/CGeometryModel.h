#pragma once
#include "CCamera.h"

class CGeometryModel
{
public:
	CGeometryModel(GLuint _program, CCamera* _camera);
	~CGeometryModel();

	void Render();
	void SetPosition(glm::vec3 _newPos);

private:
	CCamera* camera;
	GLuint program;

	GLuint VAO, VBO;

	glm::vec3 position;
};

