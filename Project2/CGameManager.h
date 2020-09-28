#pragma once
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <fmod.hpp>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

// Actors
#include "CActor.h"

// Objects
#include "CSkybox.h"
#include "CTextLabel.h"

// Utilities
#include "CAudio.h"
#include "CCamera.h"
#include "CInput.h"
#include "CShaderLoader.h"

// Meshes
#include "CSphere.h"
#include "CPlane.h"
#include "CPyramid.h"

// Program Scenes
#include "CMainMenuScene.h"
#include "CPlayScene.h"

class CGameManager
{
public:
	CGameManager(int argc, char** argv);
	~CGameManager();

	void CreateAudioSystem();

	void KeyBoardDown(unsigned char key, int x, int y);
	void KeyBoardUp(unsigned char key, int x, int y);
	void MousePassiveMove(int x, int y);
	void MouseClick(int button, int state, int x, int y);
	void MouseMove(int x, int y);

	void Update();
	void Render();
	void ManagerMain();

private:
	GLuint VBO, EBO, VAO;
	FMOD::System* audioSystem;

	// Camera
	CCamera* gameCamera;

	CInput* gameInput;

	// Labels
	CTextLabel* labelExample;

	// Meshes
	CPyramid* gamePyramid;
	CSphere* gameSphere;
	CPlane* gamePlane;

	// Program Scenes
	CMainMenuScene* gameMainMenuScene;
	CPlayScene* gamePlayScene;

	float timeElapsed = 0;
	ESceneManager currentScene;
	GLfloat currentTime, previousTime, deltaTime;
};