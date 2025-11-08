#	SPDX-License-Identifer: 0BSD
#
#	libFL:
#	Collection of FLTK subclasses (Makefile)
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

.PHONY: static clean
.DEFAULT_GOAL = staticlib

override CXXFLAGS += $(shell fltk-config --cxxflags) -I.
ifneq ($(DEBUG),)
	override CXXFLAGS += -g -Wall -Werror
endif

ifeq ($(PLATFORM), win32)
	LIBPREFIX =
	LIBSUFFIX_STATIC = .lib
else
	LIBPREFIX = lib
	LIBSUFFIX_STATIC = .a
endif

TARGET = $(LIBPREFIX)Fl$(LIBSUFFIX_STATIC)
SOURCES = $(wildcard *.cpp)
OBJECTS = $(addsuffix .o,$(SOURCES))

%.cpp.o: %.cpp
	@echo " CXX $^"
	@$(CXX) $(CXXFLAGS) -c $^ -o $@

# AR seems to write to both stdout and stderr
staticlib: $(OBJECTS)
	@echo " AR $(TARGET)"
	@$(AR) $(ARFLAGS) $(TARGET) $(OBJECTS) >/dev/null 2>&1

clean:
	@echo " RM $(OBJECTS)"
	@-rm $(OBJECTS)
	@echo " RM $(TARGET)"
	@-rm $(TARGET)
