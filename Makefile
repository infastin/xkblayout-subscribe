PREFIX ?= /usr/local
CC ?= cc
LDFLAGS = -lX11

output: xkblayout-subscribe.c
	${CC} xkblayout-subscribe.c $(LDFLAGS) -o xkblayout-subscribe

clean:
	rm -f *.o xkblayout-subscribe

install: output
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 0755 xkblayout-subscribe $(DESTDIR)$(PREFIX)/bin/xkblayout-subscribe

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/xkblayout-subscribe
