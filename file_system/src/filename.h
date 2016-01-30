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
* @brief Duplicates name param int the name member variable of a filename_t and
* returns a filename_t on the stack by value.
*
* @param name A NULL terminated string that represents the path.
*
* @pre name param must be NULL terminated c-string.
*
* @post If there is sufficient memory filename_t will be returned by value and
* its name member variable will be a string duplicate of the name param.
*
* @return A filename_t with its name set to name param
*/
filename_t filename_create(const char *name);

/**
* @brief Duplicates name param into the name member variable of a filename.
*
* @param name A NULL terminated string that represents the path.
*
* @pre name param must be NULL terminated c-string.
*
* @post If there is sufficient memory a filename_t will be allocated on the
* heap and its name member variable will be a string duplicate of the name
* param.
*
* @return A filename_t with its name set to name param or null if there is not
* sufficient memory.
*/
filename_t *filename_ptr_create(const char *name);

/**
* @brief A filename_t to be un allocated on the heap
*
* @pre name param's name member variable is not NULL.
*
* @post name param has its name member variable unallocated and set to NULL.
*
* @param name The filename_t to have its name member variable freed'
*/
void filename_free(filename_t *name);

/**
* @brief A filename_t* to be un allocated on the heap.
*
* @pre name param is not NULL.
*
* @post name param has its name member variable unallocated and the name param
* is also unallocated on the heap and name param is set to NULL.
*
* @param name The filename_t to be freed.
*/
void filename_ptr_free(filename_t **name);

/**
* @brief Checks for the presence of '\0' char or a slash in the name
* param.
*
* @param name The filename_t to check for validity.
*
* @return 0 if not valid and 1 if valid. Valid implies that '/' and '\0' are
* not present in the name params name member variable. It also confirms that
* the name param's name member variable is less than PATH_MAX.
*/
int filename_is_valid(const filename_t *const name);

/**
* @brief Duplicates a filename_t (name) into a new filename_t.
*
* @param name The filename_t to duplicate.
*
* @return A new filename_t struct with a duplicate name member variable
* equivalent to the one in the name parameter.
*/
filename_t filename_dup(const filename_t *const name);

/**
* @brief Duplicates a filename_t (name) into a new filename_t*
*
* @param name The filename_t to duplicate.
*
* @return A new filename_t struct * with a duplicate name member variable
* equivalent to the one in name parameter.
*/
filename_t *filename_ptr_dup(const filename_t *const name);

#ifdef __cplusplus
}}
#endif

#endif//FILE_NAME_H
