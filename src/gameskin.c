#include "helpers.h"
#include "lodepng.h"
#include "png_handle.h"
#include "tw_assets.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ErrorValue gameskin_array_init(BaseArray **base) {
  return array_init(base, sizeof(GameSkin));
}

ErrorValue gameskin_copy_part_from(GameSkin *src, GameSkin *dst,
                                   GameSkinPartID part) {
  if (src == NULL || dst == NULL || src->pixels == NULL ||
      dst->pixels == NULL) {
    return (struct ErrorValue){1, "Either src or dst is NULL"};
  }

  if (src->height != dst->height) {
    return (struct ErrorValue){1, "Source and Destination height do not match"};
  }

  GameSkinPartPosition pos = gameskin_get_part_position(part);

  write_pixels(src->pixels, dst->pixels, pos.x, pos.y, pos.height, pos.width);

  return (ErrorValue){0};
}

ErrorValue gameskin_save(GameSkin *gameskin) {
  unsigned err = lodepng_encode32_file(gameskin->path, gameskin->pixels,
                                       gameskin->width, gameskin->height);

  if (!err)
    return (ErrorValue){0};

  return (ErrorValue){1, lodepng_error_text(err)};
}

unsigned char *gameskin_get_part_pixels(GameSkin *gameskin, GameSkinPartID part,
                                        unsigned *height, unsigned *width,
                                        ErrorValue *err) {
  if (gameskin == NULL) {
    create_error(err, "Gameskin is NULL");
    return NULL;
  }

  GameSkinPartPosition pos = gameskin_get_part_position(part);

  if (height != NULL)
    *height = pos.height;

  if (width != NULL)
    *width = pos.width;

  if (pos.height == 0) {
    create_error(err, "Invalid GameSkinPartID Provided");
    return NULL;
  }

  return slice_pixels(gameskin->pixels, pos.x, pos.y, EXPECTED_WIDTH, pos.width,
                      pos.height);
}

int gameskin_array_length(BaseArray *base) { return array_length(base); }

ErrorValue gameskin_free(GameSkin *gs) {
  if (gs == NULL)
    return (ErrorValue){1, "Gameskin is NULL"};
  if (gs->name != NULL)
    free(gs->name);
  if (gs->path != NULL)
    free(gs->path);
  if (gs->pixels != NULL)
    free(gs->pixels);
  free(gs);

  return (ErrorValue){0};
}

ErrorValue gameskin_save_part(GameSkin *gameskin, GameSkinPartID part,
                              const char *path) {
  struct ErrorValue err = {0};
  unsigned h, w;
  unsigned char *pixels =
      gameskin_get_part_pixels(gameskin, part, &h, &w, &err);

  if (err.did_error) {
    return err;
  }

  int error = lodepng_encode32_file(path, pixels, w, h);

  if (error) {
    create_error(&err, lodepng_error_text(error));
    return err;
  }

  return (ErrorValue){0};
}

// Load a gameskin from the spicified path
ErrorValue gameskin_from_path(const char *path, GameSkin *gameskin) {
  char *name = malloc(256);

  if (name == NULL) {
    return (ErrorValue){1, "Error allocating for name"};
  }

  load_png(path, &gameskin->pixels, name, &gameskin->height, &gameskin->width);

  ErrorValue str_err;
  gameskin->name = string_init(name, &str_err);
  free(name);

  if (str_err.did_error) {
    // no cleanup or return and just balls to the walls
    printf("Error: %s\n", str_err.error_message);
  }

  // Should always be NULL?, but just incase
  if (gameskin->path != NULL) {
    free(gameskin->path);
  }
  // Should probably do some error handling here?
  ErrorValue err;
  gameskin->path = string_init(path, &err);

  return err;
}

// TODO: make safey
ErrorValue gameskin_init(GameSkin **gs) {
  *gs = malloc(sizeof(struct GameSkin));

  // allocate for name here so we can pass it to get_name_extension, could cause
  // issues but fuck it big balls
  // Now allocate for name instead when using get_name_extension ?
  // (*gs)->name = malloc(256);
  return (ErrorValue){0};
}

ErrorValue gameskin_array_push(BaseArray *base, GameSkin *gameskin) {
  if (base == NULL || gameskin == NULL)
    return (ErrorValue){1, "Either BaseArray or GameSkin is NULL"};

  if (gameskin_array_indexof(base, gameskin->name) != -1)
    return (ErrorValue){1, "Gameskin already exists with name"};

  return array_push(base, gameskin);
}

ErrorValue gameskin_array_remove(BaseArray *base, int index, int free_memory) {
  if (free_memory)
    gameskin_free(gameskin_array_get(base, index, NULL));

  return array_remove(base, index, 0);
}

ErrorValue gameskin_array_clear(BaseArray *arr, int free_memory) {
  while (arr->length > 0) {
    gameskin_array_remove(arr, 0, free_memory);
  }

  return (ErrorValue){0};
}

ErrorValue gameskin_array_push_all(BaseArray *base, GameSkin **gameskin,
                                   int count) {
  if (gameskin == NULL)
    return (ErrorValue){1, "Gameskin array is NULL"};

  for (int i = 0; i < count; i++) {
    if (gameskin[i] == NULL)
      return (ErrorValue){1, "Gameskin is NULL"};

    ErrorValue ev = gameskin_array_push(base, gameskin[i]);
    if (ev.did_error)
      return ev;
  }

  return (ErrorValue){0};
}

int gameskin_array_indexof(BaseArray *base, const char *name) {
  for (int i = 0; i < base->length; i++) {
    void *rv = array_get(base, i, NULL);
    if (rv == NULL)
      continue;

    if (strcmp(((GameSkin *)(rv))->name, name) == 0)
      return i;
  }
  return -1;
}

GameSkin *gameskin_array_find(BaseArray *base, const char *name,
                              ErrorValue *err) {
  int index = gameskin_array_indexof(base, name);
  return index == -1 ? NULL : gameskin_array_get(base, index, err);
}

struct GameSkin *gameskin_array_get(BaseArray *base, int index,
                                    ErrorValue *err) {
  return array_get(base, index, err);
}
