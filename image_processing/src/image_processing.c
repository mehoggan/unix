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
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "image_processing.h"
#include "version_num.h"

#ifdef __cplusplus
namespace image_processing { extern "C" {
#endif

void
handle_help_option()
{
  size_t len;

  const char *header = "Report bugs to: matthew.hoggan@matthewh.me\n"
    "pkg home page: <http://gnu.org/software/image_processing>\n"
    "General help using GNU software: <http://www.gnu.org/gethelp/>\n";
  len = strlen(header) + sizeof(char);
  errno = 0;
  if (write(STDOUT_FILENO, header, len) == -1) {
    strerror(errno);
    exit(-1);
  }

  const char *directory_string = "  -d --directory <arg>"
    "    Absolute or relative path to a directory which contains\n"
    "                    images that need to be processed.\n";
  len = strlen(directory_string) + sizeof(char);
  errno = 0;
  if (write(STDOUT_FILENO, directory_string, len) == -1) {
    strerror(errno);
    exit(-1);
  }

  const char *file_string = "  -f --file <arg>"
    "         Absolute or relative path to a file which contains \n"
    "                    an image that needs to be processed.\n";
  len = strlen(file_string) + sizeof(char);
  errno = 0;
  if (write(STDOUT_FILENO, file_string, len) == -1) {
    strerror(errno);
    exit(-1);
  }

  const char *output_string = "  -o --output <arg>"
    "       Absolute or relative path to a directory where output\n"
    "                    of processing should be put.\n";
  len = strlen(output_string) + sizeof(char);
  errno = 0;
  if (write(STDOUT_FILENO, output_string, len) == -1) {
    strerror(errno);
    exit(-1);
  }
  exit(0);
}

void
handle_version_option()
{
  size_t len;
  size_t elem;

  const char* parts[] = {
    "GNU image_processing ",
    IMAGE_PROCESSING_VERSION_NUM,
    "\n",
    "Copyright (C) 2016 Free Software Foundation, Inc.\n"
    "License MIT: <https://opensource.org/licenses/MIT>\n"
    "This is free software: you are free to change and redistribute it.\n"
    "There is NO WARRANTY, to the exnent permitted by law.\n"};

  for (elem = 0; elem < sizeof(parts) / sizeof(parts[0]); ++elem) {
    len = strlen(parts[elem]) + sizeof(char);
    errno = 0;
    if (write(STDOUT_FILENO, parts[elem], len) == -1) {
      strerror(errno);
      exit(-1);
    }
    if (write(STDOUT_FILENO, "\n", strlen("\n") + sizeof(char)) == -1) {
      strerror(errno);
      exit(-1);
    }
  }
  exit(0);
}

int // -1 on failure
handle_file_option(const char *optarg)
{
  size_t len;

  if (optarg && strcmp(optarg, "") != 0) {
    errno = 0;
    len = strlen(optarg) + sizeof(char);
    if (write(STDOUT_FILENO, optarg, strlen(optarg) + sizeof(char)) == -1) {
      strerror(errno);
      exit(-1);
    }
    if (write(STDOUT_FILENO, "\n", strlen("\n") + sizeof(char)) == -1) {
      strerror(errno);
      exit(-1);
    }
    return 0;
  }

  return -1;
}

int // -1 on failure
handle_directory_option(const char *optarg)
{
  size_t len;

  if (optarg && strcmp(optarg, "") != 0) {
    errno = 0;
    len = strlen(optarg) + sizeof(char);
    if (write(STDOUT_FILENO, optarg, strlen(optarg) + sizeof(char)) == -1) {
      strerror(errno);
      exit(-1);
    }
    return 0;
  }

  return -1;
}

int // -1 on failure
handle_output_option(const char *optarg)
{
  size_t len;

  if (optarg && strcmp(optarg, "") != 0) {
    errno = 0;
    len = strlen(optarg) + sizeof(char);
    if (write(STDOUT_FILENO, optarg, strlen(optarg) + sizeof(char)) == -1) {
      strerror(errno);
      exit(-1);
    }
    return 0;
  }

  return -1;
}

int
application_specific_argparse()
{
  return -1;
}

int
parse_args(int argc, char *argv[])
{
  int opt; // Used by getopt(3) family of functions below.
  size_t byte_count;

  if (argc <= 1) {
    const char *err_str = "";
    byte_count = strlen(err_str) + sizeof(char);
    if (write(STDERR_FILENO, err_str, byte_count) == -1) {
    }
  }

  /*
    A string containing the legitimate option characters. If such a character
    is followed by a colon, the option requires an argument. Two colons imply
    it takes an optional arg. In both cases optarg will point to the argument,
    or NULL in the latter case if the argument is not specified.

    Modes:
    If the first character of optstring is a '+' or POSIXLY_CORRECT is set
    then option processing stops as soon as a nonoption argument is
    encountered.
    If the first character of optstring is a '-' then each nonoption
    argv-element is handled as if it were the argument of an option with
    character code 0x1.
    If in longopts below the val is specified it is treated like a option
    character in an option element used in getopt(3).
   */
  const char *optstring = "";

  /*
    This array is used by getopt_long or getopt_long_only

    name: Value of long option.
    has_arg: 0 no_argument, 1 required_arugment, 2 optional_argument
    flag: If NULL, make getopt_long or getopt_long_only return val. Else flag
    points to variable which is set to val if option is found but left
    unchanged if option is not found. If flag == NULL then 0 is returned by
    getopt_long(3) or getopt_long_only(3)
    val: The value to return, or load int the variable pointed to by flag.
  */
  struct option longopts[] = {
    {"directory", required_argument, NULL, (int)'d'},
    {"file", required_argument, NULL, (int)'f'},
    {"output", required_argument, NULL, (int)'o'},
    {"help", no_argument, NULL, (int)'h'},
    {"version", no_argument, NULL, 0},
    {0, 0, 0, 0}};


  /*
    getopt_long is like getopt(3) except that it also accepts long options
    started with two dashes. If the program accepts only long options then set
    optstring to the empty string and not NULL.

    longindex will point to the index of the long option relative to longopts.

    getopt_long_only allows for "-" and "--" to indicate a long option. Note
    that it is a GNU extension. Where as getopt(3) is part of POSIX.2 and
    POSIX.1-2001.

    if longopts[longindex].flag == NULL then the return value of
    getopt_long(3) or getopt_long_only(3) is val other wise it is 0 and flag
    points to val.
  */
  while (1) {
    int longindex;

    opt = getopt_long_only(argc, argv, optstring, longopts,
      &longindex);
    if (opt == -1) {
      break;
    }

    switch (opt) {
    case 0: { // Special case for version above. -v saved for verbose
      handle_version_option();
    }
    case 'f': { // User specified file.
      if (handle_file_option(optarg) == -1) {
        return -1;
      }
    }

    case 'd': { // User specified directory.
      if (handle_directory_option(optarg) == -1) {
        return -1;
      }
    }
    case 'o': { // User specified output.
      if (handle_output_option(optarg) == -1) {
        return -1;
      }
    }
    case 'h': { // User specified help.
      handle_help_option();
    }
    default: { // '?' Unknow argument.
      return -1;
    }
    }
  }

  return 0;
}

#ifdef __cplusplus
}}
#endif
