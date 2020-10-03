#include "CTerrain.h"

namespace
{
	struct TerrainVertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texC;
	};
}

CTerrain::CTerrain(GLint* _program, CCamera* _camera, GLuint* _texture)//, std::string _FileName)
{
	camera = _camera;
	program = _program;
	texture = _texture;
	HeightmapFilename = "Resources/Textures/coastMountain513.raw";

	objPosition = vec3(0.0f, -30.0f, 1.0f);
	objRotaion = vec3(0.0f, 0.0f, 1.0f);
	objScale = vec3(1.0f, 1.0f, 1.0f);

	objScaleAmount = 1.0f;
	objAngleRotation = 0.0f;

	numVertices = NumRows * NumCols;
	numFaces = (NumRows - 1) * (NumCols - 1) * 2;

	LoadHeightMap();
	Smooth();
	BuildVBIB();
	Update();
}

CTerrain::~CTerrain()
{
}

float CTerrain::Width() const
{
	return((NumCols - 1) * CellSpacing);
}

float CTerrain::Depth() const
{
	return((NumRows- 1) * CellSpacing);
}

float CTerrain::GetHeight(float x, float z) const
{
	// Transform from terrain local space to "cell" space.
	float c = (x + 0.5f * Width()) / CellSpacing;
	float d = (z - 0.5f * Depth()) / -CellSpacing;

	// Get the row and column we are in.
	int row = (int)floorf(d);
	int col = (int)floorf(c);

	// Grab the heights of the cell we are in.
	// A*--*B
	//  | /|
	//  |/ |
	// C*--*D
	float A = heightmap[row * NumCols + col];
	float B = heightmap[row * NumCols + col + 1];
	float C = heightmap[(row + 1) * NumCols + col];
	float D = heightmap[(row + 1) * NumCols + col + 1];

	// Where we are relative to the cell.
	float s = c - (float)col;
	float t = d - (float)row;

	// If upper triangle ABC.
	if (s + t <= 1.0f)
	{
		float uy = B - A;
		float vy = C - A;
		return A + s * uy + t * vy;
	}
	else // lower triangle DCB.
	{
		float uy = C - D;
		float vy = B - D;
		return D + (1.0f - s) * uy + (1.0f - t) * vy;
	}
}

void CTerrain::LoadHeightMap()
{
	// A height for each vertex
	std::vector<unsigned char> in(NumRows * NumCols);

	// Open the file.
	std::ifstream inFile;
	inFile.open(HeightmapFilename.c_str(), std::ios_base::binary);

	if (inFile)
	{
		// Read the RAW bytes.
		inFile.read((char*)&in[0], (std::streamsize)in.size());

		// Done with file.
		inFile.close();
	}

	// Copy the array data into a float array, and scale and offset the heights.
	heightmap.resize(NumRows * NumCols, 0);
	for (UINT i = 0; i < NumRows * NumCols; ++i)
	{
		heightmap[i] = (float)in[i] * HeightScale + HeightOffset;
	}
}

bool CTerrain::IsInBounds(int i, int j)
{
	// True if ij are valid indices; false otherwise.
	return
		i >= 0 && i < NumRows &&
		j >= 0 && j < NumCols;
}

float CTerrain::Average(int i, int j)
{
	// Function computes the average height of the ij element.
	// It averages itself with its eight neighbor pixels.  Note
	// that if a pixel is missing neighbor, we just don't include it
	// in the average--that is, edge pixels don't have a neighbor pixel.
	//
	// ----------
	// | 1| 2| 3|
	// ----------
	// |4 |ij| 6|
	// ----------
	// | 7| 8| 9|
	// ----------

	float avg = 0.0f;
	float num = 0.0f;

	for (UINT m = i - 1; m <= i + 1; ++m)
	{
		for (UINT n = j - 1; n <= j + 1; ++n)
		{
			if (IsInBounds(m, n))
			{
				avg += heightmap[m * NumCols + n];
				num += 1.0f;
			}
		}
	}

	return (avg / num);
}

void CTerrain::Smooth()
{
	std::vector<float> dest(heightmap.size());

	for (UINT i = 0; i < NumRows; ++i)
	{
		for (UINT j = 0; j < NumCols; ++j)
		{
			dest[i * NumCols + j] = Average(i, j);
		}
	}

	// Replace the old heightmap with the filtered one.
	heightmap = dest;
}

void CTerrain::Render()
{
	glUseProgram(*program);
	glBindVertexArray(VAO);		// Bind VAO

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glUniform1i(glGetUniformLocation(*program, "tex"), 0);

	GLuint modelLoc = glGetUniformLocation(*program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(objModelMatrix));

	GLuint projection = glGetUniformLocation(*program, "proj");
	glUniformMatrix4fv(projection, 1, GL_FALSE, value_ptr(camera->CameraProjection()));

	GLuint view = glGetUniformLocation(*program, "view");
	glUniformMatrix4fv(view, 1, GL_FALSE, value_ptr(camera->CameraView()));

	GLuint camPos = glGetUniformLocation(*program, "camPos");
	glUniform3fv(camPos, 1, value_ptr(camera->GetCamPos()));

	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void CTerrain::BuildVBIB()
{
	std::vector<TerrainVertex> vertices(numVertices);

	float halfWidth = (NumCols - 1) * CellSpacing * 0.5f;
	float halfDepth = (NumRows - 1) * CellSpacing * 0.5f;

	float du = 1.0f / (NumCols - 1);
	float dv = 1.0f / (NumRows - 1);
	for (UINT i = 0; i < NumRows; ++i)
	{
		float z = halfDepth - i * CellSpacing;
		for (UINT j = 0; j < NumCols; ++j)
		{
			float x = -halfWidth + j * CellSpacing;

			float y = heightmap[i * NumCols + j];
			vertices[i * NumCols + j].pos = glm::vec3(x, y, z);
			vertices[i * NumCols + j].normal = glm::vec3(0.0f, 1.0f, 0.0f);

			// Stretch texture over grid.
			vertices[i * NumCols + j].texC.x = j * du;
			vertices[i * NumCols + j].texC.y = i * dv;
		}
	}

	// Estimate normals for interior nodes using central difference.
	float invTwoDX = 1.0f / (2.0f * CellSpacing);
	float invTwoDZ = 1.0f / (2.0f * CellSpacing);
	for (int i = 2; i < NumRows - 1; ++i)
	{
		for (int j = 2; j < NumCols - 1; ++j)
		{
			float t = heightmap[(i - 1) * NumCols + j];
			float b = heightmap[(i + 1) * NumCols + j];
			float l = heightmap[i * NumCols + j - 1];
			float r = heightmap[i * NumCols + j + 1];

			glm::vec3 tanZ(0.0f, (t - b) * invTwoDZ, 1.0f);
			glm::vec3 tanX(1.0f, (r - l) * invTwoDX, 0.0f);

			glm::vec3 N;
			//D3DXVec3Cross(&N, &tanZ, &tanX);
			N = glm::cross(tanZ, tanX);
			N = glm::normalize(N); //D3DXVec3Normalize(&N, &N);
			

			vertices[i * NumCols + j].normal = N;
		}
	}

	std::vector<DWORD> indices(numFaces * 3); // 3 indices per face

	// Iterate over each quad and compute indices.
	int k = 0;
	for (UINT i = 0; i < NumRows - 1; ++i)
	{
		for (UINT j = 0; j < NumCols - 1; ++j)
		{
			indices[k] = i * NumCols + j;
			indices[k + 1] = i * NumCols + j + 1;
			indices[k + 2] = (i + 1) * NumCols + j;

			indices[k + 3] = (i + 1) * NumCols + j;
			indices[k + 4] = i * NumCols + j + 1;
			indices[k + 5] = (i + 1) * NumCols + j + 1;

			k += 6; // next quad
		}
	}

	GLuint EBO, VBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TerrainVertex), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, normal));
	glEnableVertexAttribArray(1);				    
												    
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, texC));
	glEnableVertexAttribArray(2);

	//indiceCount = sizeof(indices) / sizeof(GLuint);
	indiceCount = indices.size();
}

void CTerrain::Update()
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), glm::radians(objAngleRotation), objRotaion);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objScale * objScaleAmount);

	// Create model matrix to combine them
	objModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}