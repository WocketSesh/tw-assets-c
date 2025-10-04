#include "tw_assets.h"
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TWAssets init_tw_assets(int expceted_width, int expected_height,
                        const char *save_folder, int logging_enabled) {
  TWAssets twa;

  twa.save_folder = save_folder;
  twa.logging_enabled = logging_enabled;
  twa.expected_width = expceted_width;
  twa.expected_height = expected_height;

  BaseArray *arr = malloc(sizeof(BaseArray));
  ErrorValue err = gameskin_array_init(&arr);

  if (err.did_error) {
    printf("init_tw_assets error at gameskin_array_init: %s\n",
           err.error_message);
  }

  twa.p_gameskins = arr;
  return twa;
}

ErrorValue twa_gameskin_copy_part_from(TWAssets *twa, const char *src,
                                       const char *dst, GameSkinPartID part) {
  GameSkin *src_ = gameskin_array_find(twa->p_gameskins, src, NULL);
  GameSkin *dst_ = gameskin_array_find(twa->p_gameskins, dst, NULL);
  return gameskin_copy_part_from(src_, dst_, part);
}

ErrorValue twa_gameskin_from_path(TWAssets *twa, const char *path) {
  GameSkin *gs;
  gameskin_init(&gs);

  ErrorValue err = gameskin_from_path(path, gs);
  if (err.did_error) {
    gameskin_free(gs);
    return err;
  }

  return gameskin_array_push(twa->p_gameskins, gs);
}

ErrorValue twa_gameskin_save(TWAssets *twa, const char *name) {
  return gameskin_save(gameskin_array_find(twa->p_gameskins, name, NULL));
}

// Uses the base path provided while initializing TWA and appends the given name
// to load a gameskin
ErrorValue twa_gameskin_from_name(TWAssets *twa, const char *name) {
  size_t buf_size = strlen(name) + strlen(twa->save_folder) + 2;

  char *path = malloc(buf_size);

  if (path == NULL) {
    ErrorValue err;
    create_error(&err, "Error allocating for path");
    return err;
  }

  snprintf(path, buf_size, "%s/%s", twa->save_folder, name);

  return twa_gameskin_from_path(twa, path);
}

ErrorValue twa_clone_gameskin(TWAssets *twa, const char *name,
                              const char *new_name) {

  ErrorValue find_err;
  GameSkin *to_clone = gameskin_array_find(twa->p_gameskins, name, &find_err);

  if (find_err.did_error) {
    return find_err;
  }

  if (to_clone == NULL) {
    find_err.did_error = 1;
    find_err.error_message = "No gameskin with specified name";
    return find_err;
  }

  GameSkin *gs;
  gameskin_init(&gs);

  size_t buf_size = strlen(twa->save_folder) + strlen(new_name) +
                    6; // +1 for '/' + 1 for null term + 4 for .png
  char *full_path = malloc(buf_size);

  snprintf(full_path, buf_size, "%s/%s.png", twa->save_folder, new_name);

  printf("set full path to: %s\n", full_path);
  gs->path = full_path;

  if (strlen(new_name) + 1 > 256) {
    gs->name = realloc(gs->name, strlen(new_name) + 1);

    if (gs->name == NULL) {
      ErrorValue err;
      err.did_error = 1;
      err.error_message = "Error reallocating for new name length";

      gameskin_free(gs);
      return err;
    }
  }

  memcpy(gs->name, new_name, strlen(new_name) + 1);
  gs->width = to_clone->width;
  gs->height = to_clone->height;

  size_t pixel_size = gs->width * gs->height * 4;

  gs->pixels = malloc(pixel_size);

  if (gs->pixels == NULL) {
    ErrorValue err;
    err.did_error = 1;
    err.error_message = "Error allocating memory for pixels";
    gameskin_free(gs);

    return err;
  }

  memcpy(gs->pixels, to_clone->pixels, pixel_size);

  gameskin_array_push(twa->p_gameskins, gs);

  return (ErrorValue){0};
}
