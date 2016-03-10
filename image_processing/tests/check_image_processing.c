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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(32 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(20 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(16 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(14 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(12 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(12 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(11 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(10 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(9 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(9 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(9 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(9 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(8 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(8 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(8 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(8 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(8 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(8 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(8 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(7 * sizeof(char), byte_count);

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
    check_val = -2147483648;
    byte_count = charcnta(check_val, base);
    ck_assert_uint_eq(6 * sizeof(char), byte_count);

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
  int test_val, base;
  char buff[256];
  char* test_val_str;

base = 2;
  {
    {
      test_val = INT_MIN;
      test_val_str = ip_itoa(test_val, buff, base);
      ck_assert_str_eq("10000000000000000000000000000000", test_val_str);
      test_val_str = NULL;
    }

    {
      test_val = INT_MAX;
      test_val_str = ip_itoa(test_val, buff, base);
      ck_assert_str_eq("1111111111111111111111111111111", test_val_str);
      test_val_str = NULL;
    }

    {
      test_val = -1;
      test_val_str = ip_itoa(test_val, buff, base);
      ck_assert_str_eq("11111111111111111111111111111111", test_val_str);
      test_val_str = NULL;
    }

    {
      test_val = 1;
      test_val_str = ip_itoa(test_val, buff, base);
      ck_assert_str_eq("1", test_val_str);
      test_val_str = NULL;
    }

    {
      test_val = -1024;
      test_val_str = ip_itoa(test_val, buff, base);
      ck_assert_str_eq("11111111111111111111110000000000", test_val_str);
      test_val_str = NULL;
    }
  }

  base = 10;
  {
    {
      test_val = 0;
      test_val_str = ip_itoa(test_val, buff, base);
      ck_assert_str_eq("0", test_val_str);
      test_val_str = NULL;
    }

    {
      test_val = INT_MAX;
      test_val_str = ip_itoa(test_val, buff, base);
      ck_assert_str_eq("2147483647", test_val_str);
      test_val_str = NULL;
    }

    {
      test_val = INT_MIN;
      test_val_str = ip_itoa(test_val, buff, base);
      ck_assert_str_eq("-2147483648", test_val_str);
      test_val_str = NULL;
    }

    {
      test_val = 50;
      test_val_str = ip_itoa(test_val, buff, base);
      ck_assert_str_eq("50", test_val_str);
      test_val_str = NULL;
    }

    {
      test_val = -50;
      test_val_str = ip_itoa(test_val, buff, base);
      ck_assert_str_eq("-50", test_val_str);
      test_val_str = NULL;
    }
  }
}
END_TEST

START_TEST(check_ncomp)
{
  int base;

  base = 2;
  {
    {
      char val[] = "11111111111111111111111111111111";
      char *val_comp = ncomp(val, base);
      ck_assert_str_eq("00000000000000000000000000000001", val_comp);
    }

    {
      char val[] = "00000000000000000000000000000000";
      char *val_comp = ncomp(val, base);
      ck_assert_str_eq("00000000000000000000000000000000", val_comp);
    }

    {
      char val[] = "11111111111111111111111111111110";
      char *val_comp = ncomp(val, base);
      ck_assert_str_eq("00000000000000000000000000000010", val_comp);
    }

    {
      char val[] = "00000000000000000000000000000001";
      char *val_comp = ncomp(val, base);
      ck_assert_str_eq("11111111111111111111111111111111", val_comp);
    }
  }

  base = 3;
  {
    {
      char val[] = "0000";
      char *val_comp = ncomp(val, base);
      ck_assert_str_eq("0000", val_comp);
    }

    {
      char val[] = "2020";
      char *val_comp = ncomp(val, base);
      ck_assert_str_eq("0210", val_comp);
    }

    {
      char val[] = "3020";
      char *val_comp = ncomp(val, base);
      ck_assert_ptr_eq(NULL, val_comp);
    }
  }

  base = 16;
  {
    {
      char val[] = "ffffffff";
      char *val_comp = ncomp(val, base);
      ck_assert_str_eq("00000001", val_comp);
    }

    {
      char val[] = "0000000f";
      char *val_comp = ncomp(val, base);
      ck_assert_str_eq("fffffff1", val_comp);
    }
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
