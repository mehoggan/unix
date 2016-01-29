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
#include <stdlib.h>
#include <unistd.h>

#include "../src/file_name.h"

START_TEST(test_filename_create)
{
  filename *file = filename_create("frog");
  ck_assert_str_eq("frog", file->name);
  filename_free(&file);
  ck_assert_msg(file == NULL, "one free filename should be set to null.");
}
END_TEST

START_TEST(test_filename_is_valid)
{
  filename *file = filename_create("frog");
  ck_assert_str_eq("frog", file->name);
  ck_assert_int_eq(1, filename_is_valid(file));
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
  tcase_add_test(tc_core, test_filename_is_valid);
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
