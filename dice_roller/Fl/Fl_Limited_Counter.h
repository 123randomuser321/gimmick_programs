/*
	SPDX-License-Identifer: 0BSD

	Fl_Limited_Counter (header):
	Subclass of Fl_Simple_Counter that can be scrolled on to change its value.
	
	Copyright (C) 2025 by Sembo Sadur <labmailssadur@gmail.com>
	
	Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
	
	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
	OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
	NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef Fl_Limited_Counter_H
#define Fl_Limited_Counter_H


/* FLTK headers */
#include <Fl/Fl.H>
#include <Fl/Fl_Simple_Counter.H>

class Fl_Limited_Counter : public Fl_Simple_Counter {
	public:
	Fl_Limited_Counter(int x, int y, int w, int h, double min = 0.0, double max = 100.0, const char *label = 0)
	: Fl_Simple_Counter(x, y, w, h, label)
	{
		minimum(min);
		maximum(max);
		value(min);
	}
	virtual int handle(int event);
};


#endif
