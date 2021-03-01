/* See LICENSE file for copyright and license details. */
#ifndef LIBHAIKU_H
#define LIBHAIKU_H

#include <errno.h>

/**
 * Get a random generic poetic error message
 * 
 * @return  A random generic poetic error message
 */
const char *libhaiku_generic(void);

/**
 * Get a poetic error message
 * 
 * @param   errnum    `errno` value that the error message shall be selected for
 * @param   genericp  Unless `NULL`, will be set to 1 if the function didn't have
 *                    any haikus specific the the specified error, and had to
 *                    return a generic haiku, and to 0 otherwise
 * @return            A poetic error message
 */
const char *libhaiku_strerror(int, int *);

/**
 * Print a poetic error message
 * 
 * @param  prefix  Unless `NULL` or empty, each line will be prefixed
 *                 by the specified string followed by a colon and a space
 * @param  errnum  `errno` value that the error message shall be selected for;
 *                 if negative, a generic error message is printed
 */
void libhaiku_perror2(const char *, int);

/**
 * Print a poetic error message
 * 
 * @param  prefix  Unless `NULL` or empty, each line will be prefixed
 *                 by the specified string followed by a colon and a space
 */
inline void
libhaiku_perror(const char *_libhaiku_prefix)
{
	libhaiku_perror2(_libhaiku_prefix, errno);
}

#endif
