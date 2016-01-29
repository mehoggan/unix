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

#ifndef FILE_NAME_H
#define FILE_NAME_H

#ifdef __cplusplus
namespace filesystem { extern "C" {
#endif

/**
* @brief A representation of a filename.
*/
typedef struct {
  char *name;
} filename_t;

/**
* @brief Duplicates name param into the name member variable of a filename.
*
* @param name A NULL terminated string that represents the path.
*
* @pre name param must be NULL terinated string.
*
* @post If there is sufficient memory filename will will be allocated on the
* heap and its name member variable will be a string duplicate of name param.
*
* @return A filename with its name set to name param or null if there is not
* sufficient memory.
*/
filename_t *filename_create(const char *name);

/**
* @brief A filename to be un allocated on the heap.
*
* @pre name param is not NULL.
*
* @post name param has its name member variable unallocated and the name param
* is also unallocated on the heap and name param is set to NULL.
*
* @param name The filename to be freed.
*/
void filename_free(filename_t **name);

/**
* @brief Checks for the presence of '\0' char or a slash in the name
* param.
*
* @param name The filename to check for validity.
*
* @return 0 if not valid and 1 if valid. Valid implies that '/' and '\0' are
* not present in the name params name member variable. It also confirms that
* the name param's name member variable is less than PATH_MAX.
*/
int filename_is_valid(const filename_t *const name);

/**
* @brief Duplicates a filename_t (name) into a new filename_t struct.
*
* @param name The filename_t to duplicate.
*
* @pre name param is not NULL.
*
* @post If memory is sufficient then the return value will have a duplicate
* of the name param's name member variable. Otherwise we will return NULL.
*
* @return A new filename_t struct with a duplicate name member variable
* equivalent to the one in name parameter.
*/
filename_t *filename_dup(const filename_t *const name);

#ifdef __cplusplus
}}
#endif

#endif//FILE_NAME_H
