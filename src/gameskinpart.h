#ifndef GAMESKINPART_H
#define GAMESKINPART_H

#define NUM_SKIN_PARTS 48

typedef enum GameSkinPartID {
  HOOK,
  HAMMER_CURSOR,
  GUN_CURSOR,
  SHOTGUN_CURSOR,
  GRENADE_CURSOR,
  NINJA_CURSOR,
  LASER_CURSOR,
  HAMMER,
  GUN,
  SHOTGUN,
  GRENADE,
  NINJA,
  LASER,
  GUN_AMMO,
  SHOTGUN_AMMO,
  GRENADE_AMMO,
  LASER_AMMO,
  GUN_PARTICLE_1,
  GUN_PARTICLE_2,
  GUN_PARTICLE_3,
  SHOTGUN_PARTICLE_1,
  SHOTGUN_PARTICLE_2,
  SHOTGUN_PARTICLE_3,
  PARTICLE_1,
  PARTICLE_2,
  PARTICLE_3,
  PARTICLE_4,
  PARTICLE_5,
  PARTICLE_6,
  PARTICLE_7,
  PARTICLE_8,
  PARTICLE_9,
  STAR_1,
  STAR_2,
  STAR_3,
  HEALTH_FULL,
  HEALTH_EMPTY,
  ARMOR_FULL,
  ARMOR_EMPTY,
  HEART,
  SHIELD,
  MINUS,
  NINJA_TIMER,
  NINJA_PARTICLE_1,
  NINJA_PARTICLE_2,
  NINJA_PARTICLE_3,
  FLAG_BLUE,
  FLAG_RED
} GameSkinPartID;

typedef struct GameSkinPartPosition {
  int x;
  int y;
  int width;
  int height;
} GameSkinPartPosition;

typedef struct GameSkinPart {
  GameSkinPartID part;
  unsigned char *pixels;
} GameSkinPart;

GameSkinPartPosition get_part_position(GameSkinPartID part);

#endif
