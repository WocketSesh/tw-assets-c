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
ErrorValue gameskin_init_array(BaseArray *base);
ErrorValue gameskin_push_array(BaseArray *base, GameSkin *gameskin);
ErrorValue gameskin_push_all_array(BaseArray *base, GameSkin **gameskin,
                                   int count);
GameSkin *gameskin_get_array(BaseArray *base, int index, ErrorValue *err);
GameSkin *gameskin_find_array(BaseArray *base, const char *name,
                              ErrorValue *err);
// just have this to check if it contains a skin rather than going through all
// the error checks in ReturnValue from find_gameskin_array
int gameskin_indexof_array(BaseArray *base, const char *name);

#endif
