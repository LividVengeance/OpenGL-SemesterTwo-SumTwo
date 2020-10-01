#include "CShaderLoader.h" 

#include<iostream>
#include<fstream>
#include<vector>

CShaderLoader::CShaderLoader(void) {}
CShaderLoader::~CShaderLoader(void) {}

GLuint CShaderLoader::CreateProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
	GLuint program = glCreateProgram();

	GLint vertID = CreateShader(GL_VERTEX_SHADER, vertexShaderFilename);
	GLint fragID = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);

	glAttachShader(program, vertID);
	glAttachShader(program, fragID);

	glLinkProgram(program);

	// Check for link errors
	int link_result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		std::string programName = vertexShaderFilename + *fragmentShaderFilename;
		PrintErrorDetails(false, program, programName.c_str());
		return 0;
	}
	return program;
}

GLuint CShaderLoader::CreateProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename, 
	const char* geometryShaderFilename)
{
	GLuint program = glCreateProgram();

	GLint vertID = CreateShader(GL_VERTEX_SHADER, vertexShaderFilename);
	GLint fragID = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);

	//std::string geometry_shader_code = glm::ReadShader(geometryShaderFilename);
	//GLuint geomID = CreateShader(GL_GEOMETRY_SHADER, geometry_shader_code, "geometry shader");

	GLuint geomID = CreateShader(GL_GEOMETRY_SHADER, geometryShaderFilename);

	

	glAttachShader(program, vertID);
	glAttachShader(program, fragID);
	glAttachShader(program, geomID);

	glLinkProgram(program);

	// Check for link errors
	int link_result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);
	if (link_result == GL_FALSE)
	{
		std::string programName = vertexShaderFilename + *fragmentShaderFilename;
		PrintErrorDetails(false, program, programName.c_str());
		return 0;
	}
	return program;
}

GLuint CShaderLoader::CreateShader(GLenum shaderType, const char* shaderName)
{

	GLint shaderID = glCreateShader(shaderType);

	std::string shaderString = ReadShaderFile(shaderName);

	const char* CharPointer = shaderString.c_str();

	const GLint lengthOfString = shaderString.size();

	glShaderSource(shaderID, 1, &CharPointer, &lengthOfString);
	glCompileShader(shaderID);

	// Check for errors
	int compile_result = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_result);
	if (compile_result == GL_FALSE)
	{
		PrintErrorDetails(true, shaderID, shaderName);
		return 0;
	}
	return shaderID;
}

GLuint CShaderLoader::CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename,
	const char* TessControlShaderFilename, const char* TessEvalShaderFilename)
{
	//std::string tessControl_shader_code = ReadShader(TessControlShaderFilename);
	//std::string tessEval_shader_code = ReadShader(TessEvalShaderFilename);
	//GLuint tessControl_shader = CreateShader(GL_TESS_CONTROL_SHADER, tessControl_shader_code, "tess
	//	Control shader");
	//	GLuint tessEval_shader = CreateShader(GL_TESS_EVALUATION_SHADER, tessEval_shader_code, "tess
	//		Evalution shader");
	//		glAttachShader(program, tessControl_shader);
	//glAttachShader(program, tessEval_shader);
	GLuint program = glCreateProgram();

	GLint vertID = CreateShader(GL_VERTEX_SHADER, VertexShaderFilename);
	GLint fragID = CreateShader(GL_FRAGMENT_SHADER, FragmentShaderFilename);
	GLuint tessControl_shader = CreateShader(GL_TESS_CONTROL_SHADER, TessControlShaderFilename);
	GLuint tessEval_shader = CreateShader(GL_TESS_EVALUATION_SHADER, TessEvalShaderFilename);

	glAttachShader(program, vertID);
	glAttachShader(program, fragID);
	glAttachShader(program, tessControl_shader);
	glAttachShader(program, tessEval_shader);

	return(program);
}

std::string CShaderLoader::ReadShaderFile(const char* filename)
{
	// Open the file for reading
	std::ifstream file(filename, std::ios::in);
	std::string shaderCode;

	// Ensure the file is open and readable
	if (!file.good()) {
		std::cout << "Cannot read file:  " << filename << std::endl;
		return "";
	}

	// Determine the size of of the file in characters and resize the string variable to accomodate
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());

	// Set the position of the next character to be read back to the beginning
	file.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

void CShaderLoader::PrintErrorDetails(bool isShader, GLuint id, const char* name)
{
	int infoLogLength = 0;
	// Retrieve the length of characters needed to contain the info log
	(isShader == true) ? glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength) : glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> log(infoLogLength);

	// Retrieve the log info and populate log variable
	(isShader == true) ? glGetShaderInfoLog(id, infoLogLength, NULL, &log[0]) : glGetProgramInfoLog(id, infoLogLength, NULL, &log[0]);
	std::cout << "Error compiling " << ((isShader == true) ? "shader" : "program") << ": " << name << std::endl;
	std::cout << &log[0] << std::endl;
}