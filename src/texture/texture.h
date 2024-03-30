#ifndef AQUASENSE_TEXTURE
#define AQUASENSE_TEXTURE

typedef struct sTexture ASTexture;

struct sTexture {
	unsigned int id;

	int width;
	int height;
	int bits_per_pixel;

	unsigned char* bytes;
	char* path;
};

struct sTexture* sTexture_new(char* path, unsigned int _type);

int sTexture_getWidth(struct sTexture* texture);
int sTexture_getHeight(struct sTexture* texture);

void sTexture_bind(struct sTexture* texture, unsigned int slot);
void sTexture_delete(struct sTexture* texture);

#endif