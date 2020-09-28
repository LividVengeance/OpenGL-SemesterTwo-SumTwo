#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <fmod.hpp>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


class CAudio
{
public:
	CAudio(const char* fileLocation, FMOD::System* audioSystem, bool looping);
	~CAudio();

	FMOD::System* classAudio;
	FMOD::Sound* newSound;
	void PlaySound();

private:
	const char* fileLocation;
};