#include "gameskin.h"
#include <stdlib.h>

int main() {

  struct GameSkin *game_06 = malloc(sizeof(struct GameSkin));
  gameskin_from_path("C:/Users/wocke/Coding/C/tw-assets/test/game_06.png",
                     game_06);

  struct GameSkin *purplehaze = malloc(sizeof(struct GameSkin));
  gameskin_from_path("C:/Users/wocke/Coding/C/tw-assets/test/purplehaze.png",
                     purplehaze);

  gameskin_copy_part_from(purplehaze, game_06, GRENADE);
  gameskin_copy_part_from(purplehaze, game_06, GUN);
  gameskin_save(game_06);

  return 0;
}
