#pragma once
#include "CCamera.h"

class CTessModel
{
public:
	CTessModel(GLuint _program, CCamera* _camera);
	~CTessModel();

	void Render();
	void SetPostion(glm::vec3 _newPos);

private:
	GLuint program;
	CCamera* camera;

	glm::vec3 position;

	GLuint VAO, VBO;
};