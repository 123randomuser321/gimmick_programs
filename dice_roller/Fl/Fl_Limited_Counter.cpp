/*
	SPDX-License-Identifer: 0BSD

	Fl_Limited_Counter (implementation):
	Subclass of Fl_Simple_Counter that can be scrolled on to change its value.
	
	Copyright (C) 2025 by Sembo Sadur <labmailssadur@gmail.com>
	
	Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
	
	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
	OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
	NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/* Internal headers */
#include "Fl_Limited_Counter.h"

/* Function definitions */

int Fl_Limited_Counter::handle(int event)
{
	switch (event) {
		case FL_MOUSEWHEEL:
		{
			int indicator = Fl::event_dy();
			if (indicator > 0 && value() > minimum()) {
				set_value(value() - step());
				//set_changed(); doesn't work as expected
				if (when() & FL_WHEN_CHANGED)
					do_callback();
				redraw();
				return 1;
			} else if (indicator < 0 && value() < maximum()) {
				set_value(value() + step());
				if (when() & FL_WHEN_CHANGED)
					do_callback();
				redraw();
				return 1;
			} else {
				//return 0; // fix other counters scrolling
				return 1;
			}
			break;
		}

		default:
		return Fl_Simple_Counter::handle(event);
		break;
	}
	return 0;
}
