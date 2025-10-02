/*
	SPDX-License-Identifer: 0BSD

	randombuf (implementation):
	Fill an arbitrarily-sized buffer with random bytes.
	May or may not use OS-specific randomness.
	
	Copyright (C) 2025 by Sembo Sadur <labmailssadur@gmail.com>
	
	Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
	
	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
	OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
	NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
	TODO:
	__WIN32 --> static NULLed bcrypt provider, check in fillrandombug, then set bool to skip, register atexit() for closing provider
*/

/* What headers? */
#ifndef NO_SYSTEM_RANDOM
#ifdef __linux
#define LINUX_RANDOM
#include <sys/random.h>
#include <stdio.h>
#endif
#else
#include <time.h>
#include <stdlib.h>
#include <string.h>
#endif

/* Internal headers */
#include "randombuf.h"

/* Function definitions */

void fillrandombuf(void *buf, size_t bufsize)
{
	#ifdef LINUX_RANDOM
	if (getrandom(buf, bufsize, 0) == -1) // this also supresses a warning
		fprintf(stderr, "%s:%u%s: getrandom() error.", __FILE__, __LINE__, __func__);
	#else
	static unsigned int seed;
	static int res;
	static size_t offset;
	offset = 0; // please do not optimize this away :(
	while (offset < bufsize) {
		seed += time(NULL);
		res = rand();
		seed += res;
		if (bufsize - offset > sizeof(int)) {
			strncpy((char *) buf + offset, (char *) &res, sizeof(int));
			offset += sizeof(int);
		} else {
			strncpy((char *) buf + offset, (char *) &res, bufsize - offset);
			offset = bufsize;
		}
	}
	#endif
	return;
}
