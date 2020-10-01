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

CTerrain::CTerrain(CCamera* _camera)
{
	camera = _camera;
}

CTerrain::~CTerrain()
{
}

float CTerrain::Width() const
{
	return((initInfo.NumRows -1) * initInfo.CellSpacing);
}

float CTerrain::Depth() const
{
	return((initInfo.NumCols - 1) * initInfo.CellSpacing);
}

float CTerrain::GetHeight(float x, float z) const
{
	// Transform from terrain local space to "cell" space.
	float c = (x + 0.5f * Width()) / initInfo.CellSpacing;
	float d = (z - 0.5f * Depth()) / -initInfo.CellSpacing;

	// Get the row and column we are in.
	int row = (int)floorf(d);
	int col = (int)floorf(c);

	// Grab the heights of the cell we are in.
	// A*--*B
	//  | /|
	//  |/ |
	// C*--*D
	float A = heightmap[row * initInfo.NumCols + col];
	float B = heightmap[row * initInfo.NumCols + col + 1];
	float C = heightmap[(row + 1) * initInfo.NumCols + col];
	float D = heightmap[(row + 1) * initInfo.NumCols + col + 1];

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

void CTerrain::Init(const InitInfo& _initInfo)
{
	
}

void CTerrain::SetDirectionToSun(const glm::vec3& v)
{
	glm::vec4 temp(v.x, v.y, v.z, 0.0f);
	//mfxDirToSunVar->SetFloatVector((float*)temp);
}

void CTerrain::LoadHeightMap()
{
	// A height for each vertex
	std::vector<unsigned char> in(initInfo.NumRows * initInfo.NumCols);

	// Open the file.
	std::ifstream inFile;
	inFile.open(initInfo.HeightmapFilename.c_str(), std::ios_base::binary);

	if (inFile)
	{
		// Read the RAW bytes.
		inFile.read((char*)&in[0], (std::streamsize)in.size());

		// Done with file.
		inFile.close();
	}

	// Copy the array data into a float array, and scale and offset the heights.
	heightmap.resize(initInfo.NumRows * initInfo.NumCols, 0);
	for (int i = 0; i < initInfo.NumRows * initInfo.NumCols; ++i)
	{
		heightmap[i] = (float)in[i] * initInfo.HeightScale + initInfo.HeightOffset;
	}
}

bool CTerrain::IsInBounds(int i, int j)
{
	// True if ij are valid indices; false otherwise.
	return
		i >= 0 && i < initInfo.NumRows &&
		j >= 0 && j < initInfo.NumCols;
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

	for (int m = i - 1; m <= i + 1; ++m)
	{
		for (int n = j - 1; n <= j + 1; ++n)
		{
			if (IsInBounds(m, n))
			{
				avg += heightmap[m * initInfo.NumCols + n];
				num += 1.0f;
			}
		}
	}

	return (avg / num);
}

void CTerrain::Smooth()
{
	std::vector<float> dest(heightmap.size());

	for (int i = 0; i < initInfo.NumRows; ++i)
	{
		for (int j = 0; j < initInfo.NumCols; ++j)
		{
			dest[i * initInfo.NumCols + j] = Average(i, j);
		}
	}

	// Replace the old heightmap with the filtered one.
	heightmap = dest;
}

void CTerrain::Draw()
{
	//md3dDevice->IASetInputLayout(InputLayout::PosNormalTex);
	//
	//int stride = sizeof(TerrainVertex);
	//int offset = 0;
	//md3dDevice->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	//md3dDevice->IASetIndexBuffer(mIB, DXGI_FORMAT_R32_UINT, 0);
	//
	//glm::mat4 view = camera->CameraView();//GetCamera().view();
	//glm::mat4 proj = camera->CameraProjection();//GetCamera().proj();
	//
	////D3DXMATRIX WVP = world * view * proj;
	//glm::mat4 MVP = view * proj;
	//
	//
	//mfxWVPVar->SetMatrix((float*)&WVP);
	//mfxWorldVar->SetMatrix((float*)&world);
	//
	//mfxLayer0Var->SetResource(mLayer0);
	//mfxLayer1Var->SetResource(mLayer1);
	//mfxLayer2Var->SetResource(mLayer2);
	//mfxLayer3Var->SetResource(mLayer3);
	//mfxLayer4Var->SetResource(mLayer4);
	//mfxBlendMapVar->SetResource(mBlendMap);
	//
	//D3D10_TECHNIQUE_DESC techDesc;
	//mTech->GetDesc(&techDesc);
	//
	//for (UINT i = 0; i < techDesc.Passes; ++i)
	//{
	//	ID3D10EffectPass* pass = mTech->GetPassByIndex(i);
	//	pass->Apply(0);
	//
	//	md3dDevice->DrawIndexed(numFaces * 3, 0, 0);
	//}
}

void CTerrain::BuildVBIB()
{
	std::vector<TerrainVertex> vertices(numVertices);
	//float vertices[numVertices];

	float halfWidth = (initInfo.NumCols - 1) * initInfo.CellSpacing * 0.5f;
	float halfDepth = (initInfo.NumRows - 1) * initInfo.CellSpacing * 0.5f;

	float du = 1.0f / (initInfo.NumCols - 1);
	float dv = 1.0f / (initInfo.NumRows - 1);
	for (int i = 0; i < initInfo.NumRows; ++i)
	{
		float z = halfDepth - i * initInfo.CellSpacing;
		for (int j = 0; j < initInfo.NumCols; ++j)
		{
			float x = -halfWidth + j * initInfo.CellSpacing;

			float y = heightmap[i * initInfo.NumCols + j];
			vertices[i * initInfo.NumCols + j].pos = glm::vec3(x, y, z);
			vertices[i * initInfo.NumCols + j].normal = glm::vec3(0.0f, 1.0f, 0.0f);

			// Stretch texture over grid.
			vertices[i * initInfo.NumCols + j].texC.x = j * du;
			vertices[i * initInfo.NumCols + j].texC.y = i * dv;
		}
	}

	// Estimate normals for interior nodes using central difference.
	float invTwoDX = 1.0f / (2.0f * initInfo.CellSpacing);
	float invTwoDZ = 1.0f / (2.0f * initInfo.CellSpacing);
	for (int i = 2; i < initInfo.NumRows - 1; ++i)
	{
		for (int j = 2; j < initInfo.NumCols - 1; ++j)
		{
			float t = heightmap[(i - 1) * initInfo.NumCols + j];
			float b = heightmap[(i + 1) * initInfo.NumCols + j];
			float l = heightmap[i * initInfo.NumCols + j - 1];
			float r = heightmap[i * initInfo.NumCols + j + 1];

			glm::vec3 tanZ(0.0f, (t - b) * invTwoDZ, 1.0f);
			glm::vec3 tanX(1.0f, (r - l) * invTwoDX, 0.0f);

			glm::vec3 N;
			//D3DXVec3Cross(&N, &tanZ, &tanX);
			N = glm::cross(tanZ, tanX);
			glm::normalize(&N); //D3DXVec3Normalize(&N, &N);
			

			vertices[i * initInfo.NumCols + j].normal = N;
		}
	}

	std::vector<GLuint> indices(numFaces * 3); // 3 indices per face

	// Iterate over each quad and compute indices.
	int k = 0;
	for (int i = 0; i < initInfo.NumRows - 1; ++i)
	{
		for (int j = 0; j < initInfo.NumCols - 1; ++j)
		{
			indices[k] = i * initInfo.NumCols + j;
			indices[k + 1] = i * initInfo.NumCols + j + 1;
			indices[k + 2] = (i + 1) * initInfo.NumCols + j;

			indices[k + 3] = (i + 1) * initInfo.NumCols + j;
			indices[k + 4] = i * initInfo.NumCols + j + 1;
			indices[k + 5] = (i + 1) * initInfo.NumCols + j + 1;

			k += 6; // next quad
		}
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),	// Stride of the single vertex (pos + color)
		(GLvoid*)0);			// Offset from beginning of Vertex
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),				// Stride of the single vertex (pos + color)
		(GLvoid*)(3 * sizeof(GLfloat)));	// Offset from beginning of Vertex
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}