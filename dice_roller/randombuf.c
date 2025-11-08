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

/* What headers? */
#ifndef NO_SYSTEM_RANDOM
#ifdef __linux
#define LINUX_RANDOM
#include <sys/random.h>
#include <stdio.h>
#elif defined(__WIN32)
#define MSWIN_RANDOM
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ntstatus.h>
#include <bcrypt.h>
#include <stdio.h>
#include <stdlib.h>
#else
#error "Unrecognized OS. Pass NO_SYSTEM_RANDOM=1 (i.e. make NO_SYSTEM_RANDOM=1 [...]) to build."
#endif
#else
#include <time.h>
#include <stdlib.h>
#include <string.h>
#endif

/* Internal headers */
#include "randombuf.h"

/* Windows stuff */
#ifdef MSWIN_RANDOM
static BCRYPT_ALG_HANDLE alg = NULL;
static BOOL bSetupDone = FALSE;

static void CloseALG(void)
{
	BCryptCloseAlgorithmProvider(alg, 0);
	return;
}
#endif

/* Function definitions */

void fillrandombuf(void *buf, size_t bufsize)
{
	#ifdef LINUX_RANDOM
	if (getrandom(buf, bufsize, 0) == -1) // this also supresses a warning
		fprintf(stderr, "%s:%u:%s: getrandom() error.\n", __FILE__, __LINE__, __func__);
	#elif defined(MSWIN_RANDOM)
	if (bSetupDone == FALSE && alg == NULL) {
		NTSTATUS err = BCryptOpenAlgorithmProvider(&alg, BCRYPT_RNG_ALGORITHM, MS_PRIMITIVE_PROVIDER, 0);
		if (err != STATUS_SUCCESS)
			fprintf(stderr, "%s:%u:%s: BCryptOpenAlgorithmProvider() error: %d\n", __FILE__, __LINE__, __func__, err);
		else
			atexit(CloseALG);
		bSetupDone = TRUE;
	}
	BCryptGenRandom(alg, (PUCHAR) buf, bufsize, 0);
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
			memcpy((char *) buf + offset, (char *) &res, sizeof(int));
			offset += sizeof(int);
		} else {
			memcpy((char *) buf + offset, (char *) &res, bufsize - offset);
			offset = bufsize;
		}
	}
	#endif
	return;
}
