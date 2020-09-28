#include "CSkybox.h"

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <fmod.hpp>
#include <iostream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

CSkybox::CSkybox(GLint* _program, CCamera* _gameCamera)
{
	gameCamera = _gameCamera;
	program = _program;

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texID);

	std::string textures[]
	{
        "right.jpg", "left.jpg", "top.jpg", 
        "bottom.jpg", "back.jpg", "front.jpg",
	};

	int width, height;
	unsigned char* image;
	for (GLuint i = 0; i < 6; i++)
	{
		std::string fullPathName = "Resources/Textures/CubeMap/";
		fullPathName.append(textures[i]);
		image = SOIL_load_image(fullPathName.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, 
			width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    float size = 0.5f;
    GLfloat vertices[]
    {
        // Front
        -size,     size,    size,
        -size,    -size,    size,
         size,    -size,    size,
         size,     size,    size,

        // Back
        -size,     size,    -size,
        -size,    -size,    -size,
         size,    -size,    -size,
         size,     size,    -size,

        // Left
        -size,     size,    -size,
        -size,    -size,    -size,
        -size,    -size,     size,
        -size,     size,     size,

        // Right
         size,     size,     size,
         size,    -size,     size,
         size,    -size,    -size,
         size,     size,    -size,

        // Top
        -size,     size,    -size,
        -size,     size,     size,
         size,     size,     size,
         size,     size,    -size,

        // Bottom
        -size,    -size,     size,
        -size,    -size,    -size,
         size,    -size,    -size,
         size,    -size,     size,
    };

    GLuint indices[] =
    {
        0,  2,  1,
        0,  3,  2,

        7,  5,  6,
        7,  4,  5,

        8,  10, 9,
        8,  11, 10,

        12, 14, 13,
        12, 15, 14,

        16, 18, 17,
        16, 19, 18,

        20, 22, 21,
        20, 23, 22,
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Makes the points Point things
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
}

CSkybox::~CSkybox()
{
}

void CSkybox::Render()
{
	glUseProgram(*program);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);
	glUniform1i(glGetUniformLocation(*program, "cubeSampler"), 0);
	glUniformMatrix4fv(glGetUniformLocation(*program, "MVP"), 1, GL_FALSE, value_ptr(MVP));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void CSkybox::Update()
{
	mat4 model = scale(mat4(), vec3(200.0f, 200.0f, 200.0f));
	MVP = gameCamera->CameraProjection() * gameCamera->CameraView() * model;
}

GLuint CSkybox::GetTextureID()
{
    return(texID);
}