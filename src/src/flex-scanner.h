/* Common parts between scan-code.l, scan-gram.l, and scan-skel.l.

   Copyright (C) 2006, 2009-2015 Free Software Foundation, Inc.

   This file is part of Bison, the GNU Compiler Compiler.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef FLEX_PREFIX
# error "FLEX_PREFIX not defined"
#endif

/* Flex full version as a number.  */
#define FLEX_VERSION                    \
  ((YY_FLEX_MAJOR_VERSION) * 1000000    \
   + (YY_FLEX_MINOR_VERSION) * 1000     \
   + (YY_FLEX_SUBMINOR_VERSION))

/* Pacify "gcc -Wmissing-prototypes" when flex 2.5.31 is used.  */
#if FLEX_VERSION <= 2005031
int   FLEX_PREFIX (get_lineno) (void);
FILE *FLEX_PREFIX (get_in) (void);
FILE *FLEX_PREFIX (get_out) (void);
int   FLEX_PREFIX (get_leng) (void);
char *FLEX_PREFIX (get_text) (void);
void  FLEX_PREFIX (set_lineno) (int);
void  FLEX_PREFIX (set_in) (FILE *);
void  FLEX_PREFIX (set_out) (FILE *);
int   FLEX_PREFIX (get_debug) (void);
void  FLEX_PREFIX (set_debug) (int);
int   FLEX_PREFIX (lex_destroy) (void);
#endif

#define last_string    FLEX_PREFIX (last_string)

/* It seems to be a nice "feature" of Flex that one cannot use yytext,
   yyleng etc. when a prefix is given, since there is no longer a
   #define, but rather the token is actually changed in the output.
   However, this is not true for Flex 2.5.4.  */
#ifndef yyleng
# define yyleng  FLEX_PREFIX (leng)
#endif
#ifndef yytext
# define yytext  FLEX_PREFIX (text)
#endif

/* Non-reentrant scanners generated by Flex 2.5.9 and later (and some earlier
   versions according to the Flex manual) leak memory if yylex_destroy is not
   invoked.  However, yylex_destroy is not defined before Flex 2.5.9, so give
   an implementation here that at least appears to work with Flex 2.5.4.  */
#if FLEX_VERSION <= 2005009
# define yylex_destroy() yy_delete_buffer (YY_CURRENT_BUFFER)
#endif

/* OBSTACK_FOR_STRING -- Used to store all the characters that we need to
   keep (to construct ID, STRINGS etc.).  Use the following macros to
   use it.

   Use STRING_GROW to append what has just been matched, and
   STRING_FINISH to end the string (it puts the ending 0).
   STRING_FINISH also stores this string in LAST_STRING, which can be
   used, and which is used by STRING_FREE to free the last string.  */

#ifndef FLEX_NO_OBSTACK

static struct obstack obstack_for_string;

# define STRING_GROW                                    \
  obstack_grow (&obstack_for_string, yytext, yyleng)

# define STRING_FINISH                                  \
  (last_string = obstack_finish0 (&obstack_for_string))

# define STRING_FREE                                    \
  obstack_free (&obstack_for_string, last_string)

#endif
