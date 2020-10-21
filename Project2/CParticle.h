#pragma once
#include "CCamera.h"

#include <random>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class CParticle
{
public:
	CParticle(glm::vec3 _origin, glm::vec3 _velocity, float _elapsedTime);
	~CParticle();

	void Update(float deltaTime);
	float RandomNumber();
	glm::vec3 GetPosition();

private:
	glm::vec3 position;
	glm::vec3 velocity;
	float elapsedTime;

	float id;

	
	void ResetValues();
};