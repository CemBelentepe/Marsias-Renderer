#pragma once
class Texture
{
private:
	unsigned int textureID;
public:
	Texture() :textureID(0) {}
	Texture(const char* path);

	void loadFromFile(const char* path);

	const unsigned int getTextureID() { return this->textureID; }
};

