#include "helpers.h"
#include "tw_assets.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_error(ErrorValue *err, const char *msg) {
  if (err == NULL)
    return;

  err->did_error = 1;
  err->error_message = msg;
}

String string_init(const char *str, ErrorValue *err) {
  size_t buf_size = strlen(str) + 1;
  String string = malloc(buf_size);

  if (string == NULL) {
    create_error(err, "Error allocating for string");
    return NULL;
  }

  memcpy_s(string, buf_size, str, buf_size);
  return string;
}

ErrorValue string_concat(String *string, int count, ...) {
  size_t str_length = strlen(*string);
  size_t concat_length = 0;

  va_list args;
  va_start(args, count);

  for (int i = 0; i < count; i++) {
    const char *str = va_arg(args, const char *);
    if (str == NULL) {
      va_end(args);
      return (ErrorValue){1, "Attempt to concat NULL str"};
    }
    concat_length += strlen(str);
  }

  va_end(args);

  size_t buf_size = str_length + concat_length + 1;

  String tmp = realloc(*string, buf_size);

  if (tmp == NULL) {
    return (ErrorValue){1, "Error reallocating for string"};
  }

  va_start(args, count);

  size_t offset = str_length;

  for (int i = 0; i < count; i++) {
    const char *str = va_arg(args, const char *);
    size_t length = strlen(str);
    memcpy(tmp + offset, str, length);
    offset += length;
  }

  tmp[offset] = '\0';

  va_end(args);

  *string = tmp;

  return (ErrorValue){0};
}

ErrorValue array_init(BaseArray **base, size_t size) {
  *base = malloc(sizeof(BaseArray));

  if (*base == NULL) {
    ErrorValue err;
    err.did_error = 1;
    err.error_message = "Error allocating memory for BaseArray";
    return err;
  }

  (*base)->length = 0;
  (*base)->allocated_length = 0;
  (*base)->size = size;

  (*base)->contents = malloc(size * 2);

  if ((*base)->contents == NULL) {
    return (struct ErrorValue){1, "Error Allocating Memory"};
  }

  return (struct ErrorValue){0};
}

ErrorValue array_allocate(BaseArray *base) {
  int new_allocated_length =
      base->allocated_length == 0 ? 2 : base->allocated_length * 2;

  void **tmp = realloc(base->contents, base->size * new_allocated_length);
  if (tmp == NULL) {
    return (ErrorValue){1, "Error Reallocating Memory"};
  }

  base->contents = tmp;

  base->allocated_length = new_allocated_length;
  return (struct ErrorValue){0};
}

int array_length(BaseArray *base) { return base == NULL ? -1 : base->length; }

ErrorValue array_push(BaseArray *base, void *content) {
  if (content == NULL) {
    return (ErrorValue){1, "Attempting to push NULL to array"};
  }

  ErrorValue err = array_needs_allocation(base) ? array_allocate(base)
                                                : (struct ErrorValue){0};

  if (err.did_error)
    return err;

  base->contents[base->length] = content;
  base->length++;

  return (ErrorValue){0};
}

int array_needs_allocation(struct BaseArray *base) {
  return (base->length + 1 > base->allocated_length);
}

void *array_get(BaseArray *base, int index, ErrorValue *err) {

  if (index >= base->length) {
    create_error(err, "Attempt to out of bounds index");
    return NULL;
  }

  void *at_index = base->contents[index];

  if (at_index == NULL) {
    create_error(err, "Value at index is NULL");
    return NULL;
  }

  return at_index;
}

ErrorValue array_remove(BaseArray *base, int index, int free_memory) {

  ErrorValue err;

  if (free_memory) {
    free(array_get(base, index, &err));
  }
  for (int i = index; i + 1 < base->length; i++) {
    base->contents[i] = base->contents[i + 1];
  }

  base->contents[base->length] = NULL;
  base->length--;

  return (ErrorValue){0};
}

ErrorValue array_clear(BaseArray *base) {
  while (base->length > 0) {
    array_remove(base, 0, 1);
  }

  return (ErrorValue){0};
}
