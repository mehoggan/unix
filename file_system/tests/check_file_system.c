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

#include <check.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/filename.h"

START_TEST(test_filename_create)
{
  filename_t file = filename_create("frog");
  ck_assert_str_eq("frog", file.name);
  filename_free(&file);
  ck_assert_msg(file.name == NULL, "Fee'g a filename_t should have its"
    " member variables unallocated");

  // TODO: Test case where we run out of memory.
}
END_TEST

START_TEST(test_filename_ptr_create)
{
  filename_t *file = filename_ptr_create("frog");
  ck_assert_str_eq("frog", file->name);
  filename_ptr_free(&file);
  ck_assert_msg(file == NULL, "Free'g a filename_t* should be set to NULL.");

  file = filename_ptr_create(NULL);
  ck_assert_msg(file->name == NULL, "Creating a NULL filename_t * with an NULL"
    " name is valid");
  filename_ptr_free(&file);
  ck_assert_msg(file == NULL, "Though its name was NULL we still need to free"
    " a filename_t ptr.");

  // TODO: Test case where we run out of memory.
}
END_TEST

START_TEST(test_filename_is_valid)
{
  filename_t *file = NULL;
  ck_assert_msg(0 == filename_is_valid(file), "A NULL file is never valid.");

  file = (filename_t *)malloc(sizeof(filename_t));
  file->name = NULL;
  ck_assert_msg(0 == filename_is_valid(file), "A file with a NULL name is"
    " never valid");
  free(file);
  file = NULL;

  // +2 for the `\0` character.
  char buf[PATH_MAX + 2];
  memset(buf, 'a', sizeof(buf));
  buf[PATH_MAX + 1] = '\0'; // +1 because indexes start at 0.
  file = filename_ptr_create(&buf[0]);
  ck_assert_msg(0 == filename_is_valid(file), "A file over PATH_MAX is never"
    " valid.");
  filename_ptr_free(&file);

  file = filename_ptr_create("fr/og");
  ck_assert_str_eq("fr/og", file->name);
  ck_assert_msg(0 == filename_is_valid(file), "A filename with a / is never"
    " valid.");
  filename_ptr_free(&file);

  file = filename_ptr_create("frog");
  ck_assert_str_eq("frog", file->name);
  ck_assert_int_eq(1, filename_is_valid(file));
  filename_ptr_free(&file);
}
END_TEST

START_TEST(test_filename_dup)
{
  filename_t file;
  file.name = NULL;

  filename_t dup = filename_dup(&file);
  ck_assert_msg(NULL == dup.name, "Duplicating a filename that has not been"
    " properly created should return a filename_t with a NULL name");

  file = filename_create("frog");
  dup = filename_dup(&file);
  ck_assert_str_eq("frog", dup.name);
  ck_assert_str_eq(file.name, dup.name);
  filename_free(&file);
  filename_free(&dup);

  filename_t *fileptr = NULL;
  dup = filename_dup(fileptr);
  ck_assert_msg(NULL == dup.name, "Duplicating a filename_t * that is NULL"
    " shall return a filename_t whoes member variable name is NULL too.");
}
END_TEST

START_TEST(test_filename_ptr_dup)
{
  filename_t *file;
  filename_t *dup;

  file = NULL;
  dup = filename_ptr_dup(file);
  ck_assert_msg(NULL == dup, "Duplicating a filename_t * that is NULL shall"
    " return a filename_t * that is NULL");

  file = filename_ptr_create(NULL);
  dup = filename_ptr_dup(file);
  ck_assert_msg(dup != NULL, "We just duplicated a filename with no name.");
  ck_assert_msg(dup->name == NULL, "Creating a file with a NULL name, then"
    "duplicating it shall return a filename with a NULL name too.");
  filename_ptr_free(&file);
  filename_ptr_free(&dup);

  file = filename_ptr_create("frog");
  dup = filename_ptr_dup(file);
  ck_assert_str_eq("frog", dup->name);
  ck_assert_str_eq(file->name, dup->name);
  filename_ptr_free(&file);
  filename_ptr_free(&dup);
}
END_TEST

START_TEST(test_filename_app)
{
  filename_t file;

  // Just to check for crashes. No actual unit test.
  filename_app(NULL, "frog");

  file = filename_create("frog");

  filename_app(&file, NULL);
  ck_assert_str_eq("frog", file.name);
  filename_app(&file, ".ext");
  ck_assert_str_eq("frog.ext", file.name);

  filename_free(&file);
}
END_TEST

START_TEST(test_filename_ptr_app)
{
  filename_t *file;

  file = filename_ptr_create("frog");

  filename_ptr_app(&file, ".ext");
  ck_assert_str_eq("frog.ext", file->name);
  filename_ptr_free(&file);
}
END_TEST

START_TEST(test_filename_has_extension)
{
  filename_t file;

  file.name = NULL;

  ck_assert_int_eq(0, filename_has_extension(NULL));
  ck_assert_int_eq(0, filename_has_extension(&file));

  file = filename_create("frog");
  ck_assert_int_eq(0, filename_has_extension(&file));
  filename_free(&file);

  file = filename_create("..out");
  ck_assert_int_eq(1, filename_has_extension(&file));
  filename_free(&file);

  file = filename_create("frog.1out");
  ck_assert_int_eq(0, filename_has_extension(&file));
  filename_free(&file);

  file = filename_create("frog.");
  ck_assert_int_eq(0, filename_has_extension(&file));
  filename_free(&file);

  file = filename_create("frog.text");
  ck_assert_int_eq(1, filename_has_extension(&file));
  filename_free(&file);

  file = filename_create("frog.te");
  ck_assert_int_eq(0, filename_has_extension(&file));
  filename_free(&file);
}
END_TEST

START_TEST(test_filename_get_extension)
{
  filename_t file;

  file = filename_create("frog.txt");
  char *ext = filename_get_extension(&file);
  ck_assert_str_eq(".txt", ext);
  ck_assert_int_eq(4, strlen(ext));
  free(ext);
  filename_free(&file);
}
END_TEST

Suite *file_system_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("File System");
  tc_core = tcase_create("Core");

  // Add test cases from above between HERE ...
  tcase_add_test(tc_core, test_filename_create);
  tcase_add_test(tc_core, test_filename_ptr_create);
  tcase_add_test(tc_core, test_filename_is_valid);
  tcase_add_test(tc_core, test_filename_dup);
  tcase_add_test(tc_core, test_filename_ptr_dup);
  tcase_add_test(tc_core, test_filename_app);
  tcase_add_test(tc_core, test_filename_ptr_app);
  tcase_add_test(tc_core, test_filename_has_extension);
  tcase_add_test(tc_core, test_filename_get_extension);
  // and HERE

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = file_system_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
