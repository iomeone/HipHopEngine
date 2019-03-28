#ifndef INC_TEXTURE2D_H_
#define INC_TEXTURE2D_H_

#include<string>
#include<glm/glm.hpp>
#include<glad/glad.h>
#include "IAsset.h"


class Texture2D : public IAsset
{
public:
	Texture2D();
	Texture2D(const std::string& assetName);
	GLuint CreateTexture(const std::string& path, bool repeat = false);
	~Texture2D();
	void BindToUnit(GLenum textureUnit)const;
	void Unbind()const;

	inline GLuint GetID() const { return mID;}
	inline glm::vec2 GetSize() const { return mSize;}
	inline GLenum GetFormat() const { return mFormat;}
	inline unsigned char* GetBits() const { return mImage;}

protected:

	GLuint mID;
	glm::vec2 mSize;
	GLenum mFormat;
	unsigned char* mImage;

};

#endif