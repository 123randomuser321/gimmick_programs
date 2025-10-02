/*
	SPDX-License-Identifer: 0BSD

	reshandler (header):
	Rudimentary resource handler for embedded (by ld) PNGs
	
	Copyright (C) 2025 by Sembo Sadur <labmailssadur@gmail.com>
	
	Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
	
	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
	OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
	NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef RESHANDLER_H
#define RESHANDLER_H
#ifdef __cplusplus
extern "C" {
#endif


/* PNGs */
#define PNG_BUTTROLL		1U
#define PNG_D4				2U
#define PNG_D6				3U
#define PNG_D8				4U
#define PNG_D10				5U
#define PNG_D12				6U
#define PNG_D20				7U
#define PNG_D100			8U
#define PNG_ICON			PNG_D6

#include <stddef.h>
#include <stdint.h>

struct resPNG {
	const unsigned char *data;
	size_t size;
};

struct resPNG getPNG(uint8_t index);


#ifdef __cplusplus
}
#endif
#endif
