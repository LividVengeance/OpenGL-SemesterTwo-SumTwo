#include "CObject.h"

CObject::CObject(GLint* _program, GLuint* _VAO, int _indiceCount, CCamera* _gameCamera, GLuint* _texture)
{
	program = _program;
	VAO = _VAO;
	indiceCount = _indiceCount;
	gameCamera = _gameCamera;
	texture = _texture;

	objPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	objRotaion = glm::vec3(0.0f, 0.0f, 1.0f);
	objScale = glm::vec3(1.0f, 1.0f, 1.0f);

	objScaleAmount = 1.0f;
	objAngleRotation = 0.0f;

	Update();
}

CObject::~CObject()
{
}

void CObject::Update()
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), glm::radians(objAngleRotation), objRotaion);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objScale * objScaleAmount);

	// Create model matrix to combine them
	objModelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void CObject::Render()
{
	glUseProgram(*program);
	glBindVertexArray(*VAO);		// Bind VAO

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glUniform1i(glGetUniformLocation(*program, "tex"), 0);

	GLuint modelLoc = glGetUniformLocation(*program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(objModelMatrix));

	GLuint projection = glGetUniformLocation(*program, "proj");
	glUniformMatrix4fv(projection, 1, GL_FALSE, value_ptr(gameCamera->CameraProjection()));

	GLuint view = glGetUniformLocation(*program, "view");
	glUniformMatrix4fv(view, 1, GL_FALSE, value_ptr(gameCamera->CameraView()));

	GLuint camPos = glGetUniformLocation(*program, "camPos");
	glUniform3fv(camPos, 1, value_ptr(gameCamera->GetCamPos()));

	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0); // Drawing Background
	glBindVertexArray(0);
	glUseProgram(0);
}

void CObject::Render2D()
{
	glUseProgram(*program);

	glBindVertexArray(*VAO);		// Bind VAO

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glUniform1i(glGetUniformLocation(*program, "tex"), 0);

	GLuint modelLoc = glGetUniformLocation(*program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(objModelMatrix));

	GLuint projection = glGetUniformLocation(*program, "proj");
	glUniformMatrix4fv(projection, 1, GL_FALSE, value_ptr(gameCamera->CameraProjection2D()));

	GLuint view = glGetUniformLocation(*program, "view");
	glUniformMatrix4fv(view, 1, GL_FALSE, value_ptr(gameCamera->CameraView2D()));

	GLuint camPos = glGetUniformLocation(*program, "camPos");
	glUniform3fv(camPos, 1, value_ptr(gameCamera->GetCamPos()));

	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0); // Drawing Background
	glBindVertexArray(0);
	glUseProgram(0);
}

void CObject::RenderReflection(CSkybox* skyboxObj)
{
	glUseProgram(*program);
	glBindVertexArray(*VAO);		// Bind VAO

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(*program, "skybox"), 1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxObj->GetTextureID());

	GLuint modelLoc = glGetUniformLocation(*program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(objModelMatrix));

	GLuint projection = glGetUniformLocation(*program, "proj");
	glUniformMatrix4fv(projection, 1, GL_FALSE, value_ptr(gameCamera->CameraProjection()));

	GLuint view = glGetUniformLocation(*program, "view");
	glUniformMatrix4fv(view, 1, GL_FALSE, value_ptr(gameCamera->CameraView()));

	GLuint camPos = glGetUniformLocation(*program, "camPos");
	glUniform3fv(camPos, 1, value_ptr(gameCamera->GetCamPos()));

	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, 0); // Drawing Background
	glBindVertexArray(0);
	glUseProgram(0);
}