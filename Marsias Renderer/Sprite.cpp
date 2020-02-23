#include "Sprite.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

class RectVertexObject
{
private:
	unsigned int VAO, VBO, EBO;

	RectVertexObject(const RectVertexObject&) = delete;

	RectVertexObject()
	{
		float vertices[] = {
		-1.0f, -1.0f,  0.0f,	0.0f, 0.0f,
		 1.0f, -1.0f,  0.0f,	1.0f, 0.0f,
		 1.0f,  1.0f,  0.0f,	1.0f, 1.0f,
		-1.0f,  1.0f,  0.0f,	0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

public:
	static RectVertexObject& Get()
	{
		static RectVertexObject instance;
		return instance;
	}

	static unsigned int GetVAO() { return Get().VAO; }
	static unsigned int GetVBO() { return Get().VBO; }
	static unsigned int GetEBO() { return Get().EBO; }
};

Sprite::Sprite()
	: pos(glm::vec3(0, 0, 0)), scale(1.0f), rotation(0.0f), textureID(0)
{
	this->prepareSprite();
}

Sprite::Sprite(float x, float y, unsigned int textureID)
	: pos(glm::vec3(x, y, 0)), scale(1.0f), rotation(0.0f), textureID(textureID)
{
	this->prepareSprite();
}

Sprite::Sprite(float x, float y, Texture texture)
	: pos(glm::vec3(x, y, 0)), scale(1.0f), rotation(0.0f), textureID(texture.getTextureID())
{
	this->prepareSprite();
}

void Sprite::render(Shader* shader)
{
	// Optimize by removing view and projection
	shader->setMat4f("u_model", this->model);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textureID);

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Sprite::setPosition(float x, float y)
{
	this->pos = glm::vec3(x, y, 0);
	calculateModelMatrix();
}

void Sprite::setScale(float xScale, float yScale)
{
	this->scale = glm::vec3(xScale, yScale, 1);
	calculateModelMatrix();
}

void Sprite::setRotation(float angle)
{
	this->rotation = glm::radians(angle);
	calculateModelMatrix();
}

void Sprite::move(glm::vec3 vel)
{
	this->pos += vel;
	calculateModelMatrix();
}

void Sprite::rotate(float angle)
{
	this->rotation += glm::radians(angle);
	calculateModelMatrix();
}

void Sprite::calculateModelMatrix()
{
	this->model = glm::translate(glm::mat4(1.0f), this->pos);
	this->model = glm::scale(this->model, this->scale);
	this->model = glm::rotate(this->model, this->rotation, glm::vec3(0, 0, 1));
}

void Sprite::prepareSprite()
{
	this->VAO = RectVertexObject::GetVAO();

	calculateModelMatrix();
}
