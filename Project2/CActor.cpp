#include "CActor.h"

CActor::CActor(GLint* _program, GLuint* _VAO, int _indiceCount, CCamera* _gameCamera, GLuint* _texture, FMOD::System* _audioSystem)
	: CObject(_program, _VAO, _indiceCount, _gameCamera, _texture)
{
	audioSystem = _audioSystem;

	program = CShaderLoader::CreateProgram("Resources/Shaders/Fog.vs",
		"Resources/Shaders/Fog.fs");
	
	// Gen Textures For Actor
	const char* fileLocationBullet = "Resources/Textures/BackgroundSprite.png";
	TextureGen(fileLocationBullet, &texture);
	
	actorSphere = new CSphere();
}

CActor::~CActor()
{
}

void CActor::MoveInput(GLfloat deltaTime, CInput* gameInput)
{
	
}

void CActor::TextureGen(const char* textureLocation, GLuint* texture)
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