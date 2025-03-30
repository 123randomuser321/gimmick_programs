/*
	Free Cupholder, Linux Edition (FLTK 1.3.9)
	Based in part on the work of the FLTK project (http://www.fltk.org).
*/

/* Standard headers */
#include <fcntl.h>

/* Linux headers */
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/cdrom.h>

/* FLTK headers */
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

/* constants */
constexpr int WINDOWROOTX = 320;
constexpr int WINDOWROOTY = 130;
constexpr int DEFAULTWIDGETX = 80;
constexpr int DEFAULTWIDGETY = 30;
constexpr const char *FAILSTRING = "No Cupholder for you :(";
constexpr const char *SUCCSTRING = "Enjoy your Free Cupholder :)";

/* Static functions */
static void cb_okbutton(Fl_Widget *widget, void *data);
static bool ejectCDROM(void);


int main(int argc, char **argv)
{
	// Root window and boxes
	Fl_Window *windowroot = new Fl_Window(WINDOWROOTX, WINDOWROOTY, "Free Cupholder");
	Fl_Box *imgbox = new Fl_Box(10, 10, DEFAULTWIDGETX, DEFAULTWIDGETX);
	Fl_Box *textbox = new Fl_Box(imgbox->x() + imgbox->w(), imgbox->y(), WINDOWROOTX - 20 - imgbox->w(), imgbox->h());

	// try to eject, setup labels
	if (ejectCDROM()) {
		imgbox->label("@+9>");
		imgbox->labelcolor(FL_GREEN);
		textbox->label(SUCCSTRING);
	} else {
		imgbox->label("@+9circle");
		imgbox->labelcolor(FL_RED);
		textbox->label(FAILSTRING);
	}
	
	// ok button
	Fl_Button *okbutton = new Fl_Button((WINDOWROOTX - DEFAULTWIDGETX) / 2, imgbox->y() + imgbox->h(), DEFAULTWIDGETX, DEFAULTWIDGETY, "Okay");
	okbutton->callback(cb_okbutton, windowroot);
	
	// end and show
	windowroot->end();
	// suppress CLI args
	char *sargv[2] = { argv[0], NULL };
	windowroot->show(1, sargv);
	return Fl::run();
}

static void cb_okbutton(Fl_Widget *widget, void *data)
{
	// data is windowroot
	static_cast<Fl_Window *>(data)->hide();
	return;
}

static bool ejectCDROM(void)
{
	int drive;
	if ((drive = open("/dev/sr0", O_RDONLY | O_NONBLOCK)) == -1 || (drive = open("/dev/cdrom", O_RDONLY | O_NONBLOCK)) == -1) {
		return false;
	} else if (ioctl(drive, CDROMEJECT) != 0) {
		close(drive);
		return false;
	} else {
		close(drive);
		return true;
	}
}
