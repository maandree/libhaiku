.POSIX:

CONFIGFILE = config.mk
include $(CONFIGFILE)

# Change to macos.mk for Mac OS
OSCONFIGFILE = linux.mk
include $(OSCONFIGFILE)


LIB_MAJOR = 2
LIB_MINOR = 0

LIB_VERSION = $(LIB_MAJOR).$(LIB_MINOR)

MAN3 = libhaiku.7
MAN7 = libhaiku_generic.3 libhaiku_perror.3 libhaiku_perror2.3 libhaiku_strerror.3


all: libhaiku.a libhaiku.$(LIBEXT)

libhaiku.o: libhaiku.c libhaiku.h
	$(CC) -c -o $@ libhaiku.c $(CFLAGS) $(CPPFLAGS)

libhaiku.lo: libhaiku.c libhaiku.h
	$(CC) -fPIC -c -o $@ libhaiku.c $(CFLAGS) $(CPPFLAGS)

libhaiku.$(LIBEXT): libhaiku.lo
	$(CC) $(LIBFLAGS) -o $@ libhaiku.lo $(LDFLAGS)

libhaiku.a: libhaiku.o
	-rm -f -- $@
	$(AR) rc $@ libhaiku.o
	$(AR) -s $@

install: libhaiku.$(LIBEXT) libhaiku.a
	mkdir -p -- "$(DESTDIR)$(PREFIX)/lib"
	mkdir -p -- "$(DESTDIR)$(PREFIX)/include"
	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man3"
	mkdir -p -- "$(DESTDIR)$(MANPREFIX)/man7"
	cp -- libhaiku.a "$(DESTDIR)$(PREFIX)/lib/"
	cp -- libhaiku.$(LIBEXT) "$(DESTDIR)$(PREFIX)/lib/libhaiku.$(LIBMINOREXT)"
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
	-rm -f -- *.o *.lo *.a *.su *.$(LIBEXT) *.$(LIBEXT).* *.*.$(LIBEXT)

.PHONY: all install uninstall clean
