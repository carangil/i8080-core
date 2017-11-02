Intel 8080 (KR580VM80A) microprocessor core model
=================================================
This project is a fork of https://github.com/begoon/i8080-core

This is ported from C to CMOC, which is very close to C.

Build for PC
=====


make pc100
	Will build for a PC, with start address 0x100
	Offers minimal CP/M output functionality

	The PC version will run better with the commamd:
	stdbuf -i0 -o0 -e0 ./pcmain

	The stdbuf command disables output line buffering.
	Keyboard input is not implemented in the PC version.

make pc
	Will build for a PC, with start address 0x1000

	The PC version will run better with the commamd:
	stdbuf -i0 -o0 -e0 ./pcmain

	The stdbuf command disables output line buffering.
	Keyboard input is not implemented in the PC version.

Build for PC
=====


make coco100
	Will build for a CoCo, with start address 0x100
	Offers minimal CP/M output for test programs


make coco
	Will build for a CoCo, with start address 0x0
	Keyboard input is implemented on IO port 1.
	Runs Altair Basic


Test Programs
=============

prog8080.c already contains a simple test program.  This should be run with pc100 or coco100

make pc100
./pcmain        Should output:

[
MICROCOSM ASSOCIATES 8080/8085 CPU DIAGNOSTIC VERSION 1.0  (C) 1980

CPU IS OPERATIONAL
]

along with other debugging information.


Other test programs require 'conv':

make conv

Then:

make test, make 8080pre or make 8080ex1 will reconfigure prog8080.c to contain tests/TEST.COM, 8080EX1.COM or *)*)EX1.COM respectively.  The emulator can then be rebuilt with either make pc100 or make coco100.

Building for CoCo
=================
CMOC is required.  https://perso.b2b2c.ca/~sarrazip/dev/cmoc.html

The Makefile needs to be modified co COCOINC points to where coco.h is installed.

I have only tested this with Disk Extended Color Basic.

Building Altair BASIC for CoCo
===============================

This is what you really came here for.

You need to download altair basic.  There is a Makefile target to do this already.  (Downloads from a different github repo).

make altbas   : Should download altair 4k basic and run conv
make coco	: Should build a new cocomain.bin image containing altair basic.

This can then be run in xroar, by using the File/Run menu and selecting cocomain.bin.




