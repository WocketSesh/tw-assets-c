#include "png_handle.h"
#include "../include/lodepng.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_name_extension(const char *path, char *name, char *extension) {

  const char *s = strrchr(path, '/');
  const char *bs = strrchr(path, '\\');
  const char *sep = bs > s ? bs : s;
  const char *base = sep ? sep + 1 : path;
  const char *dot = strrchr(path, '.');

  if (dot) {
    size_t name_len = dot - base;
    strncpy_s(name, 256, base, name_len);

    name[name_len] = '\0';

    strcpy_s(extension, 256, dot + 1);
  } else {
    strcpy_s(name, 256, base);
    extension[0] = '\0';
  }
}

struct ErrorValue load_png(const char *path, unsigned char **image) {
  printf("loading png\n");

  char *name = malloc(256);
  char *extension = malloc(256);

  get_name_extension(path, name, extension);

  if (strcmp(extension, "png") != 0) {
    return (struct ErrorValue){1, "File passed is not a png"};
  }

  printf("is png\n");

  unsigned width, height;
  unsigned error = lodepng_decode32_file(image, &width, &height, path);

  if (error)
    return (struct ErrorValue){1, lodepng_error_text(error)};

  if (width != EXPECTED_WIDTH || height != EXPECTED_HEIGHT)
    return (struct ErrorValue){1, "Unexpected image size"};

  return (struct ErrorValue){0};
}

// no safety because i got big balls and ye!
void write_pixels(unsigned char *src, unsigned char *dst, unsigned x,
                  unsigned y, unsigned height, unsigned width) {
  printf("riting pixels\n");
  for (int row = 0; row < height; row++) {
    int calc = 4 * ((y + row) * EXPECTED_WIDTH + x);
    memcpy(dst + calc, src + calc, width * 4);
  }
  printf("finished writing pixels\n");
}
