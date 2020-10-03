#include "CPlayScene.h"

CPlayScene::CPlayScene(CCamera* _gameCamera, CInput* _gameInput, FMOD::System* _audioSystem)
{
	gameCamera = _gameCamera;
	gameInput = _gameInput;
	audioSystem = _audioSystem;

	// Creates Programs For Objects In Scene
	program = CShaderLoader::CreateProgram("Resources/Shaders/Fog.vs",
		"Resources/Shaders/Fog.fs");

	programs = CShaderLoader::CreateProgram("Resources/Shaders/Basic.vs",
		"Resources/Shaders/Basic.fs");

	programSkybox = CShaderLoader::CreateProgram("Resources/Shaders/skybox.vs",
		"Resources/Shaders/skybox.fs");

	geomProgram = CShaderLoader::CreateProgram("Resources/Shaders/geometry.fs",
		"Resources/Shaders/geometry.fs", "Resources/Shaders/geometry.gs");
	
	//tessProgram = CShaderLoader::CreateProgram("Resources/Shaders/tessellaction.vs",
	//	"Resources/Shaders/tesTriangle.fs", "Resources/Shaders/tesQuad.fs", 
	//	"Resources/Shaders/tesQuadPatch.fs");

	// Generate Texte
	const char* fileLocation = "Resources/Textures/BackgroundSprite.png";
	TextureGen(fileLocation, &actorTex);

	const char* cubeFileLocation = "Resources/Textures/frogChair.jpg";
	TextureGen(cubeFileLocation, &actorCubeTex);

	const char* waterFileLocation = "Resources/Textures/WaterSprite.png";
	TextureGen(waterFileLocation, &actorWaterTex);

	// Geometry Model
	geomModel = new CGeometryModel(program, gameCamera);
	geomModel->SetPosition(glm::vec3(6.0f, 1.0f, 0.0f));

	tessModel = new CTessModel(program, gameCamera);
	tessModel->SetPostion(glm::vec3(6.0f, -2.0f, 0.0f));

	// Creates Mesh
	actorPyramid = new CPyramid();
	actorCube = new CCube(0.1f);
	actorMeshTest = new CCube(1.1f);
	actorPlane = new CPlane(10.0f, 10.0f);

	terrainMesh = new CTerrain(&programs, gameCamera, &actorCubeTex);

	gameActor = new CActor(&programs, actorCube->GetVAO(), actorCube->GetIndiceCount(), 
		gameCamera, &actorTex, audioSystem);

	// Create Game Actors
	actorCubeTwoObj = new CObject(&program, actorCube->GetVAO(), actorCube->GetIndiceCount(), gameCamera, &actorTex);
	actorCubeObj = new CObject(&program, actorMeshTest->GetVAO(), actorMeshTest->GetIndiceCount(), gameCamera, &actorCubeTex);
	waterActor = new CObject(&program, actorPlane->GetVAO(), actorPlane->GetIndiceCount(), gameCamera, &actorWaterTex);
	quadObj = new CObject(&program, actorPlane->GetVAO(), actorPlane->GetIndiceCount(), gameCamera, &actorCubeTex);

	// Create Skybox
	gameSkybox = new CSkybox(&programSkybox, gameCamera);

	// Labels
	restartLabel = new CTextLabel("Press 'R' to restart", "Resources/Fonts/arial.ttf", glm::vec2(10.0f, 570.0f), glm::vec3(0.0f, 1.0f, 0.5f), 0.5f);

	// Sets water location/rotaion
	waterActor->objPosition.y -= 0.5;
	waterActor->objAngleRotation = 180.0f;
	waterActor->objRotaion = vec3(0.f, 180.f, 180.f);

	// Sets quad location/rotaion
	quadObj->objPosition.y -= 0.8;
	quadObj->objAngleRotation = 180.0f;
	quadObj->objRotaion = vec3(0.f, 180.f, 180.f);
	quadObj->objScaleAmount = 2.0f;

}

CPlayScene::~CPlayScene()
{
}

void CPlayScene::Render()
{
	glUseProgram(program);

	// Enabling Culling
	glFrontFace(GL_CCW);
	glCullFace(GL_FRONT);
	//glEnable(GL_CULL_FACE);

	restartLabel->Render(); // Call before scissor test
	

	// Enables and declares scissor rectangle
	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 50, 1200, 500);


	if (isWireFrame)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
	}

	

	// Stencil set up
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);
	// Draw first actor
	
	//actorCubeTwoObj->Render();

	// The second pass
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF); 
	glStencilMask(0x00);
	// Draw second actor

	//actorCubeObj->Render();

	// Disable stencil
	glStencilMask(0x00); //disable writing to stencil mask
	glDisable(GL_STENCIL_TEST); // Disable stencil test
	glStencilMask(0xFF); // Enable writing again for next time

	//quadObj->Render();

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Draw actors

	//waterActor->Render();

	//tessModel->Render();
	//geomModel->Render();

	// Disable blending
	glDisable(GL_BLEND);


	gameSkybox->Render();
	terrainMesh->Render();
	gameActor->Render();

	glPolygonMode(GL_FRONT, GL_FILL);

	glBindVertexArray(0);		// Unbinding VAO
	glDisable(GL_SCISSOR_TEST);	// Disables scissor rectangle
	glUseProgram(0);
}

void CPlayScene::Update(GLfloat* deltaTime, ESceneManager* _currentScene)
{
	currentScene = _currentScene;
	gameCamera->Update(*deltaTime);

	// Wire Frame Check
	if (gameInput->getKeyState('q') || gameInput->getKeyState('Q'))
	{
		isWireFrame = true;
	}
	if (gameInput->getKeyState('e') || gameInput->getKeyState('E'))
	{
		isWireFrame = false;
	}
	
	gameSkybox->Update();
	actorCubeTwoObj->Update();
	waterActor->Update();
	quadObj->Update();
	actorCubeObj->Update();
	terrainMesh->Update();
	gameActor->Update(*deltaTime, gameInput, terrainMesh);
	gameCamera->FollowActor(gameActor->objPosition);

	// Resets every thing in game scene
	if (gameInput->getKeyState('r') || gameInput->getKeyState('R'))
	{
		gameCamera->ResetCamPos(); // This is the only thing in the scene that changes
	}
}

void CPlayScene::TextureGen(const char* textureLocation, GLuint* texture)
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