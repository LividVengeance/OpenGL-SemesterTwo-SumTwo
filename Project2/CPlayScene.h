#pragma once
// Utilities
#include "CShaderLoader.h"
#include "CCamera.h"
#include "CInput.h"
#include "CTextLabel.h"
#include "CGeometryModel.h"
#include "CTerrain.h"

// Actors
#include "CActor.h"

// Meshes
#include "CPyramid.h"
#include "CSphere.h"
#include "CSkybox.h"
#include "CPlane.h"
#include "Model.h"
#include "CCube.h"

// Particle System
#include "CParticleSystem.h"


class CPlayScene
{
public:
	CPlayScene(CCamera* _gameCamera, CInput* _gameInput, FMOD::System* _audioSystem);
	~CPlayScene();

	void Render();
	void Update(GLfloat* deltaTime, ESceneManager* _currentScene);

private:
	void TextureGen(const char* textureLocation, GLuint* texture);

	bool isWireFrame = false;

	// Programs
	GLint program;
	GLint programs;
	GLint programSkybox;
	GLint geomProgram;

	// Audio
	FMOD::System* audioSystem;

	// Utilities
	ESceneManager* currentScene;
	CCamera* gameCamera;
	CInput* gameInput;
	CGeometryModel* geomModel;

	// Meshes
	CCube* actorCube;
	CSkybox* gameSkybox;
	CTerrain* terrainMesh;

	// Objects
	CActor* gameActor;

	// Particle System
	CParticleSystem* particleSystem;

	// Textures
	GLuint actorTex;
	GLuint actorCubeTex;
};