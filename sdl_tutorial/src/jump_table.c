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

#include <dlfcn.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "opengl_core.h"

static void init_api(void);

///*
//  Note args will not be used here but are used below. The typedef is for
//  function pointers for jump table, and predeclare funcs. The DEFAULT funcs
//  will init jump table and then call real function. The REAL funcs are the
//  actual functions, name-mangled to not clash.
//*/
//#define CREATE_JUMP_TABLE_ENTRY(ret, func, params, args, retkw) \
//  typedef ret (*JUMP_TABLE_ENTRY_##func) params;
//#include "jump_table.h"
//#undef CREATE_JUMP_TABLE_ENTRY
//
//#define CREATE_JUMP_TABLE_ENTRY(ret, func, params, args, retkw) \
//  static ret func##_DEFAULT params;
//#include "jump_table.h"
//#undef CREATE_JUMP_TABLE_ENTRY
//
//#define CREATE_JUMP_TABLE_ENTRY(ret, func, params, args, retkw) \
//  extern ret func##_REAL params;
//#include "jump_table.h"
//#undef CREATE_JUMP_TABLE_ENTRY
//
///*
//  A jump table implementation.
//*/
//typedef struct {
//  #define CREATE_JUMP_TABLE_ENTRY(ret, func, params, args, retkw) \
//    JUMP_TABLE_ENTRY_##func func;
//  #include "jump_table.h"
//  #undef CREATE_JUMP_TABLE_ENTRY
//} DynamicJumpTable;
//
///*
//  Predeclare the default functions for initializing the jump table.
//*/
//#define CREATE_JUMP_TABLE_ENTRY(ret, func, params, args, retkw) \
//  static ret func##_DEFAULT params;
//#include "jump_table.h"
//#undef CREATE_JUMP_TABLE_ENTRY
//
///*
//  The actual jump table.
//*/
//static DynamicJumpTable jump_table = {
//  #define CREATE_JUMP_TABLE_ENTRY(ret, func, params, args, retkw) \
//    func##_DEFAULT,
//  #include "jump_table.h"
//  #undef CREATE_JUMP_TABLE_ENTRY
//};
//
///*
//  The magic. All functions in the jump_table should call init_api() below.
//*/
//#define CREATE_JUMP_TABLE_ENTRY(ret, func, params, args, retkw) \
//  static ret func##_DEFAULT params { \
//    init_api(); \
//    retkw jump_table.func args; \
//  }
//#include "jump_table.h"
//#undef CREATE_JUMP_TABLE_ENTRY
//
///*
//  Public API function to jump into the jump table.
//*/
//#define CREATE_JUMP_TABLE_ENTRY(ret, func, params, args, retkw) \
//  ret func params { retkw jump_table.func args; }
//#include "jump_table.h"
//#undef CREATE_JUMP_TABLE_ENTRY
//
//extern int32_t
//jump_table_create(int32_t, void *, size_t);
//
//int32_t
//jump_table_create(int32_t apiver, void *table, size_t size)
//{
//  DynamicJumpTable *result_table = (DynamicJumpTable *)table;
//
//  // More functions have been added. We cannot provide them so bail out.
//  if (size > sizeof(jump_table)) {
//    return -1;
//  }
//
//  // Actual initialization of jump table.
//  #define CREATE_JUMP_TABLE_ENTRY(ret, func, params, args, retkw) \
//    jump_table.func = func##_REAL;
//  #include "jump_table.h"
//  #undef CREATE_JUMP_TABLE_ENTRY
//
//  if (result_table != &jump_table) {
//    memcpy(result_table, &jump_table, size);
//  }
//
//  return 0;
//}
//
//
///*
//  Every function in the jump table should default to calling this function,
//  and then replace itself with a version that doesn't call this function
//  anymore. If threading occurs and this function is hit multiple times. In
//  this case we ensure nothing gets through by using a mutex.
//*/
//static pthread_mutex_t init_mutex;
//
//static void init_api(void)
//{
//  // Mighte wan't to look into a futex, but mutex should be sufficient since
//  // this function should not be called multiple times.
//
//}
