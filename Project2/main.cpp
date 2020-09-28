#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <fmod.hpp>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "CGameManager.h"


int main(int argc, char** argv)
{
	CGameManager mainGameManager(argc, argv);
	mainGameManager.ManagerMain();

	return(0);
}