#pragma once

// Dependenicy Includes
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

//Libary Includes
#include <map>
#include <string>
#include <iostream>

#include "Utilities.h"
#include "CShaderLoader.h"

struct FontChar
{
	GLuint		TextureID;
	glm::ivec2	Size;
	glm::ivec2	Bearing;
	GLuint		Advance;
};

class CTextLabel
{
public:
	CTextLabel(
		std::string text,
		std::string font,
		glm::vec2 pos,
		glm::vec3 colour = glm::vec3(1.0f, 1.0f, 1.0f),
		float scale = 1.0f);

	~CTextLabel();

	void Render();
	void SetText(std::string newText) { text = newText; };
	void SetColour(glm::vec3 newColour) { colour = newColour; };
	void SetScale(GLfloat newScale) { scale = newScale; };
	void SetPosition(glm::vec2 newPosition) { position = newPosition; };
private:
	GLuint GenerateTexture(FT_Face face);

	std::string	text;
	GLfloat		scale;
	glm::vec3	colour;
	glm::vec2	position;

	GLuint VAO, VBO, program;
	glm::mat4 proj;
	std::map<GLchar, FontChar> Characters;
};

