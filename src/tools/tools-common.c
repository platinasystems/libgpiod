/*
 * Common code for GPIO tools.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 */

#include <gpiod.h>
#include "tools-common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <libgen.h>

#define NORETURN		__attribute__((noreturn))

static char *progname = "unknown";

void set_progname(char *name)
{
	progname = name;
}

const char * get_progname(void)
{
	return progname;
}

void NORETURN PRINTF(1, 2) die(const char *fmt, ...)
{
	va_list va;

	va_start(va, fmt);
	fprintf(stderr, "%s: ", progname);
	vfprintf(stderr, fmt, va);
	fprintf(stderr, "\n");
	va_end(va);

	exit(EXIT_FAILURE);
}

void NORETURN PRINTF(1, 2) die_perror(const char *fmt, ...)
{
	va_list va;

	va_start(va, fmt);
	fprintf(stderr, "%s: ", progname);
	vfprintf(stderr, fmt, va);
	fprintf(stderr, ": %s\n", gpiod_last_strerror());
	va_end(va);

	exit(EXIT_FAILURE);
}

void print_version(void)
{
	char *prog, *tmp;

	tmp = strdup(progname);
	if (!tmp)
		prog = progname;
	else
		prog = basename(tmp);

	printf("%s (libgpiod) %s\n", prog, gpiod_version_string());
	printf("Copyright (C) 2017 Bartosz Golaszewski\n");
	printf("License: LGPLv2.1\n");
	printf("This is free software: you are free to change and redistribute it.\n");
	printf("There is NO WARRANTY, to the extent permitted by law.\n");

	if (tmp)
		free(tmp);
}
