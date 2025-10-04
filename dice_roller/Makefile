#	SPDX-License-Identifer: 0BSD
#
#	Dice Roller: rolls dice
#	(Makefile)
#
#	Copyright (C) 2025 by Sembo Sadur <labmailssadur@gmail.com>
#	
#	Permission to use, copy, modify, and/or distribute this software for any purpose with or without fee is hereby granted.
#	
#	THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
#	WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.
#	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
#	OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
#	NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#

.PHONY: all clean Fl
.DEFAULT_GOAL = all

override CXXFLAGS += $(shell fltk-config --use-images --cxxflags) -I. -I./Fl -I../cp2020chargen
# FLTK member objects may emit an 'unused variable' warning
ifneq ($(DEBUG),)
	override CXXFLAGS += -g -Wall -Werror -Wno-error=unused-variable
endif

LIBFLAGS = -L./Fl -lFl -lm

ifeq ($(PLATFORM), win32)
	EXESUFFIX = .exe
	LIBFLAGS += -lbcrypt
else
	EXESUFFIX =
endif

override LDFLAGS += $(shell fltk-config --use-images --ldstaticflags) $(LIBFLAGS)

ifneq ($(NO_SYSTEM_RANDOM),)
	DEFINES = -D NO_SYSTEM_RANDOM=1
else
	DEFINES =
endif

NAME = dice_roller
TARGET = $(NAME)$(EXESUFFIX)
OBJECTS = main.cpp.o randombuf.c.o reshandler.c.o images.o
ICONS = $(wildcard data/*.png)
# this supresses a warning for a circular dependency on the icon
%: %.o

$(TARGET): $(OBJECTS) Fl
Fl:
	$(MAKE) -C Fl PLATFORM=$(PLATFORM) DEBUG=$(DEBUG)

%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEFINES) -c $^ -o $@

%.c.o: %.c
	$(CXX) $(CXXFLAGS) $(DEFINES) -c $^ -o $@

main.cpp: images.o
images.o:
	$(LD) -o $@ -b binary -r $(ICONS)

all: $(TARGET)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

clean:
	-rm $(OBJECTS)
	-rm $(TARGET)
	$(MAKE) -C Fl clean PLATFORM=$(PLATFORM)
