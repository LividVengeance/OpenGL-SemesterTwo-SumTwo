#pragma once
#include "CObject.h"
#include "CPlane.h"
#include "CShaderLoader.h"
#include "CAudio.h"

class CActorWater : public CObject
{
public:
	CActorWater(GLint* _program, GLuint* _VAO, int _indiceCount, CCamera* _gameCamera, GLuint* _texture, FMOD::System* _audioSystem);
	~CActorWater();

	void TextureGen(const char* textureLocation, GLuint* texture);

	CPlane* actorPlane;
	GLuint texture;
	GLint program;

	FMOD::System* audioSystem;
};