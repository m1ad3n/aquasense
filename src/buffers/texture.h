#ifndef AQUASENSE_TEXTURE
#define AQUASENSE_TEXTURE

#include "buffer.h"
#include "../string_functions.h"

class Texture : public BufferBase {
public:
	unsigned int ID;

	Texture(Path path, unsigned int type);
	~Texture() override;

	void Bind(unsigned int slot);
	void Bind() override { this->Bind(0); }

	void Unbind() override;
	void Delete() override;
	void ChangeTypeParameter(unsigned int type);

	int GetWidth() const { return this->width; }
	int GetHeight() const { return this->height; }

private:
	unsigned int type;
	int
		height,
		bits_per_pixel,
		width;

	unsigned char* bytes;
};

#endif // AQUASENSE_TEXTURE