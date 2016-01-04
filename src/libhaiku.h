/**
 * Copyright © 2016  Mattias Andrée <maandree@member.fsf.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBHAIKU_H
#define LIBHAIKU_H


/**
 * Whenever possible, print am error message in haiku.
 * 
 * Nothing is printed if `errno` is 0.
 * 
 * @param  s  The argument to pass to `perror` in case we call back to it.
 *            `NULL` if you never what `perror` to be used.
 */
void libhaiku_perror(const char *s);


#endif

