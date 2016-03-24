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
/*
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
*/
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
/*
  free(dest);
*/
}
END_TEST

START_TEST(check_charcnta)
{
  int check_val;
  int base;
  size_t byte_count;
  size_t digit_count;
  short index;

  base = 2;
  {
    check_val = 2147483647;
    digit_count = 31;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count * sizeof(char), byte_count);
      check_val /= base;
      --digit_count;
    }
  }

  base = 3;
  {
    check_val = 2147483647;
    digit_count = 20;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 4;
  {
    check_val = 2147483647;
    digit_count = 16;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 5;
  {
    check_val = 2147483647;
    digit_count = 14;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 6;
  {
    check_val = 2147483647;
    digit_count = 12;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 7;
  {
    check_val = 2147483647;
    digit_count = 12;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 8;
  {
    check_val = 2147483647;
    digit_count = 11;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 9;
  {
    check_val = 2147483647;
    digit_count = 10;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 10; // Special exception for the '-' ASCII character.
  {
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(11 * sizeof(char), byte_count);

    check_val = -83648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(6 * sizeof(char), byte_count);

    check_val = 0;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(1 * sizeof(char), byte_count);

    check_val = 2147483647;
    digit_count = 10;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 11;
  {
    check_val = 2147483647;
    digit_count = 9;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 12;
  {
    check_val = 2147483647;
    digit_count = 9;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 13;
  {
    check_val = 2147483647;
    digit_count = 9;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 14;
  {
    check_val = 2147483647;
    digit_count = 9;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 15;
  {
    check_val = 2147483647;
    digit_count = 8;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 16;
  {
    check_val = 2147483647;
    digit_count = 8;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 17;
  {
    check_val = 2147483647;
    digit_count = 8;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 18;
  {
    check_val = 2147483647;
    digit_count = 8;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 19;
  {
    check_val = 2147483647;
    digit_count = 8;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 20;
  {
    check_val = 2147483647;
    digit_count = 8;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 21;
  {
    check_val = 2147483647;
    digit_count = 8;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 22;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 23;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 24;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 25;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 26;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 27;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 28;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 29;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 30;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 32;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 33;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 34;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 35;
  {
    check_val = 2147483647;
    digit_count = 7;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }

  base = 36;
  {
    check_val = 2147483647;
    digit_count = 6;
    index = 0;
    while (check_val) {
      byte_count = charcnta(check_val, base);
      ck_assert_uint_eq(digit_count, byte_count);
      check_val /= base;
      --digit_count;
      ++index;
    }
  }
}
END_TEST

START_TEST(check_itoa)
{
/*
  int test_val, base;
  char buff[256];
  char* test_val_str;
*/
}
END_TEST

START_TEST(check_ncomp)
{
  size_t len, index;

  struct
  {
    int base;
    const char *val1;
    const char *val2;
  } test_vals[] = {{2, "000", "000"}, {2, "001", "111"}};

  len = sizeof(test_vals) / sizeof(test_vals[0]);

  for (index = 0; index < len; ++index) {
    char *val1_dup = strdup(test_vals[index].val1);
    char *val2_dup = strdup(test_vals[index].val2);

    free(val1_dup);
    free(val2_dup);
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
  tcase_add_test(tc_core, check_charcnta);
  tcase_add_test(tc_core, check_ncomp);
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
