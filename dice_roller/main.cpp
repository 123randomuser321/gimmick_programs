/*
	SPDX-License-Identifer: 0BSD

	Dice Roller: rolls dice
	Main + UI
	This program is based in part on the work of the FLTK project (http://www.fltk.org).
	
	Copyright (C) 2025 by Sembo Sadur <labmailssadur@gmail.com>
	
	Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
	
	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
	OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
	NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/* Standard headers */
#include <cstdint>
#include <cstdio>
#include <cmath>

/* FLTK headers */
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include "Fl/Fl_Limited_Counter.h"
#include <Fl/Fl_Output.H>
#include <Fl/Fl_PNG_Image.H>

/* Internal headers */
#include "randombuf.h"
#include "reshandler.h"

/* Constants */
constexpr int WINDOWW = 320;
constexpr int WINDOWH = 110 + 52;
constexpr int WIDGETH = 30;
constexpr uint8_t OBUFSIZE = 4; // buf in cbRoll is uint8_t

/* There must be smarter solution */
static double arrDX[] = {4.0, 6.0, 8.0, 10.0, 12.0, 20.0, 100.0};

static struct {
	Fl_Limited_Counter *counter;
	Fl_Output *output;
} w2;

/* Callbacks */
static void cbRoll(Fl_Widget *widget, void *data);
static void cbDX(Fl_Widget *widget, void *data);

int main(int argc, char **argv)
{
	Fl_Window *windowmain = new Fl_Window(WINDOWW, WINDOWH, "Dice Roller");
	Fl_Limited_Counter *countereyes = new Fl_Limited_Counter(10, 10, 120, WIDGETH, 1.0, 100.0, "EYES");
	countereyes->value(10.0);
	countereyes->step(1.0);
	countereyes->labelfont(FL_BOLD);
	countereyes->tooltip("This sets the number of eyes the 'dice' has.");
	countereyes->when(FL_WHEN_CHANGED);
	Fl_Button *buttonroll = new Fl_Button(countereyes->x() + (countereyes->w() - WIDGETH) / 2, countereyes->y() + countereyes->h() + 20, WIDGETH, WIDGETH);
	struct resPNG PNGholder = getPNG(PNG_BUTTROLL);
	Fl_PNG_Image *pngbuttonroll = new Fl_PNG_Image(NULL, PNGholder.data, PNGholder.size);
	buttonroll->image(pngbuttonroll);
	buttonroll->tooltip("Roll the dice!");
	Fl_Output *outroll = new Fl_Output(countereyes->x() + countereyes->w() + 10, countereyes->y(), WINDOWW - countereyes->x() - countereyes->w() - 10 - 10, WIDGETH * 3);
	outroll->textsize(outroll->h());

	w2.counter = countereyes;
	w2.output = outroll;
	buttonroll->callback(cbRoll);

	Fl_Button *buttond4 = new Fl_Button(10, outroll->y() + outroll->h() + 10, 42, 42);
	PNGholder = getPNG(PNG_D4);
	Fl_PNG_Image *pngd4 = new Fl_PNG_Image(NULL, PNGholder.data, PNGholder.size);
	buttond4->image(pngd4);
	buttond4->callback(cbDX, &arrDX[0]);
	Fl_Button *buttond6 = new Fl_Button(buttond4->x() + buttond4->w() + 1, buttond4->y(), 42, 42);
	PNGholder = getPNG(PNG_D6);
	Fl_PNG_Image *pngd6 = new Fl_PNG_Image(NULL, PNGholder.data, PNGholder.size);
	buttond6->image(pngd6);
	buttond6->callback(cbDX, &arrDX[1]);
	Fl_Button *buttond8 = new Fl_Button(buttond6->x() + buttond6->w() + 1, buttond4->y(), 42, 42);
	PNGholder = getPNG(PNG_D8);
	Fl_PNG_Image *pngd8 = new Fl_PNG_Image(NULL, PNGholder.data, PNGholder.size);
	buttond8->image(pngd8);
	buttond8->callback(cbDX, &arrDX[2]);
	Fl_Button *buttond10 = new Fl_Button(buttond8->x() + buttond8->w() + 1, buttond4->y(), 42, 42);
	PNGholder = getPNG(PNG_D10);
	Fl_PNG_Image *pngd10 = new Fl_PNG_Image(NULL, PNGholder.data, PNGholder.size);
	buttond10->image(pngd10);
	buttond10->callback(cbDX, &arrDX[3]);
	Fl_Button *buttond12 = new Fl_Button(buttond10->x() + buttond10->w() + 1, buttond4->y(), 42, 42);
	PNGholder = getPNG(PNG_D12);
	Fl_PNG_Image *pngd12 = new Fl_PNG_Image(NULL, PNGholder.data, PNGholder.size);
	buttond12->image(pngd12);
	buttond12->callback(cbDX, &arrDX[4]);
	Fl_Button *buttond20 = new Fl_Button(buttond12->x() + buttond12->w() + 1, buttond4->y(), 42, 42);
	PNGholder = getPNG(PNG_D20);
	Fl_PNG_Image *pngd20 = new Fl_PNG_Image(NULL, PNGholder.data, PNGholder.size);
	buttond20->image(pngd20);
	buttond20->callback(cbDX, &arrDX[5]);
	Fl_Button *buttond100 = new Fl_Button(buttond20->x() + buttond20->w() + 1, buttond4->y(), 42, 42);
	PNGholder = getPNG(PNG_D100);
	Fl_PNG_Image *pngd100 = new Fl_PNG_Image(NULL, PNGholder.data, PNGholder.size);
	buttond100->image(pngd100);
	buttond100->callback(cbDX, &arrDX[6]);

	PNGholder = getPNG(PNG_ICON);
	Fl_PNG_Image *pngicon = new Fl_PNG_Image(NULL, PNGholder.data, PNGholder.size);
	windowmain->icon(pngicon);
	windowmain->end();
	windowmain->show();
	return Fl::run();
}

static void cbRoll(Fl_Widget *widget, void *data)
{
	static uint8_t buf = 0;
	static char outputbuf[OBUFSIZE];
	fillrandombuf(&buf, sizeof(uint8_t));
	buf = buf % static_cast<uint8_t>(floor(w2.counter->value())) + 1;
	snprintf(outputbuf, OBUFSIZE, "%u", buf);
	w2.output->value(outputbuf);
	return;
}

static void cbDX(Fl_Widget *widget, void *data)
{
	w2.counter->value(* (double *) data);
	w2.counter->redraw();
	return;
}
