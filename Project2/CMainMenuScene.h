#pragma once

#include "CShaderLoader.h"
#include "CCamera.h"
#include "CInput.h"
#include "CObject.h"
#include "CPlane.h"

class CMainMenuScene
{
public:
	CMainMenuScene(CCamera* _gameCamera, CInput* _gameInput);
	~CMainMenuScene();

	void Render();
	void Update(GLfloat* deltaTime, ESceneManager* _currentScene);
	bool Button(float width, float height, CObject* _buttonObj);
	void TextureGen(const char* textureLocation, GLuint* texture);

	float mouseX;
	float mouseY;

	float offSetX = Utils::SCR_WIDTH / 2;
	float offSextY = Utils::SCR_HEIGHT / 2;

	CCamera* gameCamera;
	mat4 view;

	GLint program;

	ESceneManager* currentScene;

	// Button Textures
	GLuint playButtonTex;
	GLuint exitButtonTex;
	GLuint titleTex;
	// Button Objects
	CObject* playButtonObj;
	CObject* exitButtonObj;
	CObject* titleObj;
	// Button Type
	CPlane* buttonPlane;
	CPlane* titlePlane;

	CInput* gameInput;

private:

};

