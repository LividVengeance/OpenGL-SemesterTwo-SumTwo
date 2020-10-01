#pragma once
#include "CCamera.h"

#include <fstream>
#include <string>
#include <vector>

#include "glm.hpp"

class CTerrain
{
public:
	struct InitInfo
	{
		std::wstring HeightmapFilename;
		std::wstring LayerMapFilename0;
		std::wstring LayerMapFilename1;
		std::wstring LayerMapFilename2;
		std::wstring LayerMapFilename3;
		std::wstring LayerMapFilename4;
		std::wstring BlendMapFilename;
		float HeightScale;
		float HeightOffset;
		int NumRows;
		int NumCols;
		float CellSpacing;
	};
	
	CTerrain(GLint* _program, GLuint* _VAO, CCamera* _camera, GLuint* _texture);
	~CTerrain();

	float Width() const;
	float Depth() const;
	float GetHeight(float x, float z) const;

	void Init(const InitInfo& _initInfo);
	void SetDirectionToSun(const glm::vec3& v);
	void Draw();

private:
	InitInfo initInfo;

	CCamera* camera;
	GLuint* texture;
	int numVertices;
	int numFaces;

	GLint* program;
	GLuint* VAO;
	float indiceCount;

	std::vector<float> heightmap;
	void LoadHeightMap();
	void Smooth();
	float Average(int i, int j);
	bool IsInBounds(int i, int j);

	void BuildVBIB();
};

