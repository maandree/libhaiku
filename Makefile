.POSIX:

CONFIGFILE = config.mk
include $(CONFIGFILE)

OS = linux
# Linux:   linux
# Mac OS:  macos
# Windows: windows
include mk/$(OS).mk


LIB_MAJOR = 2
LIB_MINOR = 0
LIB_VERSION = $(LIB_MAJOR).$(LIB_MINOR)


MAN3 = libhaiku.7
MAN7 = libhaiku_generic.3 libhaiku_perror.3 libhaiku_perror2.3 libhaiku_strerror.3

OBJ = libhaiku.o
HDR = libhaiku.h

LOBJ = $(OBJ:.o=.lo)


all: libhaiku.a libhaiku.$(LIBEXT)
$(OBJ): $(HDR)
$(LOBJ): $(HDR)

.c.o:
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

.c.lo:
	$(CC) -fPIC -c -o $@ $< $(CFLAGS) $(CPPFLAGS)

libhaiku.$(LIBEXT): $(LOBJ)
	$(CC) $(LIBFLAGS) -o $@ $(LOBJ) $(LDFLAGS)

libhaiku.a: $(OBJ)
	-rm -f -- $@
	$(AR) rc $@ $(OBJ)
	$(AR) -s $@

install: libhaiku.$(LIBEXT) libhaiku.a
	mkdir -p -- "$(DESTDIR)$(PREFIX)/lib"
	mkdir -p -- "$(DESTDIR)$(PREFIX)/include"
	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man3"
	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man7"
	cp -- libhaiku.a "$(DESTDIR)$(PREFIX)/lib/"
	cp -- libhaiku.$(LIBEXT) "$(DESTDIR)$(PREFIX)/lib/libhaiku.$(LIBMINOREXT)"
	$(FIX_INSTALL_NAME) "$(DESTDIR)$(PREFIX)/lib/libhaiku.$(LIBMINOREXT)"
	ln -sf -- libhaiku.$(LIBMINOREXT) "$(DESTDIR)$(PREFIX)/lib/libhaiku.$(LIBMAJOREXT)"
	ln -sf -- libhaiku.$(LIBMINOREXT) "$(DESTDIR)$(PREFIX)/lib/libhaiku.$(LIBEXT)"
	cp -- libhaiku.h "$(DESTDIR)$(PREFIX)/include/"
	cp -- $(MAN3) "$(DESTDIR)$(MANPREFIX)/man3/"
	cp -- $(MAN7) "$(DESTDIR)$(MANPREFIX)/man7/"

uninstall:
	-rm -f "$(DESTDIR)$(PREFIX)/lib/libhaiku.a"
	-rm -f "$(DESTDIR)$(PREFIX)/lib/libhaiku.$(LIBMINOREXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libhaiku.$(LIBMAJOREXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/lib/libhaiku.$(LIBEXT)"
	-rm -f -- "$(DESTDIR)$(PREFIX)/include/libhaiku.h"
	-cd -- "$(DESTDIR)$(MANPREFIX)/man3/" && rm -rf -- $(MAN3)
	-cd -- "$(DESTDIR)$(MANPREFIX)/man7/" && rm -rf -- $(MAN7)

clean:
	-rm -f -- *.o *.lo *.a *.su *.$(LIBEXT) *.$(LIBEXT).*

.SUFFIXES:
.SUFFIXES: .lo .o .c

.PHONY: all install uninstall clean
