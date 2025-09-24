
#ifndef TW_ASSETS_H
#define TW_ASSETS_H

#include "helpers.h"

// Helpers
typedef struct BaseArray BaseArray;

// GameSkinPart
#define NUM_SKIN_PARTS 48

typedef enum GameSkinPartID {
  GAMESKIN_HOOK,
  GAMESKIN_HAMMER_CURSOR,
  GAMESKIN_GUN_CURSOR,
  GAMESKIN_SHOTGUN_CURSOR,
  GAMESKIN_GRENADE_CURSOR,
  GAMESKIN_NINJA_CURSOR,
  GAMESKIN_LASER_CURSOR,
  GAMESKIN_HAMMER,
  GAMESKIN_GUN,
  GAMESKIN_SHOTGUN,
  GAMESKIN_GRENADE,
  GAMESKIN_NINJA,
  GAMESKIN_LASER,
  GAMESKIN_GUN_AMMO,
  GAMESKIN_SHOTGUN_AMMO,
  GAMESKIN_GRENADE_AMMO,
  GAMESKIN_LASER_AMMO,
  GAMESKIN_GUN_PARTICLE_1,
  GAMESKIN_GUN_PARTICLE_2,
  GAMESKIN_GUN_PARTICLE_3,
  GAMESKIN_SHOTGUN_PARTICLE_1,
  GAMESKIN_SHOTGUN_PARTICLE_2,
  GAMESKIN_SHOTGUN_PARTICLE_3,
  GAMESKIN_PARTICLE_1,
  GAMESKIN_PARTICLE_2,
  GAMESKIN_PARTICLE_3,
  GAMESKIN_PARTICLE_4,
  GAMESKIN_PARTICLE_5,
  GAMESKIN_PARTICLE_6,
  GAMESKIN_PARTICLE_7,
  GAMESKIN_PARTICLE_8,
  GAMESKIN_PARTICLE_9,
  GAMESKIN_STAR_1,
  GAMESKIN_STAR_2,
  GAMESKIN_STAR_3,
  GAMESKIN_HEALTH_FULL,
  GAMESKIN_HEALTH_EMPTY,
  GAMESKIN_ARMOR_FULL,
  GAMESKIN_ARMOR_EMPTY,
  GAMESKIN_HEART,
  GAMESKIN_SHIELD,
  GAMESKIN_MINUS,
  GAMESKIN_NINJA_TIMER,
  GAMESKIN_NINJA_PARTICLE_1,
  GAMESKIN_NINJA_PARTICLE_2,
  GAMESKIN_NINJA_PARTICLE_3,
  GAMESKIN_FLAG_BLUE,
  GAMESKIN_FLAG_RED
} GameSkinPartID;

typedef struct GameSkinPartPosition {
  int x;
  int y;
  int width;
  int height;
} GameSkinPartPosition;

GameSkinPartPosition gameskin_get_part_position(GameSkinPartID part);

// GameSkin
#define GAME_SKIN_PARTS 10

typedef struct GameSkin {
  char *name;
  char *path;
  unsigned char *pixels;
} GameSkin;

// Array
ErrorValue gameskin_array_init(BaseArray *base);
ErrorValue gameskin_array_push(BaseArray *base, GameSkin *gameskin);
ErrorValue gameskin_array_push_all(BaseArray *base, GameSkin **gameskin,
                                   int count);
ErrorValue gameskin_array_remove(BaseArray *base, int index, int free_memory);
ErrorValue gameskin_array_clear(BaseArray *arr);
GameSkin *gameskin_array_get(BaseArray *base, int index, ErrorValue *err);
GameSkin *gameskin_array_find(BaseArray *base, const char *name,
                              ErrorValue *err);
int gameskin_array_length(BaseArray *base);

ErrorValue gameskin_free(GameSkin *gs);

ErrorValue gameskin_copy_part_from(GameSkin *src, GameSkin *dst,
                                   GameSkinPartID part);
ErrorValue gameskin_save(GameSkin *gameskin);
ErrorValue gameskin_from_path(const char *path, GameSkin *gameskin);
ErrorValue gameskin_save_part(GameSkin *gameskin, GameSkinPartID part,
                              const char *path);
ErrorValue gameskin_save_all_parts(GameSkin *gameskin, const char *folder_path);
unsigned char *gameskin_get_part_pixels(GameSkin *gameskin, GameSkinPartID part,
                                        unsigned *height, unsigned *width,
                                        ErrorValue *err);
ErrorValue gameskin_init(GameSkin **gs);

// just have this to check if it contains a skin rather than going through all
// the error checks in ReturnValue from find_gameskin_array
int gameskin_array_indexof(BaseArray *base, const char *name);

#endif
