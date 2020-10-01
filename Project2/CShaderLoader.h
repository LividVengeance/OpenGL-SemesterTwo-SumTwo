#pragma once

// Dependency Includes
#include <glew.h>
#include <freeglut.h>

// Library Includes
#include <iostream>

class CShaderLoader
{

public:
	CShaderLoader(void);
	~CShaderLoader(void);
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename);
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename, 
		const char* GeometryShaderFilename);
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename,
		const char* TessControlShaderFilename, const char* TessEvalShaderFilename);
private:
	static GLuint CreateShader(GLenum shaderType, const char* shaderName);
	static std::string ReadShaderFile(const char* filename);
	static void PrintErrorDetails(bool isShader, GLuint id, const char* name);
};
