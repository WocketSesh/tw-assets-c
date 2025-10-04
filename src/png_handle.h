#ifndef PNGHANDLE_H
#define PNGHANDLE_H
#include "helpers.h"
#define EXPECTED_HEIGHT 512
#define EXPECTED_WIDTH 1024

void write_pixels(unsigned char *src, unsigned char *dst, unsigned x,
                  unsigned y, unsigned height, unsigned width);
void get_name_extension(const char *path, char *name, char *extension);
ErrorValue load_png(const char *path, unsigned char **pixels, char *name,
                    unsigned *width, unsigned *height);
unsigned char *slice_pixels(unsigned char *src, unsigned x, unsigned y,
                            unsigned src_width, unsigned slice_width,
                            unsigned slice_height);

#endif
