/*
 * This file is part of libgpiod.
 *
 * Copyright (C) 2017-2018-2018 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 */

/* Common code for GPIO tools. */

#include <gpiod.h>
#include "tools-common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <libgen.h>
#include <errno.h>

const char * get_progname(void)
{
	return program_invocation_name;
}

void die(const char *fmt, ...)
{
	va_list va;

	va_start(va, fmt);
	fprintf(stderr, "%s: ", program_invocation_name);
	vfprintf(stderr, fmt, va);
	fprintf(stderr, "\n");
	va_end(va);

	exit(EXIT_FAILURE);
}

void die_perror(const char *fmt, ...)
{
	va_list va;

	va_start(va, fmt);
	fprintf(stderr, "%s: ", program_invocation_name);
	vfprintf(stderr, fmt, va);
	fprintf(stderr, ": %s\n", strerror(errno));
	va_end(va);

	exit(EXIT_FAILURE);
}

void print_version(void)
{
	printf("%s (libgpiod) %s\n",
	       program_invocation_short_name, gpiod_version_string());
	printf("Copyright (C) 2017-2018-2018 Bartosz Golaszewski\n");
	printf("License: LGPLv2.1\n");
	printf("This is free software: you are free to change and redistribute it.\n");
	printf("There is NO WARRANTY, to the extent permitted by law.\n");
}
