/*
  The MIT License

  Copyright (c) 2009 Matthew Hoggan matthew.hoggan@matthewh.me

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include "filename.h"

#include <errno.h>
#include <linux/limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
namespace filesystem { extern "C" {
#endif

filename_t filename_create(const char *name)
{
  filename_t ret;
  ret.name = NULL;

  if (name != NULL) {
    errno = 0;
    char *dup = strdup(name);
    if (!dup || errno == ENOMEM) {
      free(dup);
    } else {
      ret.name = dup;
    }
  }

  return ret;
}

filename_t *filename_ptr_create(const char *name)
{
  errno = 0;
  void *ret = malloc(sizeof(filename_t));
  if (!ret || errno == ENOMEM) {
    free(ret);
    return NULL;
  }
  ((filename_t *)ret)->name = NULL;

  if (name != NULL) {
    errno = 0;
    char *dup = strdup(name);
    if (!dup || errno == ENOMEM) {
      free(dup);
      free(ret);
      return NULL;
    }
    ((filename_t *)ret)->name = dup;
  }

  return (filename_t *)ret;
}

void filename_free(filename_t *name)
{
  free(name->name);
  name->name = NULL;
}

void filename_ptr_free(filename_t **name)
{
  free((*name)->name);
  free(*name);
  (*name) = NULL;
}

int filename_is_valid(const filename_t *const name)
{
  size_t idx;
  size_t len;
  int ret;

  ret = 1;
  if (name != NULL && name->name != NULL) {
    len = strlen(name->name);
    if (len <= PATH_MAX) {
      for (idx = 0; idx < len; ++idx) {
        // By definition a "c" string cannot contain the '\0' other than at
        // the end of it. However, the the strlen function will prevent the
        // '\0' from being found. Perhaps we could force the user to pass in a        // length if needed.
        if (name->name[idx] == '/' || name->name[idx] == '\0') {
          ret = 0;
          break;
        }
      }
    } else {
      ret = 0;
    }
  } else {
    ret = 0;
  }

  return ret;
}

filename_t filename_dup(const filename_t *const name)
{
  filename_t ret;
  ret.name = NULL;

  if (name != NULL && name->name != NULL) {
    errno = 0;
    char *dup = strdup(name->name);
    if (!dup || errno == ENOMEM) {
      free(dup);
    } else {
      ret.name = dup;
    }
  }

  return ret;
}

filename_t *filename_ptr_dup(const filename_t *const name)
{
  void *ret;

  if (!name) {
    return NULL;
  }

  errno = 0;
  ret = malloc(sizeof(filename_t));
  if (!ret || errno == ENOMEM) {
    free(ret);
    return NULL;
  }
  ((filename_t *)ret)->name = NULL;

  if (name->name != NULL) {
    errno = 0;
    char *dup = strdup(name->name);
    if (!dup || errno == ENOMEM) {
      free(ret);
      free(dup);
      return NULL;
    }
    ((filename_t *)ret)->name = dup;
  }

  return ret;
}

void filename_app(filename_t *name, const char *app)
{
  void *tmp = NULL;

  if (!name || !(name->name) || !app) {
    return;
  }

  size_t name_bytes_cnt = strlen(name->name);
  size_t app_bytes_cnt = strlen(app);
  size_t new_bytes_cnt = name_bytes_cnt + app_bytes_cnt + sizeof(char);

  errno = 0;
  tmp = realloc((void *)name->name, new_bytes_cnt);
  if (!tmp || errno == ENOMEM) {
    free(tmp);
    return;
  }

  tmp = strcat(tmp, app);
  name->name = tmp;
}

void filename_ptr_app(filename_t **name, const char *app)
{
  void *tmp;

  if (!name || !(*name) || !((*name)->name) || !app) {
    return;
  }

  size_t name_bytes_cnt = strlen((*name)->name);
  size_t app_bytes_cnt = strlen(app);
  size_t new_bytes_cnt = name_bytes_cnt + app_bytes_cnt + sizeof(char);

  errno = 0;
  tmp = realloc((void *)(*name)->name, new_bytes_cnt);
  if (!tmp || errno == ENOMEM) {
    free(tmp);
    return;
  }

  tmp = strcat(tmp, app);
  (*name)->name = tmp;
}

int filename_has_extension(const filename_t *const name)
{
  size_t len;
  int idx;
  int jdx;
  const char *curr;
  ptrdiff_t diff;

  if (!name || !(name->name)) {
    return 0;
  }

  const char *dot = strrchr(name->name, '.');
  if (!dot || dot == name->name) {
    return 0;
  }

  diff = &(name->name[strlen(name->name)]) - dot;
  if (diff >= 1 && diff <= 3) {
    return 0;
  }

  curr = dot + 1;
  while (*curr != '\0') {
    if (*curr > 'Z' && *curr < 'a') {
      return 0;
    } else if (*curr < 'A' || *curr > 'z') {
      return 0;
    }
    ++curr;
  }

  return 1;
}

char *filename_get_extension(const filename_t *const name)
{
  void *ret;
  size_t len;
  int idx;
  ptrdiff_t diff;

  if (!filename_has_extension(name)) {
    return NULL;
  }

  // No check on dot because filename_has_extension already verified this.
  const char *dot = strrchr(name->name, '.');
  diff = &(name->name[strlen(name->name)]) - dot;
  ret = NULL;
  errno = 0;
  ret = malloc(diff * sizeof(char) + sizeof(char));
  if (!ret || errno == ENOMEM) {
    free(ret);
    ret = NULL;
  } else {
    strcpy(ret, dot);
  }

  return ret;
}

#ifdef __cplusplus
}}
#endif
