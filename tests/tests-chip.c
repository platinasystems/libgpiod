// SPDX-License-Identifier: LGPL-2.1-or-later
/*
 * This file is part of libgpiod.
 *
 * Copyright (C) 2017-2018 Bartosz Golaszewski <bartekgola@gmail.com>
 */

/* Test cases for GPIO chip handling. */

#include <errno.h>
#include <stdio.h>

#include "gpiod-test.h"

static void chip_open_good(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;

	chip = gpiod_chip_open(test_chip_path(0));
	TEST_ASSERT_NOT_NULL(chip);
}
TEST_DEFINE(chip_open_good,
	    "gpiod_chip_open() - good",
	    0, { 8 });

static void chip_open_nonexistent(void)
{
	struct gpiod_chip *chip;

	chip = gpiod_chip_open("/dev/nonexistent_gpiochip");
	TEST_ASSERT_NULL(chip);
	TEST_ASSERT_ERRNO_IS(ENOENT);
}
TEST_DEFINE(chip_open_nonexistent,
	    "gpiod_chip_open() - nonexistent chip",
	    0, { 8 });

static void chip_open_notty(void)
{
	struct gpiod_chip *chip;

	chip = gpiod_chip_open("/dev/null");
	TEST_ASSERT_NULL(chip);
	TEST_ASSERT_ERRNO_IS(ENOTTY);
}
TEST_DEFINE(chip_open_notty,
	    "gpiod_chip_open() - notty",
	    0, { 8 });

static void chip_open_by_name_good(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;

	chip = gpiod_chip_open_by_name(test_chip_name(0));
	TEST_ASSERT_NOT_NULL(chip);
}
TEST_DEFINE(chip_open_by_name_good,
	    "gpiod_chip_open_by_name() - good",
	    0, { 8 });

static void chip_open_by_number_good(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;

	chip = gpiod_chip_open_by_number(test_chip_num(0));
	TEST_ASSERT_NOT_NULL(chip);
}
TEST_DEFINE(chip_open_by_number_good,
	    "gpiod_chip_open_by_number() - good",
	    0, { 8 });

static void chip_open_lookup(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip_by_label = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip_by_name = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip_by_path = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip_by_num = NULL;

	chip_by_name = gpiod_chip_open_lookup(test_chip_name(1));
	chip_by_path = gpiod_chip_open_lookup(test_chip_path(1));
	chip_by_num = gpiod_chip_open_lookup(
				test_build_str("%u", test_chip_num(1)));
	chip_by_label = gpiod_chip_open_lookup("gpio-mockup-B");

	TEST_ASSERT_NOT_NULL(chip_by_name);
	TEST_ASSERT_NOT_NULL(chip_by_path);
	TEST_ASSERT_NOT_NULL(chip_by_num);
	TEST_ASSERT_NOT_NULL(chip_by_label);

	TEST_ASSERT_STR_EQ(gpiod_chip_name(chip_by_name), test_chip_name(1));
	TEST_ASSERT_STR_EQ(gpiod_chip_name(chip_by_path), test_chip_name(1));
	TEST_ASSERT_STR_EQ(gpiod_chip_name(chip_by_num), test_chip_name(1));
	TEST_ASSERT_STR_EQ(gpiod_chip_name(chip_by_label), test_chip_name(1));
}
TEST_DEFINE(chip_open_lookup,
	    "gpiod_chip_open_lookup() - good",
	    0, { 8, 8, 8 });

static void chip_open_by_label_good(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;

	chip = gpiod_chip_open_by_label("gpio-mockup-D");
	TEST_ASSERT_NOT_NULL(chip);
	TEST_ASSERT_STR_EQ(gpiod_chip_name(chip), test_chip_name(3));
}
TEST_DEFINE(chip_open_by_label_good,
	    "gpiod_chip_open_by_label() - good",
	    0, { 4, 4, 4, 4, 4 });

static void chip_open_by_label_bad(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;

	chip = gpiod_chip_open_by_label("nonexistent_gpio_chip");
	TEST_ASSERT_NULL(chip);
	TEST_ASSERT_ERRNO_IS(ENOENT);
}
TEST_DEFINE(chip_open_by_label_bad,
	    "gpiod_chip_open_by_label() - bad",
	    0, { 4, 4, 4, 4, 4 });

static void chip_name(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip0 = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip1 = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip2 = NULL;

	chip0 = gpiod_chip_open(test_chip_path(0));
	chip1 = gpiod_chip_open(test_chip_path(1));
	chip2 = gpiod_chip_open(test_chip_path(2));
	TEST_ASSERT_NOT_NULL(chip0);
	TEST_ASSERT_NOT_NULL(chip1);
	TEST_ASSERT_NOT_NULL(chip2);

	TEST_ASSERT_STR_EQ(gpiod_chip_name(chip0), test_chip_name(0));
	TEST_ASSERT_STR_EQ(gpiod_chip_name(chip1), test_chip_name(1));
	TEST_ASSERT_STR_EQ(gpiod_chip_name(chip2), test_chip_name(2));
}
TEST_DEFINE(chip_name,
	    "gpiod_chip_name()",
	    0, { 8, 8, 8 });

static void chip_label(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip0 = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip1 = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip2 = NULL;

	chip0 = gpiod_chip_open(test_chip_path(0));
	chip1 = gpiod_chip_open(test_chip_path(1));
	chip2 = gpiod_chip_open(test_chip_path(2));
	TEST_ASSERT_NOT_NULL(chip0);
	TEST_ASSERT_NOT_NULL(chip1);
	TEST_ASSERT_NOT_NULL(chip2);

	TEST_ASSERT_STR_EQ(gpiod_chip_label(chip0), "gpio-mockup-A");
	TEST_ASSERT_STR_EQ(gpiod_chip_label(chip1), "gpio-mockup-B");
	TEST_ASSERT_STR_EQ(gpiod_chip_label(chip2), "gpio-mockup-C");
}
TEST_DEFINE(chip_label,
	    "gpiod_chip_label()",
	    0, { 8, 8, 8 });

static void chip_num_lines(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip0 = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip1 = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip2 = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip3 = NULL;
	TEST_CLEANUP_CHIP struct gpiod_chip *chip4 = NULL;

	chip0 = gpiod_chip_open(test_chip_path(0));
	chip1 = gpiod_chip_open(test_chip_path(1));
	chip2 = gpiod_chip_open(test_chip_path(2));
	chip3 = gpiod_chip_open(test_chip_path(3));
	chip4 = gpiod_chip_open(test_chip_path(4));
	TEST_ASSERT_NOT_NULL(chip0);
	TEST_ASSERT_NOT_NULL(chip1);
	TEST_ASSERT_NOT_NULL(chip2);
	TEST_ASSERT_NOT_NULL(chip3);
	TEST_ASSERT_NOT_NULL(chip4);

	TEST_ASSERT_EQ(gpiod_chip_num_lines(chip0), 1);
	TEST_ASSERT_EQ(gpiod_chip_num_lines(chip1), 4);
	TEST_ASSERT_EQ(gpiod_chip_num_lines(chip2), 8);
	TEST_ASSERT_EQ(gpiod_chip_num_lines(chip3), 16);
	TEST_ASSERT_EQ(gpiod_chip_num_lines(chip4), 32);
}
TEST_DEFINE(chip_num_lines,
	    "gpiod_chip_num_lines()",
	    0, { 1, 4, 8, 16, 32 });

static void chip_get_lines(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;
	struct gpiod_line_bulk bulk;
	unsigned int offsets[4];
	struct gpiod_line *line;
	int rv;

	chip = gpiod_chip_open(test_chip_path(0));
	TEST_ASSERT_NOT_NULL(chip);

	offsets[0] = 1;
	offsets[1] = 3;
	offsets[2] = 4;
	offsets[3] = 7;

	rv = gpiod_chip_get_lines(chip, offsets, 4, &bulk);
	TEST_ASSERT_RET_OK(rv);

	TEST_ASSERT_EQ(gpiod_line_bulk_num_lines(&bulk), 4);
	line = gpiod_line_bulk_get_line(&bulk, 0);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 1);
	line = gpiod_line_bulk_get_line(&bulk, 1);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 3);
	line = gpiod_line_bulk_get_line(&bulk, 2);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 4);
	line = gpiod_line_bulk_get_line(&bulk, 3);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 7);
}
TEST_DEFINE(chip_get_lines,
	    "gpiod_chip_get_lines()",
	    0, { 16 });

static void chip_get_all_lines(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;
	struct gpiod_line_bulk bulk;
	struct gpiod_line *line;
	int rv;

	chip = gpiod_chip_open(test_chip_path(0));
	TEST_ASSERT_NOT_NULL(chip);

	rv = gpiod_chip_get_all_lines(chip, &bulk);
	TEST_ASSERT_RET_OK(rv);

	TEST_ASSERT_EQ(gpiod_line_bulk_num_lines(&bulk), 4);
	line = gpiod_line_bulk_get_line(&bulk, 0);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 0);
	line = gpiod_line_bulk_get_line(&bulk, 1);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 1);
	line = gpiod_line_bulk_get_line(&bulk, 2);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 2);
	line = gpiod_line_bulk_get_line(&bulk, 3);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 3);
}
TEST_DEFINE(chip_get_all_lines,
	    "gpiod_chip_get_all_lines()",
	    0, { 4 });

static void chip_find_line_good(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;
	struct gpiod_line *line;

	chip = gpiod_chip_open(test_chip_path(1));
	TEST_ASSERT_NOT_NULL(chip);

	line = gpiod_chip_find_line(chip, "gpio-mockup-B-4");
	TEST_ASSERT_NOT_NULL(line);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 4);
	TEST_ASSERT_STR_EQ(gpiod_line_name(line), "gpio-mockup-B-4");
}
TEST_DEFINE(chip_find_line_good,
	    "gpiod_chip_find_line() - good",
	    TEST_FLAG_NAMED_LINES, { 8, 8, 8 });

static void chip_find_line_not_found(void)
{
	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;
	struct gpiod_line *line;

	chip = gpiod_chip_open(test_chip_path(1));
	TEST_ASSERT_NOT_NULL(chip);

	line = gpiod_chip_find_line(chip, "nonexistent");
	TEST_ASSERT_NULL(line);
	TEST_ASSERT_ERRNO_IS(ENOENT);
}
TEST_DEFINE(chip_find_line_not_found,
	    "gpiod_chip_find_line() - not found",
	    TEST_FLAG_NAMED_LINES, { 8, 8, 8 });

static void chip_find_lines_good(void)
{
	static const char *names[] = { "gpio-mockup-B-3",
				       "gpio-mockup-B-6",
				       "gpio-mockup-B-7",
				       NULL };

	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;
	struct gpiod_line_bulk bulk;
	struct gpiod_line *line;
	int rv;

	chip = gpiod_chip_open(test_chip_path(1));
	TEST_ASSERT_NOT_NULL(chip);

	rv = gpiod_chip_find_lines(chip, names, &bulk);
	TEST_ASSERT_RET_OK(rv);
	TEST_ASSERT_EQ(gpiod_line_bulk_num_lines(&bulk), 3);
	line = gpiod_line_bulk_get_line(&bulk, 0);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 3);
	line = gpiod_line_bulk_get_line(&bulk, 1);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 6);
	line = gpiod_line_bulk_get_line(&bulk, 2);
	TEST_ASSERT_EQ(gpiod_line_offset(line), 7);
}
TEST_DEFINE(chip_find_lines_good,
	    "gpiod_chip_find_lines() - good",
	    TEST_FLAG_NAMED_LINES, { 8, 8, 8 });

static void chip_find_lines_not_found(void)
{
	static const char *names[] = { "gpio-mockup-B-3",
				       "nonexistent",
				       "gpio-mockup-B-7",
				       NULL };

	TEST_CLEANUP_CHIP struct gpiod_chip *chip = NULL;
	struct gpiod_line_bulk bulk;
	int rv;

	chip = gpiod_chip_open(test_chip_path(1));
	TEST_ASSERT_NOT_NULL(chip);

	rv = gpiod_chip_find_lines(chip, names, &bulk);
	TEST_ASSERT_EQ(rv, -1);
	TEST_ASSERT_ERRNO_IS(ENOENT);
}
TEST_DEFINE(chip_find_lines_not_found,
	    "gpiod_chip_find_lines() - not found",
	    TEST_FLAG_NAMED_LINES, { 8, 8, 8 });
