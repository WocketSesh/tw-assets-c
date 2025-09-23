#ifndef PNGHANDLE_H
#define PNGHANDLE_H
#include "helpers.h"
#define EXPECTED_HEIGHT 512
#define EXPECTED_WIDTH 1024

void write_pixels(unsigned char *src, unsigned char *dst, unsigned x,
                  unsigned y, unsigned height, unsigned width);
void get_name_extension(const char *path, char *name, char *extension);
struct ErrorValue load_png(const char *path, unsigned char **pixels);

#endif
