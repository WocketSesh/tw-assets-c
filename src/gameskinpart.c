#include "gameskinpart.h"

static const struct GameSkinPartPosition skin_part_positions[NUM_SKIN_PARTS] = {
    [HOOK] = {64, 0, 128, 32},
    [HAMMER_CURSOR] = {0, 0, 64, 64},
    [GUN_CURSOR] = {0, 128, 64, 64},
    [SHOTGUN_CURSOR] = {0, 192, 64, 64},
    [GRENADE_CURSOR] = {0, 256, 64, 64},
    [NINJA_CURSOR] = {0, 320, 64, 64},
    [LASER_CURSOR] = {0, 384, 64, 64},
    [HAMMER] = {64, 32, 128, 96},
    [GUN] = {64, 128, 128, 64},
    [SHOTGUN] = {64, 192, 256, 64},
    [GRENADE] = {64, 256, 256, 64},
    [NINJA] = {64, 320, 256, 64},
    [LASER] = {64, 384, 224, 96},
    [GUN_AMMO] = {192, 128, 64, 64},
    [SHOTGUN_AMMO] = {320, 192, 64, 64},
    [GRENADE_AMMO] = {320, 256, 64, 64},
    [LASER_AMMO] = {320, 384, 64, 64},
    [GUN_PARTICLE_1] = {256, 128, 128, 64},
    [GUN_PARTICLE_2] = {384, 128, 128, 64},
    [GUN_PARTICLE_3] = {512, 128, 128, 64},
    [SHOTGUN_PARTICLE_1] = {384, 192, 128, 64},
    [SHOTGUN_PARTICLE_2] = {512, 192, 128, 64},
    [SHOTGUN_PARTICLE_3] = {640, 192, 128, 64},
    [PARTICLE_1] = {192, 0, 32, 32},
    [PARTICLE_2] = {224, 0, 32, 32},
    [PARTICLE_3] = {256, 0, 32, 32},
    [PARTICLE_4] = {192, 32, 32, 32},
    [PARTICLE_5] = {224, 32, 32, 32},
    [PARTICLE_6] = {256, 32, 32, 32},
    [PARTICLE_7] = {288, 0, 64, 64},
    [PARTICLE_8] = {352, 0, 64, 64},
    [PARTICLE_9] = {416, 0, 64, 64},
    [STAR_1] = {480, 0, 64, 64},
    [STAR_2] = {544, 0, 64, 64},
    [STAR_3] = {608, 0, 64, 64},
    [HEALTH_FULL] = {672, 0, 64, 64},
    [HEALTH_EMPTY] = {736, 0, 64, 64},
    [ARMOR_FULL] = {672, 64, 64, 64},
    [ARMOR_EMPTY] = {736, 64, 64, 64},
    [HEART] = {320, 64, 64, 64},
    [SHIELD] = {384, 64, 64, 64},
    [MINUS] = {256, 64, 64, 64},
    [NINJA_TIMER] = {672, 128, 128, 64},
    [NINJA_PARTICLE_1] = {800, 0, 224, 128},
    [NINJA_PARTICLE_2] = {800, 128, 224, 128},
    [NINJA_PARTICLE_3] = {800, 256, 224, 128},
    [FLAG_BLUE] = {384, 256, 128, 256},
    [FLAG_RED] = {512, 256, 128, 256}};

struct GameSkinPartPosition get_part_position(enum GameSkinPartID part) {
  if (part < 0 || part >= NUM_SKIN_PARTS)
    return (struct GameSkinPartPosition){0};

  return skin_part_positions[part];
}
