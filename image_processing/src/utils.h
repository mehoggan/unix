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

#ifndef UTILS_H
#define UTILS_H

#ifdef __cplusplus
namespace image_processing { extern "C" {
#endif

/**
* @brief If passed an appropiate value (see errno(3)) it will write to stderr
* a descriptive message. It will also terminate the program with an exit call.
*
* @param errnum Should be errno or a value defined in errno.h.
*/
void print_error_msg_and_exit(int errnum);

/**
* @brief If passed an appropiate value (see errno(3)) it will write to stderr
* a descriptive message.
*
* @param errnum Should be errno or a value defined in errno.h.
*/
void print_error_msg(int errnum);

/**
* @brief Converts param i to a c string to be free'd by client code.
*
* @param i The integer to be converted.
*
* @return a null terminated c string to be free'd by clients whoes value is
* lexicographically equivalent to the value contained in param i. Otherwise
* it returns NULL if the coversion is not possible.
*/
char *itoa(int i);

/**
* @brief Used to get the path of the current executable. This is accomplished
* by reading the symlink for /proc/getpid()/exe.
*
* @return a malloc'd c string that is to be free'd by client code.
*/
char *get_exe_path();

#ifdef __cplusplus
}}
#endif
#endif


