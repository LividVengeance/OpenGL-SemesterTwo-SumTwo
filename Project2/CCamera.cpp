#pragma

#include "CCamera.h"

CCamera::CCamera()
{
	// 3D Camera
	camPos = vec3(0.0f, 0.0f, 3.0f);
	camLookDir = vec3(0.0f, 0.0f, -1.0f);
	camUpDir = vec3(0.0f, 1.0f, 0.0f);

	// 2D Camera
	camPos2D = vec3(0.0f, 0.0f, 3.0f);
	camLookDir2D = vec3(0.0f, 0.0f, -1.0f);
	camUpDir2D = vec3(0.0f, 1.0f, 0.0f);

	ResetCamPos();
}

CCamera::~CCamera()
{
}

mat4 CCamera::CameraView()
{
	proj = glm::perspective(45.0f, halfScreenWidth / halfScreenHeight, 0.1f, 10000.0f);
	return(view);
}

mat4 CCamera::CameraView2D()
{
	//proj2D = ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
	view2D = glm::lookAt(camPos2D, camPos2D + camLookDir2D, camUpDir2D);
	return(view2D);
}

void CCamera::Update(GLfloat deltaTime)
{
	view = glm::lookAt(camPos, glm::vec3(0.0f, 0.0f, 0.0f), camUpDir);
	proj = glm::perspective(45.0f, halfScreenWidth / halfScreenHeight, 0.1f, 10000.0f);
}

void CCamera::Update2D()
{
	view = glm::lookAt(camPos2D, camPos2D + camLookDir2D, camUpDir2D);
	proj2D = ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);
}

mat4 CCamera::CameraProjection()
{
	return(proj);
}

mat4 CCamera::CameraProjection2D()
{
	return(proj2D);
}

vec3 CCamera::GetCamPos()
{
	return(camPos);
}

void CCamera::MoveCamera(GLfloat deltaTime, bool moveRight)
{
	totalTime = moveRight ? totalTime += deltaTime : totalTime -= deltaTime;

	camPos.x = sin(totalTime) * radius;
	camPos.y = 1.5f;
	camPos.z = cos(totalTime) * radius;
}

void CCamera::CameraRadius(float newRadius)
{
	radius += newRadius;
}

void CCamera::ResetCamPos()
{
	// Setting defualt Camera Positions
	camPos.x = 4.9f;
	camPos.y = 1.5f;
	camPos.z = 3.0f;

	radius = 5.0f;
}