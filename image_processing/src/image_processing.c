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
#include <dirent.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "image_processing.h"
#include "utils.h"
#include "version_num.h"

#ifdef __cplusplus
namespace image_processing { extern "C" {
#endif

void
handle_help_option()
{
  int status;
  size_t len;

  const char *header = "Report bugs to: matthew.hoggan@matthewh.me\n"
    "pkg home page: <http://gnu.org/software/image_processing>\n"
    "General help using GNU software: <http://www.gnu.org/gethelp/>\n";
  len = strlen(header) + sizeof(char);
  errno = 0;
  status = write(STDOUT_FILENO, header, len);
  if (status == -1) {
    print_error_msg_and_exit(errno, __LINE__, __FILE__, __FUNCTION__);
  }

  const char *required_args = "\nREQUIRED ARGUMENTS:\n";
  len = strlen(required_args) + sizeof(char);
  errno = 0;
  status = write(STDOUT_FILENO, required_args, len);
  if (status == -1) {
    print_error_msg_and_exit(errno, __LINE__, __FILE__, __FUNCTION__);
  }

  const char *directory_string = "  -d <arg> or --dir <arg>"
    "          Absolute or relative path to a directory\n"
    "                                   which contains images that need to\n"
    "                                   be processed. At least -f or -d is\n"
    "                                   required but both can be used.\n";
  len = strlen(directory_string) + sizeof(char);
  errno = 0;
  status = write(STDOUT_FILENO, directory_string, len);
  if (status == -1) {
    print_error_msg_and_exit(errno, __LINE__, __FILE__, __FUNCTION__);
  }

  const char *file_string = "  -f <arg> or --file <arg>"
    "         Absolute or relative path to a file which\n"
    "                                   contains images that need to be\n"
    "                                   processed. At least -f or -d is\n"
    "                                   required but both can be used.\n";
  len = strlen(file_string) + sizeof(char);
  errno = 0;
  status = write(STDOUT_FILENO, file_string, len);
  if (status == -1) {
    print_error_msg_and_exit(errno, __LINE__, __FILE__, __FUNCTION__);
  }

  const char *output_string = "  -o <arg> or --output <arg>"
    "       Absolute or relative path to a directory\n"
    "                                   where output of processing should\n"
    "                                   be put.\n";
  len = strlen(output_string) + sizeof(char);
  errno = 0;
  status = write(STDOUT_FILENO, output_string, len);
  if (status == -1) {
    print_error_msg_and_exit(errno, __LINE__, __FILE__, __FUNCTION__);
  }
}

void
handle_version_option()
{
  int status;
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
    status = write(STDOUT_FILENO, parts[elem], len);
    if (status == -1) {
      print_error_msg_and_exit(errno, __LINE__, __FILE__, __FUNCTION__);
    }
    errno = 0;
    status = write(STDOUT_FILENO, "\n", strlen("\n") + sizeof(char));
    if (status == -1) {
      print_error_msg_and_exit(errno, __LINE__, __FILE__, __FUNCTION__);
    }
  }
  exit(0);
}

int // -1 on failure
handle_file_option(const char *optarg)
{
  size_t len;
  int fd;

  if (!optarg || strcmp(optarg, "") == 0) {
    handle_help_option();
    return -1;
  }

  errno = 0;
  fd = open(optarg, O_RDONLY);
  if (fd == -1) {
    print_error_msg(errno, __LINE__, __FILE__, __FUNCTION__);
    return -1;
  }

  return 0;
}

int // -1 on failure
handle_directory_option(const char *optarg)
{
  int status;
  size_t len;
  DIR *dirp;
  struct dirent *dir_s;
  struct stat buf;

  if (!optarg || strcmp(optarg, "") == 0) {
    handle_help_option();
    return -1;
  }

  status = lstat(optarg, &buf);
  if (status == -1) {
      print_error_msg(errno, __LINE__, __FILE__, __FUNCTION__);
      return -1;
  }

  if (!S_ISDIR(buf.st_mode)) {
    return -1;
  }

  // TODO: Working here.
  if ((buf.st_mode & S_IFDIR) == 0) {
    // Get error etc.
  }

  errno = 0;
  dirp = opendir(optarg);
  if (dirp == NULL) {
    switch (errno) {
    case EACCES:
    case ENFILE:
    case ENOMEM: {
      print_error_msg(errno, __LINE__, __FILE__, __FUNCTION__);
      return -1;
    }
      // No break needed just return.
    case ENOENT: {
      errno = 0;
      status = mkdir(optarg, 0x755);
      if (status == -1) {
        print_error_msg(errno, __LINE__, __FILE__, __FUNCTION__);
        return -1;
      }
      dirp = opendir(optarg);
      if (dirp == NULL) {
        print_error_msg(errno, __LINE__, __FILE__, __FUNCTION__);
        return -1;
      }
    }
      break;
    default: {
      return -1;
    }
    }
  }

  errno = 0;
  status = closedir(dirp);
  if (status == -1) {
    print_error_msg(errno, __LINE__, __FILE__, __FUNCTION__);
    return -1;
  }

  return 0;
}

int // -1 on failure
handle_output_option(const char *optarg)
{
  int status;
  size_t len;

  if (optarg && strcmp(optarg, "") != 0) {
    errno = 0;
    len = strlen(optarg) + sizeof(char);
    status = write(STDOUT_FILENO, optarg, strlen(optarg) + sizeof(char));
    if (status == -1) {
      print_error_msg(errno, __LINE__, __FILE__, __FUNCTION__);
      exit(EXIT_FAILURE);
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
argparse(int argc, char *argv[])
{
  int status;
  int opt;
  size_t byte_count;

  char *input_file_name;
  char *input_dir_name;
  char *output_file_name;

  if (argc <= 1) {
    handle_help_option();
    return -1;
  }

  /*
    see getopt(3)
   */
  const char *optstring = "+f:d:o:";
  struct option longopts[] = {
    {"dir", required_argument, NULL, (int)'d'},
    {"file", required_argument, NULL, (int)'f'},
    {"output", required_argument, NULL, (int)'o'},
    {"help", no_argument, NULL, (int)'h'},
    {"version", no_argument, NULL, 0},
    {0, 0, 0, 0}};

    // Setting optind in getopt(3) to 0 allows us to scan another vector or
    // to rescan the same vector.
    while (1) {
      int longindex;

      opt = getopt_long(argc, argv, optstring, longopts, &longindex);

      if (opt == -1 && optind == argc) {
        optind = 0;
        break;
      } else if (opt == -1 && optind != argc) {
        handle_help_option();
        optind = 0;
        return -1;
      }

      switch (opt) {
      case 0: { // Special case for version above. -v saved for verbose
        handle_version_option();
        optind = 0;
        exit(0);
      }
        break;
      case 'f': {
        status = handle_file_option(optarg);
        if (status == -1) {
          optind = 0;
          return -1;
        }
      }
        break;
      case 'd': {
        status = handle_directory_option(optarg);
        if (status == -1) {
          optind = 0;
          return -1;
        }
      }
        break;
      case 'o': {
        status = handle_output_option(optarg);
        if (status == -1) {
          optind = 0;
          return -1;
        }
      }
        break;
      case 'h': {
        handle_help_option();
        optind = 0;
        exit(0);
      }
      default: { // '?' Unknow argument for getopt(3).
        optind = 0;
        return -1;
      }
      }
  }

  optind = 0;
  return 0;
}

#ifdef __cplusplus
}}
#endif
