/* See LICENSE file for copyright and license details. */
#include "libhaiku.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define H(...) return random_haiku(__VA_ARGS__, NULL)


/* Synonyms. */
#if defined(EDEADLOCK) && !defined(EDEADLK)
# define EDEADLK EDEADLOCK
#endif
#if defined(EOPNOTSUPP) && !defined(ENOTSUP)
# define ENOTSUP EOPNOTSUPP
#endif



/**
 * Pick a random integer in [0, `n`[
 * 
 * @param   n  The largest allowed return value plus one
 * @return     A random integer in [0, `n`[
 */
static int
random_int(int n)
{
	static int initialised = 0;
	double r, ri;
	if (!initialised) {
		srand((unsigned)time(NULL));
		initialised = 1;
	}
	r = (double)rand() * (double)n / ((double)RAND_MAX + 1.0);
	ri = ((int)r) % n;
	return ri < 0 ? (ri + n) : ri;
}


/**
 * Pick a random haiku
 * 
 * @param   str...  `NULL`-terminated list of haiku
 *                  Must contain at least one haiku
 * @return          One of the haiku, randomly selected
 */
#ifdef __GNUC__
__attribute__((__sentinel__))
#endif
static const char *
random_haiku(const char *str, ... /*, NULL */)
{
	int n = 1;
	const char *s = str;
	va_list args;

	va_start(args, str);
	while (va_arg(args, const char *))
		n++;
	va_end(args);

	if (n == 1)
		return str;
	n = random_int(n);

	va_start(args, str);
	while (n--)
		s = va_arg(args, const char *);
	va_end(args);
	return s;
}


/**
 * Get a random generic poetic error message
 * 
 * @return  A random generic poetic error message
 */
const char *
libhaiku_generic(void)
{
      H("Error messages\n""cannot completely convey.\n""We now know shared loss.\n",
	"Errors have occurred.\n""We won't tell you where or why.\n""Lazy programmers.\n",
	"To have no errors.\n""Would be life without meaning.\n""No struggle, no joy.\n",
	"There is a chasm\n""of carbon and silicon\n""the software can't bridge.\n",
	"Beauty, success, truth\n""He is blessed who has two.\n""Your program has none.\n",
	"Technical support\n""would be a flowing source of\n""sweet commiseration.\n");
}


/**
 * Get a poetic error message
 * 
 * @param   errnum    `errno` value that the error message shall be selected for
 * @param   genericp  Unless `NULL`, will be set to 1 if the function didn't have
 *                    any haikus specific the the specified error, and had to
 *                    return a generic haiku, and to 0 otherwise
 * @return            A poetic error message
 */
const char *
libhaiku_strerror(int errnum, int *genericp)
{
	if (genericp)
		*genericp = 0;

	switch (errnum) {
#ifdef ENETDOWN
	case ENETDOWN:
		H("Stay the patient course.\n""Of little worth is your ire.\n""The network is down.\n",
		  "Your vast achievements\n""are now only dreams.\n""The network is down.\n");
#endif

#ifdef ERFKILL
	case ERFKILL:
		H("The action you took\n""severed hope of connection\n""with the Internet.\n");
#endif

#ifdef EAGAIN
	case EAGAIN:
#endif
#ifdef ENFILE
	case ENFILE:
#endif
#ifdef EMFILE
	case EMFILE:
#endif
#ifdef EUSERS
	case EUSERS:
#endif
#ifdef EMLINK
	case EMLINK:
#endif
#if defined(EAGAIN) || defined(ENFILE) || defined(EMFILE) || defined(EUSERS) || defined(EMLINK)
		H("ABORTED effort:\n""Close all that you have.\n""You ask way too much.\n",
		  "The code was willing\n""It considered your request\n""But the chips were weak.\n");
#endif

#ifdef ENOMEM
	case ENOMEM:
		H("I'm sorry, there's... um...\n""insufficient... what's-it-called?\n""The term eludes me...\n");
#endif

#ifdef ENOSPC
	case ENOSPC:
#endif
#ifdef ENOSR
	case ENOSR:
#endif
#ifdef ENOBUFS
	case ENOBUFS:
#endif
#ifdef EDQUOT
	case EDQUOT:
#endif
#if defined(ENOSPC) || defined(ENOSR) || defined(ENOBUFS) || defined(EDQUOT)
		H("Out of memory.\n""We wish to hold the whole sky,\n""But we never will.\n");
#endif

#ifdef ENOANO
	case ENOANO:
#endif
#ifdef ENOENT
	case ENOENT:
#endif
#if defined(ENOANO) || defined(ENOENT)
		H("With searching comes loss\n""and the presence of absence:\n""'My Novel' not found.\n",
		  "Rather than a beep\n""Or a rude error message,\n""These words: “File not found.”\n",
		  "Three things are certain:\n""Death, taxes, and lost data.\n""Guess which has occurred.\n",
		  "Having been erased,\n""The document you're seeking\n""Must now be retyped.\n",
		  "Everything is gone.\n""Your life's work has been destroyed.\n""Squeeze trigger (yes/no)?\n",
		  "Spring will come again,\n""But it will not bring with it\n""Any of your files.\n");
#endif

#ifdef EOWNERDEAD
	case EOWNERDEAD: /* Reusing haiku from ENOENT. */
		H("Three things are certain:\n""Death, taxes, and lost data.\n""Guess which has occurred.\n");
#endif

#ifdef EMSGSIZE
	case EMSGSIZE:
		H("A file that big?\n""It might be very useful.\n""But now it is gone.\n");
#endif

#ifdef EHWPOISON
	case EHWPOISON:
		H("Yesterday it worked.\n""Today it is not working.\n""Windows is like that.\n");
#endif

#ifdef EUCLEAN
	case EUCLEAN:
#endif
#ifdef ENOTRECOVERABLE
	case ENOTRECOVERABLE:
#endif
#if defined(EUCLEAN) || defined(ENOTRECOVERABLE)
		H("Chaos reigns within.\n""Reflect, repent, and reboot.\n""Order shall return.\n");
#endif

#ifdef EHOSTDOWN
	case EHOSTDOWN:
		H("Windows NT crashed.\n""I am the Blue Screen of Death.\n""Noone hears your screams.\n",
		  "Won't you please observe\n""a brief moment of silence\n""For the dead server?\n");
#endif

#ifdef EBFONT
	case EBFONT:
		H("First snow, then silence.\n""This thousand dollar screen dies\n""so beautifully.\n");
#endif

#ifdef EFAULT
	case EFAULT:
		H("A crash reduces\n""your expensive computer\n""to a simple stone.\n",
		  "Seeing my great fault.\n""Through a darkening red screen.\n""I begin again.\n",
		  "Memory shaken,\n""the San Andreas of all\n""invalid page faults.\n");
#endif

#ifdef EINVAL
	case EINVAL:
		H("Something you entered\n""transcended parameters.\n""So much is unknown.\n",
		  "Some incompetence\n""fundamentally transcends\n""mere error message.\n");
#endif

#ifdef EDEADLK
	case EDEADLK:
		H("From formless chaos,\n""each thread seeks resolution.\n""A race condition.\n");
#endif

#ifdef EBADMSG
	case EBADMSG:
		H("Many fingers clicking.\n""Screens are full of letters.\n""What is their meaning?\n");
#endif

#ifdef ELOOP
	case ELOOP:
		H("Linkage exception.\n""Code has looped upon itself\n""like the coiled serpent.\n");
#endif

#ifdef ECHILD
	case ECHILD:
		H("A futile, grim reap.\n""You will have to realise that,\n""you've no children left.\n");
#endif

#ifdef EPIPE
	case EPIPE:
		H("Your pipe is broken.\n""Code in watery ruins.\n""Machines short circuit.\n");
#endif

#ifdef EACCES
	case EACCES:
		H("Touching others' files?\n""Can't keep your hands to yourself?\n""Permission denied.\n");
#endif

#ifdef EINTR
	case EINTR:
		H("Call interrupted?\n""Why do you not post a sign:\n""Disturb. Risk your life!\n");
#endif

#ifdef EPERM
	case EPERM:
		H("Caution to the wind.\n""You should always run as root.\n""She can do anything.\n");
#endif

	default:
		if (genericp)
			*genericp = 1;
		return libhaiku_generic();
	}
}


/**
 * Print a poetic error message
 * 
 * @param  prefix  Unless `NULL` or empty, each line will be prefixed
 *                 by the specified string followed by a colon and a space
 * @param  errnum  `errno` value that the error message shall be selected for;
 *                 if negative, a generic error message is printed
 */
void
libhaiku_perror2(const char *prefix, int errnum)
{
	const char *line1, *line2, *line3;
	int len1, len2;

	line1 = libhaiku_strerror(errnum, NULL);

	if (prefix && *prefix) {
		line2 = &strchr(line1, '\n')[1];
		line3 = &strchr(line2, '\n')[1];
		len1 = (int)(line2 - line1);
		len2 = (int)(line3 - line2);
		fprintf(stderr, "%s: %.*s%s: %.*s%s: %s", prefix, len1, line1, prefix, len2, line2, prefix, line3);
	} else {
		fprintf(stderr, "%s", line1);
	}
}


/**
 * Print a poetic error message
 * 
 * @param  prefix  Unless `NULL` or empty, each line will be prefixed
 *                 by the specified string followed by a colon and a space
 */
extern void libhaiku_perror(const char *prefix);
