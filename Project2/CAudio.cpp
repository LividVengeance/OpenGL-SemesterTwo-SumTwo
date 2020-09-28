#include "CAudio.h"

CAudio::CAudio(const char* givenFileLocation, FMOD::System* audioSystem, bool looping)
{
	classAudio = audioSystem;
	fileLocation = givenFileLocation;

	FMOD_RESULT result;

	if (looping)
	{
		result = audioSystem->createSound(fileLocation, FMOD_LOOP_NORMAL, 0, &newSound);
	}
	else
	{
		result = audioSystem->createSound(fileLocation, FMOD_DEFAULT, 0, &newSound);
	}

	if (result != FMOD_OK)
	{
		std::cout << "Failed to create sound from file location: " << fileLocation << std::endl;
	}
}

CAudio::~CAudio()
{
	//newSound->release();
}


void CAudio::PlaySound()
{
	classAudio->playSound(newSound, 0, false, 0);
}