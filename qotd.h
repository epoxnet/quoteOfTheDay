#ifndef __QOTD_H
#define __QOTD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <time.h>

#define QOTD_FILE "qotd.txt"

#define ERROR_MESSAGE "failed to allocate space for QOTD data. Exiting.\n"

#define SUCCESS 0
#define ERROR_CONDITION -1

typedef uint16_t buffersize_t;

typedef struct qotd_t
{

	uint16_t pos;
	uint16_t len;

} qotd_t;

#define BUFFERSIZE USHRT_MAX

#endif
