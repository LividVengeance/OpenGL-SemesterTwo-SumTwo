#pragma once
#include "CCamera.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "glm.hpp"

class CTerrain
{
public:
	std::string HeightmapFilename;
	float HeightScale = 0.35f;
	float HeightOffset = -20.0f;
	int NumRows = 513;
	int NumCols = 513;
	float CellSpacing = 1.0f;
	
	CTerrain(GLint* _program, CCamera* _camera, GLuint* _texture);// , std::string _FileName);
	~CTerrain();

	float Width() const;
	float Depth() const;
	float GetHeight(float x, float z) const;
	void Update();
	void Render();

private:

	CCamera* camera;
	GLuint* texture;
	UINT numVertices;
	UINT numFaces;

	GLint* program;
	GLuint VAO;
	float indiceCount;

	std::vector<float> heightmap;
	void LoadHeightMap();
	void Smooth();
	float Average(int i, int j);
	bool IsInBounds(int i, int j);

	void BuildVBIB();

	// Object Location
	vec3 objPosition;
	vec3 objScale;
	vec3 objRotaion;
	float objAngleRotation;
	float objScaleAmount;
	mat4 objModelMatrix;
};

