#pragma once

#include <cstdint>
#include "Formatter.h"

class Image {
public:
	Image(const char *file, int comp = 3);
	~Image();

	uint8_t *getData() const;
	int getWidth() const;
	int getHeight() const;

	uint8_t operator[](int index);


private:
	uint8_t *data;
	int width, height;
};


