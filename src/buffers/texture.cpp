#include "deps.h"
#include "buffers/texture.h"
#include "stb/stb_image.h"

using namespace as;

Texture::Texture(Path path, unsigned int type) : BufferBase("Texture") {
	stbi_set_flip_vertically_on_load(1);
	this->bytes = stbi_load(path.Get().c_str(), &this->width, &this->height, &this->bits_per_pixel, 4);

	GLCall(glGenTextures(1, &this->ID));
	GLCall(glBindTexture(GL_TEXTURE_2D, this->ID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	this->ChangeTypeParameter(type);

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->bytes));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (this->bytes)
		stbi_image_free(this->bytes);
}


void Texture::Bind(unsigned int slot) {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, this->ID));
}

void Texture::Unbind() {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::ChangeTypeParameter(unsigned int type) {
	this->type = type;
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type));
}

void Texture::Delete() {
	GLCall(glDeleteTextures(1, &this->ID));
}
