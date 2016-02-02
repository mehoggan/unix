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

#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#ifdef __cplusplus
namespace image_processing { extern "C" {
#endif

/**
 * @brief Used to parse application specific arguments from main and to set
 * key variables at start up.
 *
 * @param argc The number of args in argv
 * @param argv[] An array of c-strings representing arguments.
 *
 * @return Anything but -1 for success, or -1 on failure.
 */
int parse_args(int argc, char *argv[]);

#ifdef __cplusplus
}}
#endif

#endif//IMAGE_PROCESSING_H
