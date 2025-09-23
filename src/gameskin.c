#include "gameskin.h"
#include "gameskinpart.h"
#include "helpers.h"
#include "png_handle.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

ErrorValue gameskin_array_init(BaseArray *base) {
  return array_init(base, sizeof(GameSkin));
}

ErrorValue gameskin_copy_part_from(GameSkin *src, GameSkin *dst,
                                   GameSkinPartID part) {
  if (src == NULL || dst == NULL || src->pixels == NULL ||
      dst->pixels == NULL) {
    return (struct ErrorValue){1, "Either src or dst is NULL"};
  }

  GameSkinPartPosition pos = get_part_position(part);

  write_pixels(src->pixels, dst->pixels, pos.x, pos.y, pos.height, pos.width);

  return (ErrorValue){0};
}

ErrorValue gameskin_save(struct GameSkin *gameskin) {
  lodepng_encode32_file(gameskin->path, gameskin->pixels, EXPECTED_WIDTH,
                        EXPECTED_HEIGHT);
}

ErrorValue gameskin_from_path(const char *path, GameSkin *gameskin) {
  load_png(path, &gameskin->pixels);
  get_name_extension(path, gameskin->name, NULL);
  gameskin->path = path;

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
  if (free_memory) {
    GameSkin *s = gameskin_array_get(base, index, NULL);
    if (s != NULL)
      free(s->pixels);
  }

  return array_remove(base, index, free_memory);
}

ErrorValue gameskin_array_clear(BaseArray *arr) {
  while (arr->length > 0) {
    gameskin_array_remove(arr, 0, 1);
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
