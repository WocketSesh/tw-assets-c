#include "gameskin.h"
#include "gameskinpart.h"
#include "helpers.h"
#include "png_handle.h"
#include <stddef.h>
#include <string.h>

ErrorValue gameskin_init_array(BaseArray *base) {
  return init_array(base, sizeof(GameSkin));
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

ErrorValue gameskin_push_array(BaseArray *base, GameSkin *gameskin) {
  if (base == NULL || gameskin == NULL)
    return (ErrorValue){1, "Either BaseArray or GameSkin is NULL"};

  if (gameskin_indexof_array(base, gameskin->name) != -1)
    return (ErrorValue){1, "Gameskin already exists with name"};

  return push_array(base, gameskin, sizeof(*gameskin));
}

ErrorValue gameskin_push_all_array(BaseArray *base, GameSkin **gameskin,
                                   int count) {
  if (gameskin == NULL)
    return (struct ErrorValue){1, "Gameskin array is NULL"};

  for (int i = 0; i < count; i++) {
    if (gameskin[i] == NULL)
      return (ErrorValue){1, "Gameskin is NULL"};

    ErrorValue ev = gameskin_push_array(base, gameskin[i]);
    if (ev.did_error)
      return ev;
  }

  return (ErrorValue){0};
}

int gameskin_indexof_array(BaseArray *base, const char *name) {
  for (int i = 0; i < base->length; i++) {
    void *rv = get_array(base, i, NULL);
    if (rv == NULL)
      continue;

    if (strcmp(((GameSkin *)(rv))->name, name) == 0)
      return i;
  }
  return -1;
}

GameSkin *gameskin_find_array(BaseArray *base, const char *name,
                              ErrorValue *err) {
  int index = gameskin_indexof_array(base, name);
  return index == -1 ? NULL : gameskin_get_array(base, index, err);
}

struct GameSkin *gameskin_get_array(struct BaseArray *base, int index,
                                    ErrorValue *err) {
  return get_array(base, index, err);
}
