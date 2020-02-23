#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	float aspectRatio;
	glm::vec3 position;
	bool changedP, changedV;
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 pv;

public:
	Camera(float aspectRatio, glm::vec3 position)
		: aspectRatio(aspectRatio), position(position), changedP(true), changedV(true)
	{
		this->getPV();
	}

	glm::mat4 getProjection()
	{
		if (changedP)
		{
			projection = glm::ortho(-aspectRatio, aspectRatio, -1.0f, 1.0f, 0.1f, 100.0f);
			changedP = false;
		}
		return projection;
	}

	glm::mat4 getView()
	{
		if (changedV)
		{
			view = glm::translate(glm::mat4(1.0f), -position);
			changedV = false;
		}
		return view;
	}

	glm::mat4 getPV()
	{
		if (changedP || changedV)
			pv = getProjection() * getView();
		return pv;
	}

	void move(glm::vec3 vel)
	{
		this->position += vel;
		changedV = true;
	}

	void setAspectRatio(float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
		changedP = true;
	}

	void setPosition(glm::vec3 position)
	{
		this->position = position;
		changedV = true;
	}
	void setPosition(float v0, float v1, float v2)
	{
		this->position = glm::vec3(v0, v1, v2);
		changedV = true;
	}

	glm::vec3 getPosition()
	{
		return this->position;
	}
};

