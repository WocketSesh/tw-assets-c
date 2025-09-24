#include "png_handle.h"
#include "../include/lodepng.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_name_extension(const char *path, char *name, char *extension) {
  if (name == NULL && extension == NULL)
    return;

  const char *s = strrchr(path, '/');
  const char *bs = strrchr(path, '\\');
  const char *sep = bs > s ? bs : s;
  const char *base = sep ? sep + 1 : path;
  const char *dot = strrchr(path, '.');

  if (dot) {
    size_t name_len = dot - base;
    if (name != NULL)
      strncpy_s(name, 256, base, name_len);

    printf("set name?\n");
    name[name_len] = '\0';

    if (extension != NULL)
      strcpy_s(extension, 256, dot + 1);
  } else {
    if (name != NULL)
      strcpy_s(name, 256, base);
    if (extension != NULL)
      extension[0] = '\0';
  }
}

ErrorValue load_png(const char *path, unsigned char **image) {

  char *name = malloc(256);
  char *extension = malloc(256);

  get_name_extension(path, name, extension);

  if (strcmp(extension, "png") != 0) {
    return (struct ErrorValue){1, "File passed is not a png"};
  }

  unsigned width, height;
  unsigned error = lodepng_decode32_file(image, &width, &height, path);
  printf("decoded\n");
  if (error)
    return (struct ErrorValue){1, lodepng_error_text(error)};

  if (width != EXPECTED_WIDTH || height != EXPECTED_HEIGHT)
    return (struct ErrorValue){1, "Unexpected image size"};

  return (struct ErrorValue){0};
}

// no safety because i got big balls and ye!
void write_pixels(unsigned char *src, unsigned char *dst, unsigned x,
                  unsigned y, unsigned height, unsigned width) {
  for (int row = 0; row < height; row++) {
    int calc = 4 * ((y + row) * EXPECTED_WIDTH + x);
    memcpy(dst + calc, src + calc, width * 4);
  }
}

// src_width could instead just used EXPECTED_WIDTH?
unsigned char *slice_pixels(unsigned char *src, unsigned x, unsigned y,
                            unsigned src_width, unsigned slice_width,
                            unsigned slice_height) {
  unsigned char *slice =
      (unsigned char *)malloc(slice_width * slice_height * 4);

  if (!slice) {
    printf("Failed to allocate memory for slice_pixels\n");
    return NULL;
  }

  for (int row = 0; row < slice_height; row++) {
    unsigned s_offset = 4 * ((y + row) * src_width + x);
    unsigned d_offset = 4 * (row * slice_width);
    memcpy(slice + d_offset, src + s_offset, slice_width * 4);
  }

  return slice;
}
