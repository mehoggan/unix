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
#include "file_name.h"

#include <errno.h>
#include <linux/limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
namespace filesystem { extern "C" {
#endif

filename* filename_create(const char* name)
{
  char *dup = strdup(name);
  filename *file = (filename*)malloc(sizeof(filename));

  if (errno == ENOMEM) {
    free(dup);
    file = NULL;
  }

  file->name = dup;

  return file;
}

void filename_free(filename **name)
{
  free((*name)->name);
  free(*name);
  (*name) = NULL;
}

int filename_is_valid(const filename *const name)
{
  size_t idx;
  size_t len;
  int ret;

  ret = 1;
  if (name != NULL && name->name != NULL) {
    len = strlen(name->name);
    if (len <= PATH_MAX) {
      for (idx = 0; idx < len; ++idx) {
        // By definition a "c" string cannot contain the '\0' other than at the
        // end of it. However, the the strlen function will prevent the '\0'
        // from being found. Perhaps we could force the user to pass in a length
        // if needed.
        if (name->name[idx] == '/' || name->name[idx] == '\0') {
          ret = 0;
          break;
        }
      }
    }
  } else {
    ret = 0;
  }

  return ret;
}

#ifdef __cplusplus
}}
#endif
