/*
  The MIT License

  Copyright (c) 2016 Matthew Hoggan matthew.hoggan@matthewh.me

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to
  deal in the Software without restriction, including without limitation the
  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
  sell copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/

#include <errno.h>
#include <fenv.h>
#include <linux/limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils.h"

void
print_error_msg_and_exit(int errnum)
{
  size_t len;
  char *err;

  err = strerror(errnum);
  len = strlen(err);
  if (write(STDERR_FILENO, err, len) == -1) {
    exit(EXIT_FAILURE);
  }
  if (write(STDERR_FILENO, "\n", strlen("\n") + sizeof(char)) == -1) {
    exit(EXIT_FAILURE);
  }
  exit(EXIT_FAILURE);
}

void
print_error_msg(int errnum)
{
  size_t len;
  char *err = strerror(errnum);

  len = strlen(err) + sizeof(char);
  if (write(STDERR_FILENO, err, len) == -1) {
    exit(EXIT_FAILURE);
  }
  if (write(STDERR_FILENO, "\n", strlen("\n") + sizeof(char)) == -1) {
    exit(EXIT_FAILURE);
  }
}

char *
itoa(int i)
{
  short digit_cnt;
  short index;
  void *ret;
  char digit;

  errno = 0;
  feclearexcept(FE_ALL_EXCEPT);
  if (i == 0) {
    digit_cnt = 1;
  } else {
    digit_cnt = floor(log10(abs(i))) + 1;
    if (errno || fetestexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW |
      FE_UNDERFLOW)) {
      return NULL;
    }
  }

  if (i < 0) {
    ++digit_cnt;
  }
  ++digit_cnt; // '\0'

  errno = 0;
  if ((ret = malloc(digit_cnt * sizeof(char))) == NULL || errno) {
    print_error_msg(errno);
    free(ret);
    return NULL;
  }

  // This made debugging easier.
  memset(ret, '0', digit_cnt * sizeof(char));

  index = digit_cnt;
  ((char*)ret)[--index] = '\0';

  do {
    digit = (char)((int)'0' + i % 10);
    ((char*)ret)[--index] = digit;
    i /= 10;
  } while (i > 0);

  if (i < 0) {
    ((char*)ret)[--index] = '-';
  }

  return ret;
}

char *
get_exe_path()
{
  size_t len;
  size_t bytes;
  char path[PATH_MAX];
  char dest[PATH_MAX];
  pid_t pid;
  char *pidstr;
  void *argv_0;

  pid = getpid();
  pidstr = itoa(getpid());
  if (!pidstr) {
    return NULL;
  }
  strcpy(path, "/proc/");
  strcpy(path + strlen(path), pidstr);
  strcpy(path + strlen(path), "/exe");
  free(pidstr);

  errno = 0;
  if ((len = readlink(path, dest, PATH_MAX)) == -1) {
    print_error_msg(errno);
    return NULL;
  }

  bytes = len * sizeof(char) + sizeof(char);
  errno = 0;
  if ((argv_0 = malloc(bytes)) == NULL || errno) {
    free(argv_0);
    print_error_msg(errno);
    return NULL;
  }

  if ((argv_0 = memcpy(argv_0, dest, bytes)) == NULL) {
    free(argv_0);
    return NULL;
  }

  ((char*)argv_0)[len] = '\0';

  return argv_0;
}

