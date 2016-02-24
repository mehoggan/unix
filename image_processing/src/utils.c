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
#include <limits.h>
#include <linux/limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "utils.h"

void
print_error_msg_and_exit(int errnum, int line, const char *file,
  const char *func)
{
  print_error_msg(errnum, line, file, func);
  exit(EXIT_FAILURE);
}

void
print_error_msg(int errnum, int line, const char *file, const char *func)
{
  size_t len;
  char *err;
  char *line_num;
  unsigned int byte_count;

  const char *header_part1 = "ERROR: line: ";
  len = strlen(header_part1);
  if (write(STDERR_FILENO, header_part1, len) == -1) {
    free(line_num);
    exit(EXIT_FAILURE);
  }

  byte_count = charcnta(line, 10);
  errno = 0;
  line_num = malloc(byte_count + 1 * sizeof(char));
  if (!line_num || errno) {
    exit(EXIT_FAILURE);
  }
  line_num = ip_itoa(line, line_num, 10);
  len = strlen(line_num);
  if (write(STDERR_FILENO, line_num, len) == -1) {
    free(line_num);
    exit(EXIT_FAILURE);
  }

  const char *header_part2 = " file: ";
  len = strlen(header_part2);
  if (write(STDERR_FILENO, header_part2, len) == -1) {
    free(line_num);
    exit(EXIT_FAILURE);
  }

  len = strlen(file);
  if (write(STDERR_FILENO, file, len) == -1) {
    free(line_num);
    exit(EXIT_FAILURE);
  }

  const char *header_part3 = " function: ";
  len = strlen(header_part3);
  if (write(STDERR_FILENO, header_part3, len) == -1) {
    free(line_num);
    exit(EXIT_FAILURE);
  }

  len = strlen(func);
  if (write(STDERR_FILENO, func, len) == -1) {
    free(line_num);
    exit(EXIT_FAILURE);
  }

  const char *header_part4 = "\n\t";
  len = strlen(header_part4);
  if (write(STDERR_FILENO, header_part4, len) == -1) {
    free(line_num);
    exit(EXIT_FAILURE);
  }

  err = strerror(errnum);
  len = strlen(err) + sizeof(char);
  if (write(STDERR_FILENO, err, len) == -1) {
    free(line_num);
    exit(EXIT_FAILURE);
  }

  if (write(STDERR_FILENO, "\n", strlen("\n") + sizeof(char)) == -1) {
    free(line_num);
    exit(EXIT_FAILURE);
  }

  free(line_num);
}

size_t
charcnta(int i, int base)
{
  int tmp;
  short digit_cnt;

  tmp = i;
  digit_cnt = (i != 0) ? 0 : 1;
  do {
    tmp /= base;
    ++digit_cnt;
  } while(tmp);

  return digit_cnt * sizeof(char);
}

char *
ip_itoa(int i, char *str, int base)
{
  char digit;
  char max_char;
  char complement_char;
  int tmp;
  size_t index;
  size_t max_digits;
  int carry_bit;

  const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
  max_digits = charcnta(INT_MIN, base);

  max_char = digits[base - 1];
  index = charcnta(i, base);

  str[--index] = '\0';

  tmp = i;
  do {
    digit = '0' + abs(tmp % base);
    str[--index] = digit;
    tmp /= 10;
  } while (tmp != 0);

  if (i < 0) {
    str[--index] = '-';
  }

  return str;
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
  char *argv_0;
  int byte_count;

  pid = getpid();
  byte_count = charcnta(pid, 10);
  pidstr = malloc(byte_count + 1 * sizeof(char));
  pidstr = ip_itoa(pid, pidstr, 10);
  if (!pidstr) {
    return NULL;
  }
  strcpy(path, "/proc/");
  strcpy(path + strlen(path), pidstr);
  strcpy(path + strlen(path), "/exe");
  free(pidstr);

  errno = 0;
  if ((len = readlink(path, dest, PATH_MAX)) == -1) {
    print_error_msg(errno, __LINE__, __FILE__, __FUNCTION__);
    return NULL;
  }

  bytes = len * sizeof(char) + sizeof(char);
  errno = 0;
  argv_0 = malloc(bytes);
  if (argv_0 == NULL || errno) {
    free(argv_0);
    print_error_msg(errno, __LINE__, __FILE__, __FUNCTION__);
    return NULL;
  }

  argv_0 = memcpy(argv_0, dest, bytes);
  if (argv_0 == NULL) {
    free(argv_0);
    return NULL;
  }

  argv_0[len] = '\0';

  return argv_0;
}

