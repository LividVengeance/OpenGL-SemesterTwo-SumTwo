#include "CParticleSystem.h"

CParticleSystem::CParticleSystem(glm::vec3 origin, CCamera* _camera, std::string texFileName)
{
	gameCamera = _camera;
	nParticles = 4000;

	TextureGen("Resources/Textures/BackgroundSprite.png", &texture);

	program = CShaderLoader::CreateProgram("Resources/Shaders/particle.vs",
		"Resources/Shaders/particle.fs", "Resources/Shaders/particle.gs");

	for (int i = 0; i < nParticles; i++)
	{
		// initalize position vector
		vPosition.push_back(glm::vec3(0.0));

		CParticle p = CParticle(origin,
			glm::vec3(0.25 * cos(i * .0167) + 0.25f * RandomNumber() - 0.125f, // vel
				2.0f + 0.25f * RandomNumber() - 0.125f,
				0.25 * sin(i * .0167) + 0.25f * RandomNumber() - 0.125f),
			RandomNumber() + 0.125 // elapsed time
		);

		particles.push_back(p);
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenVertexArrays(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vPosition.size(), &vPosition[0], GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

CParticleSystem::~CParticleSystem()
{
}

void CParticleSystem::Render(float deltaTime)
{
	for (int i = 0; i < nParticles; i++)
	{
		particles[i].Update(deltaTime);
		vPosition[i] = particles[i].GetPosition();
	}

	glm::vec3 vQuad1, vQuad2;

	glm::vec3 camFront = gameCamera->LookDir();
	camFront = glm::normalize(camFront);

	vQuad1 = glm::cross(camFront, gameCamera->UpDir());
	vQuad1 = glm::normalize(vQuad1);

	vQuad2 = glm::cross(camFront, vQuad1);
	vQuad2 = glm::normalize(vQuad2);

	glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "vQuad1"), vQuad1.x, vQuad1.y, vQuad1.z);
	glUniform3f(glGetUniformLocation(program, "vQuad2"), vQuad2.x, vQuad2.y, vQuad2.z);

	glUniformMatrix4fv(glGetUniformLocation(program, "vp"), 1, GL_FALSE, glm::value_ptr(gameCamera->GetView()));
	
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(program, "Texture"), 0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vPosition.size(), &vPosition[0], GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glDrawArrays(GL_POINTS, 0, nParticles);
	glBindVertexArray(0);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

float CParticleSystem::RandomNumber()
{
	return((float)rand() / (double)RAND_MAX);
}

void CParticleSystem::TextureGen(const char* textureLocation, GLuint* texture)
{
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);

	int width, height;
	unsigned char* image1 = SOIL_load_image(textureLocation, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}