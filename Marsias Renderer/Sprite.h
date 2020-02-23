#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

class Sprite
{
public:
	Sprite();
	Sprite(float x, float y, unsigned int textureID);
	Sprite(float x, float y, Texture texture);

	void render(Shader* shader);
	
	void setPosition(float x, float y);
	void setScale(float xScale, float yScale);
	void setRotation(float angle);
	void setTexture(unsigned int textureID) { this->textureID = textureID; }

	inline glm::vec3 getPosition() { return this->pos; }
	inline glm::vec3 getScale() { return this->scale; }
	inline float getRotation() { return this->rotation; }
	inline unsigned int getTextureID() { return this->textureID; }

	void move(glm::vec3 vel);
	void rotate(float angle);
private:
	glm::vec3 pos;
	glm::vec3 scale;
	float rotation;
	unsigned int textureID;
	glm::mat4 model;

	unsigned int VAO;

	void calculateModelMatrix();
	void prepareSprite();
};

