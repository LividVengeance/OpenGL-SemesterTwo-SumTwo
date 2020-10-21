#pragma once
#include "CCamera.h"
#include "CParticle.h"
#include "CShaderLoader.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class CParticleSystem
{
public:
	CParticleSystem(glm::vec3 origin, CCamera* _camera, std::string texFileName);
	~CParticleSystem();

	void Render(float deltaTime);

	std::vector<CParticle> particles;
	std::vector<glm::vec3> vPosition;

private:
	float RandomNumber();
	void TextureGen(const char* textureLocation, GLuint* texture);

	CCamera* gameCamera;
	GLuint VAO, VBO, texture, program;
	float nParticles;
};

