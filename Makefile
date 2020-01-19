# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

CFLAGS=-std=gnu99
SHELL = /bin/sh
CC = gcc

INCLUDES = -I./src -I/usr/lib/gcc/x86_64-linux-gnu/7/include -I/usr/include -I/usr/include/x86_64-linux-gnu

LFLAGS =

LIBS = -lpanel -lncursesw -lcmocka

SRCS = core.c file.c game.c global.c input.c log.c piece.c render.c resource.c utilities.c windowmanager.c ccheckers.c

VPATH=src

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

MAIN = crappycheckers

.PHONY: depend clean

all: ${MAIN}

$(MAIN): $(OBJS) 
		$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o: 
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean: 
		$(RM) *.o *~ $(MAIN)

depend: $(SRCS) 
		makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

src/core.o: src/core.h /usr/lib/gcc/x86_64-linux-gnu/7/include/stdbool.h
src/file.o: /usr/include/stdio.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
src/file.o: /usr/include/features.h /usr/include/stdc-predef.h
src/file.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
src/file.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
src/file.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/libio.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/_G_config.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
src/file.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
src/file.o: /usr/include/stdlib.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/waitflags.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/waitstatus.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/floatn.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/floatn-common.h
src/file.o: /usr/include/x86_64-linux-gnu/sys/types.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
src/file.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
src/file.o: /usr/include/x86_64-linux-gnu/sys/select.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/select.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
src/file.o: /usr/include/x86_64-linux-gnu/sys/sysmacros.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/sysmacros.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
src/file.o: /usr/include/alloca.h
src/file.o: /usr/include/x86_64-linux-gnu/bits/stdlib-float.h
src/game.o: /usr/include/stdio.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
src/game.o: /usr/include/features.h /usr/include/stdc-predef.h
src/game.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
src/game.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
src/game.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/libio.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/_G_config.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
src/game.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
src/game.o: /usr/include/stdlib.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/waitflags.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/waitstatus.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/floatn.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/floatn-common.h
src/game.o: /usr/include/x86_64-linux-gnu/sys/types.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
src/game.o: /usr/include/endian.h /usr/include/x86_64-linux-gnu/bits/endian.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
src/game.o: /usr/include/x86_64-linux-gnu/sys/select.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/select.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
src/game.o: /usr/include/x86_64-linux-gnu/sys/sysmacros.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/sysmacros.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
src/game.o: /usr/include/alloca.h
src/game.o: /usr/include/x86_64-linux-gnu/bits/stdlib-float.h
src/game.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdbool.h src/game.h
src/game.o: src/utilities.h src/piece.h src/input.h /usr/include/ncurses.h
src/game.o: /usr/include/ncurses_dll.h
src/game.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h
src/game.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint-gcc.h
src/game.o: /usr/include/unctrl.h /usr/include/curses.h src/log.h
src/global.o: src/global.h
src/input.o: /usr/include/string.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
src/input.o: /usr/include/features.h /usr/include/stdc-predef.h
src/input.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
src/input.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
src/input.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
src/input.o: /usr/include/strings.h /usr/include/ncurses.h
src/input.o: /usr/include/ncurses_dll.h
src/input.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h
src/input.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint-gcc.h
src/input.o: /usr/include/stdio.h /usr/include/x86_64-linux-gnu/bits/types.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/libio.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/_G_config.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
src/input.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
src/input.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdbool.h
src/input.o: /usr/include/unctrl.h /usr/include/curses.h /usr/include/ctype.h
src/input.o: /usr/include/endian.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/endian.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
src/input.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h src/game.h
src/input.o: src/input.h src/piece.h src/log.h
src/log.o: /usr/include/stdio.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
src/log.o: /usr/include/features.h /usr/include/stdc-predef.h
src/log.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
src/log.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
src/log.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/types.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/libio.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/_G_config.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
src/log.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
src/log.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdbool.h
src/log.o: /usr/include/string.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
src/log.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/endian.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/endian.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
src/log.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h src/log.h
src/log.o: src/file.h src/utilities.h src/piece.h src/game.h
src/piece.o: /usr/include/stdlib.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
src/piece.o: /usr/include/features.h /usr/include/stdc-predef.h
src/piece.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
src/piece.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
src/piece.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/waitflags.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/waitstatus.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/floatn.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/floatn-common.h
src/piece.o: /usr/include/x86_64-linux-gnu/sys/types.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
src/piece.o: /usr/include/endian.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/endian.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
src/piece.o: /usr/include/x86_64-linux-gnu/sys/select.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/select.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
src/piece.o: /usr/include/x86_64-linux-gnu/sys/sysmacros.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/sysmacros.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
src/piece.o: /usr/include/alloca.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/stdlib-float.h
src/piece.o: /usr/include/stdio.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/libio.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/_G_config.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
src/piece.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
src/piece.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
src/piece.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdbool.h src/piece.h
src/piece.o: src/game.h src/input.h /usr/include/ncurses.h
src/piece.o: /usr/include/ncurses_dll.h
src/piece.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h
src/piece.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint-gcc.h
src/piece.o: /usr/include/unctrl.h /usr/include/curses.h src/log.h
src/piece.o: src/resource.h src/global.h
src/render.o: /usr/include/ncurses.h /usr/include/ncurses_dll.h
src/render.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h
src/render.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint-gcc.h
src/render.o: /usr/include/stdio.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
src/render.o: /usr/include/features.h /usr/include/stdc-predef.h
src/render.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
src/render.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
src/render.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/libio.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/_G_config.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
src/render.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
src/render.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdbool.h
src/render.o: /usr/include/unctrl.h /usr/include/curses.h
src/render.o: /usr/include/string.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
src/render.o: /usr/include/strings.h /usr/include/stdlib.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/waitflags.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/waitstatus.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/floatn.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/floatn-common.h
src/render.o: /usr/include/x86_64-linux-gnu/sys/types.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
src/render.o: /usr/include/endian.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/endian.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
src/render.o: /usr/include/x86_64-linux-gnu/sys/select.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/select.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
src/render.o: /usr/include/x86_64-linux-gnu/sys/sysmacros.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/sysmacros.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
src/render.o: /usr/include/alloca.h
src/render.o: /usr/include/x86_64-linux-gnu/bits/stdlib-float.h src/piece.h
src/render.o: src/game.h src/windowmanager.h src/global.h src/log.h
src/render.o: src/input.h
src/resource.o: /usr/include/stdio.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
src/resource.o: /usr/include/features.h /usr/include/stdc-predef.h
src/resource.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
src/resource.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
src/resource.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/libio.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/_G_config.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
src/resource.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
src/resource.o: /usr/include/stdlib.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/waitflags.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/waitstatus.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/floatn.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/floatn-common.h
src/resource.o: /usr/include/x86_64-linux-gnu/sys/types.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
src/resource.o: /usr/include/endian.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/endian.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
src/resource.o: /usr/include/x86_64-linux-gnu/sys/select.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/select.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
src/resource.o: /usr/include/x86_64-linux-gnu/sys/sysmacros.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/sysmacros.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
src/resource.o: /usr/include/alloca.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/stdlib-float.h
src/resource.o: /usr/include/string.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
src/resource.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
src/resource.o: /usr/include/strings.h src/resource.h src/file.h
src/utilities.o: /usr/include/stdlib.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
src/utilities.o: /usr/include/features.h /usr/include/stdc-predef.h
src/utilities.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
src/utilities.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
src/utilities.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/waitflags.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/waitstatus.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/floatn.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/floatn-common.h
src/utilities.o: /usr/include/x86_64-linux-gnu/sys/types.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/stdint-intn.h
src/utilities.o: /usr/include/endian.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/endian.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/byteswap.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/byteswap-16.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/uintn-identity.h
src/utilities.o: /usr/include/x86_64-linux-gnu/sys/select.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/select.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/sigset_t.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timeval.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
src/utilities.o: /usr/include/x86_64-linux-gnu/sys/sysmacros.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/sysmacros.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/thread-shared-types.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/pthreadtypes-arch.h
src/utilities.o: /usr/include/alloca.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/stdlib-float.h
src/utilities.o: /usr/include/time.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/time.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
src/utilities.o: /usr/include/stdio.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/libio.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/_G_config.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
src/utilities.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
src/utilities.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
src/utilities.o: src/utilities.h src/piece.h
src/utilities.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdbool.h src/game.h
src/utilities.o: src/log.h
src/windowmanager.o: /usr/include/ncurses.h /usr/include/ncurses_dll.h
src/windowmanager.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h
src/windowmanager.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint-gcc.h
src/windowmanager.o: /usr/include/stdio.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
src/windowmanager.o: /usr/include/features.h /usr/include/stdc-predef.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
src/windowmanager.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/types.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/libio.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/_G_config.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
src/windowmanager.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
src/windowmanager.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
src/windowmanager.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdbool.h
src/windowmanager.o: /usr/include/unctrl.h /usr/include/curses.h
src/windowmanager.o: /usr/include/panel.h src/global.h
src/ccheckers.o: /usr/include/ncurses.h /usr/include/ncurses_dll.h
src/ccheckers.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint.h
src/ccheckers.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdint-gcc.h
src/ccheckers.o: /usr/include/stdio.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/libc-header-start.h
src/ccheckers.o: /usr/include/features.h /usr/include/stdc-predef.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/sys/cdefs.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/wordsize.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/long-double.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/gnu/stubs.h
src/ccheckers.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stddef.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/typesizes.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/__FILE.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/FILE.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/libio.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/_G_config.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h
src/ccheckers.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdarg.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/stdio_lim.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/sys_errlist.h
src/ccheckers.o: /usr/lib/gcc/x86_64-linux-gnu/7/include/stdbool.h
src/ccheckers.o: /usr/include/unctrl.h /usr/include/curses.h
src/ccheckers.o: /usr/include/unistd.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/posix_opt.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/environments.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/confname.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/getopt_posix.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/getopt_core.h
src/ccheckers.o: /usr/include/time.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/time.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/clock_t.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/time_t.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/struct_tm.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/struct_timespec.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/clockid_t.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/timer_t.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/struct_itimerspec.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/locale_t.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/types/__locale_t.h
src/ccheckers.o: /usr/include/locale.h
src/ccheckers.o: /usr/include/x86_64-linux-gnu/bits/locale.h src/piece.h
src/ccheckers.o: src/game.h src/render.h src/input.h src/resource.h
src/ccheckers.o: src/windowmanager.h src/log.h src/file.h src/utilities.h
