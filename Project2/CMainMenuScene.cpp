#include "CMainMenuScene.h"

CMainMenuScene::CMainMenuScene(CCamera* _gameCamera, CInput* _gameInput)
{
	gameCamera = _gameCamera;
	gameInput = _gameInput;

	program = CShaderLoader::CreateProgram("Resources/Shaders/Basic.vs",
		"Resources/Shaders/Basic.fs");

	// Gen Textures For Buttons
	const char* fileLocationPlay = "Resources/Textures/MainMenu/playSprite.png";
	TextureGen(fileLocationPlay, &playButtonTex);
	const char* fileLocationExit = "Resources/Textures/MainMenu/exitSprite.png";
	TextureGen(fileLocationExit, &exitButtonTex);
	const char* fileLocationTitle = "Resources/Textures/MainMenu/titleSprite.png";
	TextureGen(fileLocationTitle, &titleTex);
	// Create Type
	buttonPlane = new CPlane(150.0f, 50.0f);
	titlePlane = new CPlane(200.0f, 50.0f);
	
	playButtonObj = new CObject(&program, buttonPlane->GetVAO(), buttonPlane->GetIndiceCount(), gameCamera, &playButtonTex);
	exitButtonObj = new CObject(&program, buttonPlane->GetVAO(), buttonPlane->GetIndiceCount(), gameCamera, &exitButtonTex);
	titleObj = new CObject(&program, titlePlane->GetVAO(), titlePlane->GetIndiceCount(), gameCamera, &titleTex);

	playButtonObj->objPosition.x -= (Utils::SCR_WIDTH/2) - 200;
	playButtonObj->objPosition.y += (Utils::SCR_HEIGHT/2) - 150;

	exitButtonObj->objPosition.x -= (Utils::SCR_WIDTH / 2) - 200;
	exitButtonObj->objPosition.y += (Utils::SCR_HEIGHT / 2) - 200;

	titleObj->objPosition.x -= (Utils::SCR_WIDTH / 2) - 225;
	titleObj->objPosition.y += (Utils::SCR_HEIGHT / 2) - 75;
}

CMainMenuScene::~CMainMenuScene()
{
}

void CMainMenuScene::Render()
{
	glUseProgram(program);
	glDisable(GL_CULL_FACE);

	playButtonObj->Render2D();
	exitButtonObj->Render2D();
	titleObj->Render2D();

	glBindVertexArray(0);		// Unbinding VAO
	glUseProgram(0);
}

void CMainMenuScene::Update(GLfloat* deltaTime, ESceneManager* _currentScene)
{
	currentScene = _currentScene;
	gameCamera->Update2D();

	// Objects
	playButtonObj->Update();
	exitButtonObj->Update();
	titleObj->Update();

	// Mouse has clicked button check
	if (Button(200, 50, playButtonObj))
	{
		// Play Button
		*currentScene = EPlayScene;
	}
	if (Button(200, 50, exitButtonObj))
	{
		// Exit program
		glutDestroyWindow(program);
	}
}

bool CMainMenuScene::Button(float width, float height, CObject* _buttonObj)
{
	mouseX = gameInput->getMouseX();
	mouseY = gameInput->getMouseY();

	float offSetX = Utils::SCR_WIDTH / 2;
	float offSetY = Utils::SCR_HEIGHT / 2;

	if (-(offSetX - mouseX) > _buttonObj->objPosition.x - width / 2 &&
		-(offSetX - mouseX) < _buttonObj->objPosition.x + width / 2 &&
		offSetY - mouseY > _buttonObj->objPosition.y - height / 2 &&
		offSetY - mouseY < _buttonObj->objPosition.y + height / 2 &&
		(gameInput->GetFirstDown(0) || gameInput->GetFirstDown(1)))
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

void CMainMenuScene::TextureGen(const char* textureLocation, GLuint* texture)
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