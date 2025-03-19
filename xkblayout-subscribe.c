#include <X11/XKBlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void
polite_exit(int signum)
{
	exit(128 + signum);
}

int
main(int argc, char **argv)
{
	XEvent event;
	Display *display;

	if (!(display = XOpenDisplay(NULL))) {
		fprintf(stderr, "cannot open display\n");
		return 1;
	}

	int xkbEventType;
	XkbQueryExtension(display, NULL, &xkbEventType, NULL, NULL, NULL);
	XkbSelectEventDetails(display, XkbUseCoreKbd, XkbStateNotify, XkbAllStateComponentsMask, XkbGroupStateMask);

	XSync(display, False);

	signal(SIGINT, polite_exit);
	signal(SIGQUIT, polite_exit);
	signal(SIGTERM, polite_exit);

	while (1) {
		XNextEvent(display, &event);

		if (event.type != xkbEventType)
			continue;

		XkbEvent *xkbEvent = (XkbEvent *) &event;

		if (xkbEvent->any.xkb_type != XkbStateNotify)
			continue;

		fprintf(stdout, "%d\n", xkbEvent->state.group);
		fflush(stdout);
	}

	return 0;
}
