#include "../deps.h"
#include "texture.h"
#include "../stb/stb_image.h"

struct sTexture* sTexture_new(char* path, unsigned int _type) {
	struct sTexture* tmp = (struct sTexture*)malloc(sizeof(struct sTexture));
	
	stbi_set_flip_vertically_on_load(1);
	tmp->bytes = stbi_load(path, &tmp->width, &tmp->height, &tmp->bits_per_pixel, 4);

	GLCall(glGenTextures(1, &tmp->id));
	GLCall(glBindTexture(GL_TEXTURE_2D, tmp->id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _type));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _type));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tmp->width, tmp->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tmp->bytes));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (tmp->bytes)
		stbi_image_free(tmp->bytes);

	return tmp;
}

int sTexture_getWidth(struct sTexture* texture) {
	return (texture == NULL) ? 0 : texture->width;
}

int sTexture_getHeight(struct sTexture* texture) {
	return (texture == NULL) ? 0 : texture->height;
}

void sTexture_bind(struct sTexture* texture, unsigned int slot) {
	// GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, texture->id));
}

void sTexture_delete(struct sTexture* texture) {
	GLCall(glDeleteTextures(1, &texture->id));
	free(texture);
}