# [ngIRCd](https://ngircd.barton.de) - Internet Relay Chat Server

## DOS 16-bit port for 8088 or better PC's

This is a very lazy and sloppy port of ngIRCd to 16-bit DOS using
Open Watcom 1.9 and Mike Brutman's [mTCP library](http://www.brutman.com/mTCP).

Port done by Mike Chambers, 2021. I've successfully tested this with well
over a dozen users on an 8088-based system with 640 KB RAM. It runs pretty
well at 10 MHz, and it's acceptable at 4.77 MHz.

## Building

To compile this, from the Open Watcom build environment, just run wmake.

Tested with Open Watcom 1.9.

Sample configuration and other extra files are in the conf folder. You will
need these in the same directory as ngircd.exe when running.

You will need a packet driver for your network adapter, and you will need
to create an mTCP configuration file. See http://www.brutman.com/mTCP

## Limitations on 16-bit port

- There is no SSL or ZLIB support.

- There is no IPv6 support.

- It supports 50 connections at once, counting both clients and servers.
  This can be adjusted by modifying TCP_MAX_SOCKETS in mTCP\TCPINC\GLOBAL.CFG
  and rebuilding the sources. I do not know what the max capability is on a
  640 KB system, but it's probably more than 50.

- I recommend using IP addresses for server-to-server outgoing connections,
  because DNS resolution current blocks. Usually not long, but it *could*
  be up to five seconds. Specifying a host by IP means no DNS resolution
  is required. I will try to fix this soon.

*Below is the rest of the original ngIRCd readme.*

## Introduction

*ngIRCd* is a free, portable and lightweight *Internet Relay Chat* ([IRC])
server for small or private networks, developed under the terms of the GNU
General Public License ([GPL]); please see the file `COPYING` for licensing
information.

The server is quite easy to configure, can handle dynamic IP addresses, and
optionally supports IDENT, IPv6 connections, SSL-protected links, and PAM for
user authentication as well as character set conversion for legacy clients. The
server has been written from scratch and is not based on the "forefather", the
daemon of the IRCNet.

The name ngIRCd means *next-generation IRC daemon*, which is a little bit
exaggerated: *lightweight Internet Relay Chat server* most probably would have
been a better name :-)

Please see the `INSTALL.md` document for installation and upgrade information,
online available here: <https://ngircd.barton.de/doc/INSTALL.md>!

## Status

ngIRCd should be quite feature-complete and stable to be used as a daemon in
real-world IRC networks.

It is not the goal of ngIRCd to implement all the nasty behaviors of the
original ircd, but to implement most of the useful commands and semantics
specified by the RFCs that are used by existing clients.

## Features (or: why use ngIRCd?)

- Well arranged (lean) configuration file.
- Simple to build, install, configure, and maintain.
- Supports IPv6 and SSL.
- Can use PAM for user authentication.
- Lots of popular user and channel modes are implemented.
- Supports "cloaking" of users.
- No problems with servers that have dynamic IP addresses.
- Freely available, modern, portable and tidy C source.
- Wide field of supported platforms, including AIX, A/UX, FreeBSD, HP-UX,
  IRIX, Linux, macOS, NetBSD, OpenBSD, Solaris, and Windows with Cygwin.
- ngIRCd is being actively developed since 2001.

## Documentation

The **homepage** of the ngIRCd project is <https://ngircd.barton.de>.

More documentation can be found in the `doc/` directory and
[online](https://ngircd.barton.de/documentation).

## Downloads & Source Code

You can find the latest information about the ngIRCd and the most recent
stable release on the [news](https://ngircd.barton.de/news) and
[downloads](https://ngircd.barton.de/download) pages of the homepage.

Visit our source code repository at [GitHub](https://github.com) if you are
interested in the latest development code: <https://github.com/ngircd/ngircd>.

## Problems, Bugs, Patches

Please don't hesitate to contact us if you encounter problems:

- On IRC: <irc://irc.barton.de/ngircd>
- Via the mailing list: <ngircd-ml@ngircd.barton.de>

See <http://ngircd.barton.de/support> for details.

If you find any bugs in ngIRCd (which most probably will be there ...), please
report them to our issue tracker at GitHub:

- Bug tracker: <https://github.com/ngircd/ngircd/issues>
- Patches, "pull requests": <https://github.com/ngircd/ngircd/pulls>

[IRC]: https://wikipedia.org/wiki/Internet_Relay_Chat
[GPL]: https://wikipedia.org/wiki/GNU_General_Public_License
