#include "Texture.h"
#include <glad/glad.h>
#include <stb_image.h>
#include "Log.h"

Texture::Texture(const char* path)
{
	this->loadFromFile(path);
}

void Texture::loadFromFile(const char* path)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	int width, height, n_channel;
	unsigned char* data = stbi_load(path, &width, &height, &n_channel, 0);

	if (data)
	{
		GLenum format = GL_RGB;
		if (n_channel == 1)
			format = GL_RED;
		else if (n_channel == 3)
			format = GL_RGB;
		else if (n_channel == 4)
			format = GL_RGBA;

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("Failed to load texture " << path);
	}
	stbi_image_free(data);
}
