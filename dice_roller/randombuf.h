/*
	SPDX-License-Identifer: 0BSD

	randombuf (header):
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

#ifndef MEEEBLIB_RANDOM_H
#define MEEEBLIB_RANDOM_H
#ifdef __cplusplus
extern "C" {
#endif


/* Standard headers */
#include <stddef.h>

/*
	Write bufsize bytes into buffer starting at buf.
*/
void fillrandombuf(void *buf, size_t bufsize);


#ifdef __cplusplus
}
#endif
#endif
