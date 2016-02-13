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
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../src/utils.h"
#include "../src/image_processing.h"

START_TEST(check_parse_args)
{
  int argc;

  char *dest = get_exe_path();

  {
    char *argv[] = {dest, 0};
    argc = sizeof(argv) / sizeof(argv[1]) - 1;
    ck_assert_int_eq(-1, argparse(argc, argv));
  }

  {
    char *argv[] = {dest, "-f", 0};
    argc = sizeof(argv) / sizeof(argv[1]) - 1;
    ck_assert_int_eq(-1, argparse(argc, argv));
  }

  {
    char *argv[] = {dest, "-f", "/dev/null", 0};
    argc = sizeof(argv) / sizeof(argv[1]) - 1;
    ck_assert_int_eq(0, argparse(argc, argv));
  }

  {
    char *argv[] = {dest, "--file", "/dev/null", 0};
    argc = sizeof(argv) / sizeof(argv[1]) - 1;
    ck_assert_int_eq(0, argparse(argc, argv));
  }

  {
    char *argv[] = {dest, "-d", 0};
    argc = sizeof(argv) / sizeof(argv[1]) - 1;
    ck_assert_int_eq(-1, argparse(argc, argv));
  }

  // TODO: These should fail due to permissions.
//  {
//    char *argv[] = {dest, "-d", "/dev", 0};
//    argc = sizeof(argv) / sizeof(argv[1]) - 1;
//    ck_assert_int_eq(0, argparse(argc, argv));
//  }
//
//  {
//    char *argv[] = {dest, "--dir", "/", 0};
//    argc = sizeof(argv) / sizeof(argv[1]) - 1;
//    ck_assert_int_eq(0, argparse(argc, argv));
//  }

  free(dest);
}
END_TEST

START_TEST(check_itoa)
{
  int test_val;
  char *test_val_str;

  {
    test_val = 0;
    test_val_str = itoa(test_val);
    ck_assert_str_eq("0", test_val_str);
    free(test_val_str);
    test_val_str = NULL;
  }

  {
    test_val = INT_MAX;
    test_val_str = itoa(test_val);
    ck_assert_str_eq("2147483647", test_val_str);
    free(test_val_str);
    test_val_str = NULL;
  }

  {
    test_val = INT_MIN;
    test_val_str = itoa(test_val);
    ck_assert_str_eq("-2147483648", test_val_str);
    free(test_val_str);
    test_val_str = NULL;
  }

}
END_TEST

START_TEST(check_get_exe_path)
{
}
END_TEST

Suite *image_processing_suite(void)
{
  Suite *s;
  TCase *tc_core;

  s = suite_create("Image Processing");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, check_parse_args);
  tcase_add_test(tc_core, check_itoa);
  tcase_add_test(tc_core, check_get_exe_path);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void)
{
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = image_processing_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
