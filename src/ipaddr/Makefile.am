#
# ipaddr/Makefile.am
# (c) 2008 Florian Westphal <fw@strlen.de>, public domain.
#

AUTOMAKE_OPTIONS =  ../portab/ansi2knr

EXTRA_DIST = Makefile.ng

AM_CPPFLAGS = -I$(srcdir)/../portab

noinst_LIBRARIES = libngipaddr.a

libngipaddr_a_SOURCES = ng_ipaddr.c

noinst_HEADERS = ng_ipaddr.h

maintainer-clean-local:
	rm -f Makefile Makefile.in Makefile.am

# -eof-
