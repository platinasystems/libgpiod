// SPDX-License-Identifier: LGPL-2.1-or-later
/*
 * This file is part of libgpiod.
 *
 * Copyright (C) 2017-2018 Bartosz Golaszewski <bartekgola@gmail.com>
 */

/* Test cases for the gpiofind program. */

#include <stdio.h>

#include "gpiod-test.h"

static void gpiofind_found(void)
{
	test_tool_run("gpiofind", "gpio-mockup-B-7", (char *)NULL);
	test_tool_wait();

	TEST_ASSERT(test_tool_exited());
	TEST_ASSERT_RET_OK(test_tool_exit_status());
	TEST_ASSERT_NOT_NULL(test_tool_stdout());
	TEST_ASSERT_STR_EQ(test_tool_stdout(),
			   test_build_str("%s 7\n", test_chip_name(1)));
	TEST_ASSERT_NULL(test_tool_stderr());
}
TEST_DEFINE(gpiofind_found,
	    "tools: gpiofind - found",
	    TEST_FLAG_NAMED_LINES, { 4, 8 });

static void gpiofind_not_found(void)
{
	test_tool_run("gpiofind", "nonexistent", (char *)NULL);
	test_tool_wait();

	TEST_ASSERT(test_tool_exited());
	TEST_ASSERT_EQ(test_tool_exit_status(), 1);
	TEST_ASSERT_NULL(test_tool_stdout());
	TEST_ASSERT_NULL(test_tool_stderr());
}
TEST_DEFINE(gpiofind_not_found,
	    "tools: gpiofind - not found",
	    TEST_FLAG_NAMED_LINES, { 4, 8 });

static void gpiofind_invalid_args(void)
{
	test_tool_run("gpiofind", (char *)NULL);
	test_tool_wait();

	TEST_ASSERT(test_tool_exited());
	TEST_ASSERT_EQ(test_tool_exit_status(), 1);
	TEST_ASSERT_NULL(test_tool_stdout());
	TEST_ASSERT_NOT_NULL(test_tool_stderr());
	TEST_ASSERT_STR_CONTAINS(test_tool_stderr(),
				 "exactly one GPIO line name must be specified");

	test_tool_run("gpiofind", "first argument",
			  "second argument", (char *)NULL);
	test_tool_wait();

	TEST_ASSERT(test_tool_exited());
	TEST_ASSERT_EQ(test_tool_exit_status(), 1);
	TEST_ASSERT_NULL(test_tool_stdout());
	TEST_ASSERT_NOT_NULL(test_tool_stderr());
	TEST_ASSERT_STR_CONTAINS(test_tool_stderr(),
				 "exactly one GPIO line name must be specified");
}
TEST_DEFINE(gpiofind_invalid_args,
	    "tools: gpiofind - invalid arguments",
	    0, { });
