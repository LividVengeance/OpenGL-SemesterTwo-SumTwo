#include "CParticle.h"

CParticle::CParticle(glm::vec3 _origin, glm::vec3 _velocity, float _elapsedTime)
{
	position = _origin;
	velocity = _velocity;
	elapsedTime = _elapsedTime;
}

CParticle::~CParticle()
{
}

void CParticle::Update(float deltaTime)
{
	velocity.y += -0.2f * deltaTime;
	position += velocity;
	elapsedTime -= deltaTime;

	if (elapsedTime <= 0.0f)
	{
		ResetValues();
	}
}

float CParticle::RandomNumber()
{
	return((float)rand() / (double)RAND_MAX);
}

void CParticle::ResetValues()
{
	velocity = glm::vec3(0.25 * cos(id * 0.0167f) + 0.25f * RandomNumber() - 0.125f,
		1.5f + 0.25f * RandomNumber() - 0.125f,
		0.25f * sin(id * 0.0167) + 0.25f * RandomNumber() - 0.125f);
	elapsedTime = RandomNumber() + 0.125f;
}

glm::vec3 CParticle::GetPosition()
{
	return(position);
}