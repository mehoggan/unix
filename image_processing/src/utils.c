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
  char *err, *line_num;
  size_t len;
  unsigned int byte_count;

  line_num = NULL;
  const char *header_part1 = "ERROR: line: ";
  len = strlen(header_part1);
  if (write(STDERR_FILENO, header_part1, len) == -1) {
    free(line_num);
    exit(EXIT_FAILURE);
  }

  byte_count = charcnta(line, 10);
  errno = 0;
  line_num = malloc(byte_count + 1);
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

// Note base 10 is a special case because it is the only case that does not
// take the N's complement, and it includes the '-' in the count of
// characters.
static const size_t complemnt_digit_count[] = {
   0,  0, 32, 20, 16, 14, 12, 12, 11, 10,
  -1,  9,  9,  9,  9,  8,  8,  8,  8,  8,
   8,  8,  7,  7,  7,  7,  7,  7,  7,  7,
   7,  7,  7,  7,  7,  7,  6
};

size_t
charcnta(int i, int base)
{
  int tmp;
  short digit_count;

  if (i < 0 && base != 10) {
    return complemnt_digit_count[base];
  }

  tmp = i;
  digit_count = (i != 0) ? 0 : 1;
  while (tmp) {
    tmp /= base;
    ++digit_count;
  }

  if (i < 0) {
    ++digit_count;
  }

  return digit_count;
}

char *
ncomp(char *i, int base)
{
  int max_char_index, complement_index, curr_index, carry;
  size_t len, index;

  const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";

  max_char_index = base - 1;

  len = strlen(i);

  // To prevent modifying invalid data do a check first.
  for (index = 0; index < len; ++index) {
    if (i[index] >= '0' && i[index] <= '9') {
      curr_index = i[index] - '0';
    } else if (i[index] >= 'a' && i[index] <= 'z') {
      curr_index = 10 + i[index] - 'a';
    } else {
      return NULL;
    }

    if (curr_index > max_char_index) {
      return NULL;
    }
  }

  // Calculate the (n - 1)'s complement.
  for (index = 0; index < len; ++index) {
    if (i[index] >= '0' && i[index] <= '9') {
      curr_index = i[index] - '0';
    } else if (i[index] >= 'a' && i[index] <= 'z') {
      curr_index = 10 + i[index] - 'a';
    }

    complement_index = max_char_index - curr_index;
    char curr_char = digits[complement_index];
    i[index] = curr_char;
  }

  // Now add 1, note we drop the carry bit on the most significant digit.
  carry = 1; // We start at 1 because we want to add one initially.
  for (index = len - 1; index != (size_t)(~0ull); --index) {
    if (i[index] >= '0' && i[index] <= '9') {
      curr_index = i[index] - '0';
    } else if (i[index] >= 'a' && i[index] <= 'z') {
      curr_index = 10 + i[index] - 'a';
    }

    if (curr_index + carry >= base) { // We have to carry
      i[index] = '0';
      carry = 1;
    } else {
      i[index] = digits[curr_index + carry];
      carry = 0;
    }
  }

  return i;
}

char *
ip_itoa(int i, char *str, int base)
{
  char digit;
  int tmp;
  size_t index;

  index = charcnta(i, base);
  memset(str, '0', index);
  str[index] = '\0';

  tmp = i;
  do {
    digit = '0' + abs(tmp % base);
    str[--index] = digit;
    tmp /= base;
  } while (tmp);

  if (i < 0 && base != 10) {
    str = ncomp(str, base);
  } else if (i < 0) {
    str[--index] = '-';
  }

  return str;
}

char *
get_exe_path()
{
  size_t len, bytes;
  char *pidstr, *argv_0;
  char path[PATH_MAX];
  char dest[PATH_MAX];
  int byte_count;
  pid_t pid;

  pid = getpid();
  byte_count = charcnta(pid, 10);
  errno = 0;
  pidstr = malloc(byte_count + 1);
  if (!pidstr || errno) {
    return NULL;
  }
  pidstr = ip_itoa(pid, pidstr, 10);
  strcpy(path, "/proc/");
  strcpy(path + strlen(path), pidstr);
  strcpy(path + strlen(path), "/exe");
  free(pidstr);

  errno = 0;
  if ((len = readlink(path, dest, PATH_MAX)) == -1) {
    print_error_msg(errno, __LINE__, __FILE__, __FUNCTION__);
    return NULL;
  }

  bytes = len + 1;
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

