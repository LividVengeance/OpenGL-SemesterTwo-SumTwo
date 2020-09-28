#pragma once
#include "CObject.h"
#include "CSphere.h"
#include "CShaderLoader.h"
#include "CAudio.h"

#include <map>

class CActor : public CObject
{
public:
	CActor(GLint* _program, GLuint* _VAO, int _indiceCount, CCamera* _gameCamera, GLuint* _texture, FMOD::System* _audioSystem);
	~CActor();

	void MoveInput(GLfloat deltaTime, CInput* gameInput);

	void TextureGen(const char* textureLocation, GLuint* texture);

	CSphere* actorSphere;
	GLuint texture;
	GLint program;

	FMOD::System* audioSystem;
};