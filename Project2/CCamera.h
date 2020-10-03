#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Utilities.h"

using namespace glm;

class CCamera
{
public:
	CCamera();
	~CCamera();

	// 3D Camera
	void Update(GLfloat deltaTime);
	mat4 CameraView();
	mat4 CameraProjection();

	// 2D Camera
	void Update2D();
	mat4 CameraView2D();
	mat4 CameraProjection2D();

	vec3 GetCamPos();
	void ResetCamPos();

	void MoveCamera(GLfloat deltaTime, bool moveRight);
	void CameraRadius(float newRadius);
	void FollowActor(glm::vec3 _objPosition);

private:
	float halfScreenWidth = Utils::SCR_WIDTH * 0.5f;
	float halfScreenHeight = Utils::SCR_HEIGHT * 0.5f;

	// 3D Camera
	vec3 camPos;
	vec3 camLookDir;
	vec3 camUpDir;

	glm::vec3 objPosition;

	mat4 proj;
	mat4 view;

	// 2D Camera
	vec3 camPos2D;
	vec3 camLookDir2D;
	vec3 camUpDir2D;

	mat4 proj2D;
	mat4 view2D;

	float timeElapsed = 0;
	GLfloat totalTime = 0;
	float radius = 5.0f;
};