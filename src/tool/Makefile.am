#
# ngIRCd -- The Next Generation IRC Daemon
# Copyright (c)2001-2012 Alexander Barton (alex@barton.de) and Contributors
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# Please read the file COPYING, README and AUTHORS for more information.
#

AUTOMAKE_OPTIONS =  ../portab/ansi2knr

EXTRA_DIST = Makefile.ng

AM_CPPFLAGS = -I$(srcdir)/../portab

noinst_LIBRARIES = libngtool.a

libngtool_a_SOURCES = tool.c

noinst_HEADERS = tool.h

maintainer-clean-local:
	rm -f Makefile Makefile.in Makefile.am

# -eof-
