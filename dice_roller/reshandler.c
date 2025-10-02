/*
	SPDX-License-Identifer: 0BSD

	reshandler (implementation):
	Rudimentary resource handler for embedded (by ld) PNGs
	
	Copyright (C) 2025 by Sembo Sadur <labmailssadur@gmail.com>
	
	Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
	
	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
	OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
	NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "reshandler.h"

/* exported from images.o */
// icon.png
extern unsigned char _binary_data_icon_png_start[];
extern unsigned char _binary_data_icon_png_end[];
// buttroll.png
extern unsigned char _binary_data_buttroll_png_start[];
extern unsigned char _binary_data_buttroll_png_end[];
// dice_4.png
extern unsigned char _binary_data_dice_4_png_start[];
extern unsigned char _binary_data_dice_4_png_end[];
// dice_6.png
extern unsigned char _binary_data_dice_6_png_start[];
extern unsigned char _binary_data_dice_6_png_end[];
// dice_8.png
extern unsigned char _binary_data_dice_8_png_start[];
extern unsigned char _binary_data_dice_8_png_end[];
// dice_10.png
extern unsigned char _binary_data_dice_10_png_start[];
extern unsigned char _binary_data_dice_10_png_end[];
// dice_12.png
extern unsigned char _binary_data_dice_12_png_start[];
extern unsigned char _binary_data_dice_12_png_end[];
// dice_20.png
extern unsigned char _binary_data_dice_20_png_start[];
extern unsigned char _binary_data_dice_20_png_end[];
// dice_100.png
extern unsigned char _binary_data_dice_100_png_start[];
extern unsigned char _binary_data_dice_100_png_end[];

struct resPNG getPNG(uint8_t index)
{
	struct resPNG ret;
	switch (index) {
		case PNG_BUTTROLL:
		ret.data = _binary_data_buttroll_png_start;
		ret.size = (size_t) _binary_data_buttroll_png_end - (size_t) _binary_data_buttroll_png_start;
		break;

		case PNG_D4:
		ret.data = _binary_data_dice_4_png_start;
		ret.size = (size_t) _binary_data_dice_4_png_end - (size_t) _binary_data_dice_4_png_start;
		break;

		case PNG_D6:
		ret.data = _binary_data_dice_6_png_start;
		ret.size = (size_t) _binary_data_dice_6_png_end - (size_t) _binary_data_dice_6_png_start;
		break;

		case PNG_D8:
		ret.data = _binary_data_dice_8_png_start;
		ret.size = (size_t) _binary_data_dice_8_png_end - (size_t) _binary_data_dice_8_png_start;
		break;

		case PNG_D10:
		ret.data = _binary_data_dice_10_png_start;
		ret.size = (size_t) _binary_data_dice_10_png_end - (size_t) _binary_data_dice_10_png_start;
		break;

		case PNG_D12:
		ret.data = _binary_data_dice_12_png_start;
		ret.size = (size_t) _binary_data_dice_12_png_end - (size_t) _binary_data_dice_12_png_start;
		break;

		case PNG_D20:
		ret.data = _binary_data_dice_20_png_start;
		ret.size = (size_t) _binary_data_dice_20_png_end - (size_t) _binary_data_dice_20_png_start;
		break;

		case PNG_D100:
		ret.data = _binary_data_dice_100_png_start;
		ret.size = (size_t) _binary_data_dice_100_png_end - (size_t) _binary_data_dice_100_png_start;
		break;

		default:
		ret.data = NULL;
		ret.size = 0;
		break;
	}
	return ret;
}
