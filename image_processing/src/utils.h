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

#include <stdint.h>

#ifdef __cplusplus
namespace image_processing { extern "C" {
#endif

/**
* @brief Write a message to stderr based on the line number in a given file
* from a specific function.
*
* @param line __LINE__
* @param file __FILE__
* @param func __FUNCTION__
*/
void print_msg(int line, const char *file, const char *func);

/**
* @brief If passed an appropiate value (see errno(3)) it will write to stderr
* a descriptive message. It will also terminate the program with an exit call.
*
* @param errnum Should be errno or a value defined in errno.h.
* @param line __LINE__
* @param file __FILE__
* @param func __FUNCTION__
*/
void print_error_msg_and_exit(int errnum, int line, const char *file,
  const char *func);

/**
* @brief If passed an appropiate value (see errno(3)) it will write to stderr
* a descriptive message. It will also terminate the program with an exit call.
*
* @param errnum Should be errno or a value defined in errno.h.
* @param line __LINE__
* @param file __FILE__
* @param func __FUNCTION__
*/
void print_error_msg(int errnum, int line, const char *file,
  const char *func);

/**
* @brief Counts the number of bytes needed to store parameter i including the
* sign into a null-terminated ascii string using the specified base.
*
* @param i The integer to count characters for.
* @param base Numerical base used to represent the value as a string, between
* 2 and 36, where 10 means decimal base, 16 hexidecimal, 8 octal, and 2
* binary.
*
* @return The number of bytes needed to store parameter i including the sign
* into a null-terminated ascii string using the specified base.
*/
size_t charcnta(int i, int base);

/**
* @brief Converts in integer value to a null-terminated string using the
* specified base and stores the results in the array given by the str
* parameter.
*
* @param i The integer to be converted.
* @param str Should be an array long enough to contain any possible value
* sizeof(int) * 8 + 1 for radix = 2, i.e. 17 bytyes in 16 bit platforms and 33
* on 32 bit platforms.
* @param base Numerical base used to represesnt the value as a string, between
* 2 and 36, where 10 means decimal base, 16 hexidecimal, 8 octal, and 2 binary.
*
* @return A pointer to the null-terminated string, same as parameter str.
*/
char *ip_itoa(int i, char *str, int base);

/**
* @brief Convert i to its n's complement.
*
* @param i The number in base b to be converted to its n`s complement.
* Expected to be null terminated.
* @param base Numerical base used to represesnt the value as a string, between
* 2 and 36, where 10 means decimal base, 16 hexidecimal, 8 octal, and 2 binary
*
* @note If any character in i is greater than or equal to base then i will
* not be modified.
*
* @return Returns NULL string on failure, or the value pointed to by i on
* on success.
*/
char *ncomp(char *i, int base);

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


