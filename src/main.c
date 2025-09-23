#include "gameskin.h"
#include <stdio.h>
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

  struct BaseArray *arr = malloc(sizeof(struct GameSkin));
  gameskin_array_init(arr);
  printf("init?\n");
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
