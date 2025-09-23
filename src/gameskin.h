#ifndef GAMESKIN_H
#define GAMESKIN_H

#include "gameskinpart.h"
#include "helpers.h"

#define GAME_SKIN_PARTS 10

typedef struct GameSkin {
  char *name;
  char *path;
  unsigned char *pixels;
  GameSkinPart parts[GAME_SKIN_PARTS];
} GameSkin;

ErrorValue gameskin_copy_part_from(GameSkin *src, GameSkin *dst,
                                   GameSkinPartID part);

ErrorValue gameskin_save(GameSkin *gameskin);

ErrorValue gameskin_from_path(const char *path, GameSkin *gameskin);
ErrorValue gameskin_array_init(BaseArray *base);
ErrorValue gameskin_array_push(BaseArray *base, GameSkin *gameskin);
ErrorValue gameskin_array_push_all(BaseArray *base, GameSkin **gameskin,
                                   int count);
ErrorValue gameskin_array_remove(BaseArray *base, int index, int free_memory);
ErrorValue gameskin_array_clear(BaseArray *arr);
GameSkin *gameskin_array_get(BaseArray *base, int index, ErrorValue *err);
GameSkin *gameskin_array_find(BaseArray *base, const char *name,
                              ErrorValue *err);
// just have this to check if it contains a skin rather than going through all
// the error checks in ReturnValue from find_gameskin_array
int gameskin_array_indexof(BaseArray *base, const char *name);

#endif
