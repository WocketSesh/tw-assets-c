#include "tw_assets.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct GameSkin *game_06;
  gameskin_init(&game_06);

  gameskin_from_path("C:/Users/wocke/Coding/C/tw-assets/test/game_06.png",
                     game_06);

  struct GameSkin *purplehaze;
  gameskin_init(&purplehaze);

  gameskin_from_path("C:/Users/wocke/Coding/C/tw-assets/test/purplehaze.png",
                     purplehaze);

  gameskin_copy_part_from(purplehaze, game_06, GAMESKIN_GRENADE);
  gameskin_copy_part_from(purplehaze, game_06, GAMESKIN_GUN);
  gameskin_copy_part_from(purplehaze, game_06, GAMESKIN_HAMMER);
  gameskin_save(game_06);

  ErrorValue errpa = gameskin_save_part(
      purplehaze, GAMESKIN_HAMMER,
      "C:/Users/wocke/Coding/C/tw-assets/test/purplehaze_hammer.png");

  struct BaseArray *arr = malloc(sizeof(struct GameSkin));
  gameskin_array_init(arr);
  gameskin_array_push(arr, game_06);
  gameskin_array_push(arr, purplehaze);

  for (int i = 0; i < arr->length; i++) {
    GameSkin *gs = gameskin_array_get(arr, i, NULL);

    if (gs != NULL)
      printf("Got gs: %s at index: %d\n", gs->name, i);
  }

  gameskin_array_clear(arr);
  return 0;
}
