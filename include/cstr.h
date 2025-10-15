/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/** \file include/cstr.h
 * \brief Public header file for the cstr library.
 * \details This file contains the declarations for the cstr library. */
#ifndef CSTR_H
#define CSTR_H

#include <stddef.h>

typedef struct str str_t;

/** Creates a new string.
 * This function sets cerror on failure.
 * \param src A string to initialize with (can be NULL).
 * \return A pointer to the new string. */
str_t *str_new(const char *src);

/** Deletes a string.
 * This function sets cerror on failure.
 * \param str A pointer to the string object to be deleted. */
void str_del(str_t *str);

/** Returns the length of a string (\0 excluded).
 * This function sets cerror on failure.
 * \param str A pointer to the string to be accessed.
 * This function sets cerror on failure.
 * \return The length of the string or (size_t)-1 on failure. */
size_t str_len(const str_t *str);

/** Returns a const pointer to the raw string data.
 * This function sets cerror on failure.
 * \param str A pointer to the string to be accessed.
 * \return A const pointer to internal string or NULL on failure. */
const char *str_view(const str_t *str);

/** Returns a pointer to a character in a string.
 * This function sets cerror on failure.
 * \param str The string to be accessed,
 * \param index The index of the character to be returned.
 * \return A const pointer to the character found at 'index' or NULL. */
const char *str_at(const str_t *str, size_t index);

/** Appends a character at the end of the string.
 * This function sets cerror on failure.
 * \param str A pointer to the string to be modified.
 * \param c The character to be added. */
void str_push_back(str_t *str, char c);

/** Prepends a character at the beginning of the string.
 * This function sets cerror on failure.
 * \param str A pointer to the string to be modified.
 * \param c The character to be added. */
void str_push_front(str_t *str, char c);

/** Removes the last character of a string.
 * This function sets cerror on failure.
 * \param str A pointer to the string to be modified. */
void str_pop_back(str_t *str);

/** Removes the first character of a string.
 * This function sets cerror on failure.
 * \param str A pointer to the string to be modified. */
void str_pop_front(str_t *str);

/** Appends a new string at the end of a string.
 * This function sets cerror on failure.
 * \param A pointer to the string to be modified.
 * \param src The string to be appended. */
void str_append(str_t *str, const char *src);

/** Prepends a new string at the beginning of a string.
 * This function sets cerror on failure.
 * \param A pointer to the string to be modified.
 * \param src The string to be appended. */
void str_prepend(str_t *str, const char *src);

/** Removes a character from the string.
 * This function sets cerror on failure.
 * \param A pointer to the string to be modified.
 * \param index The index of the character to be removed. */
void str_remove(str_t *str, size_t index);

/** Inserts a character into the string.
 * This function sets cerror on failure.
 * \param A pointer to the string to be modified.
 * \param index The index where the character is to be inserted.
 * \param c The character to be inserted. */
void str_insert(str_t *str, size_t index, char c);

/** Compares two strings.
 * This function sets cerror on failure.
 * \param str A pointer to the string to be accessed.
 * \param src The string 'str' is to be compared with.
 * \return 1 if they are the same, 0 if they are different,
 * -1 on failure. */
int str_same(const str_t *str, const char *src);

/** Checks if 'keyword' can be found in 'str'.
 * This function sets cerror on failure.
 * \param str A pointer to the string to be accessed.
 * \param keyword The string to find in 'str'.
 * \return 1 if they 'keyword' can be found, 0 if it cannot,
 * -1 on failure. */
int str_has(const str_t *str, const char *keyword);

/** Checks if 'keyword' can be found in 'str'.
 * This function sets cerror on failure.
 * \param str A pointer to the string to be accessed.
 * \param keyword The string to find in 'str'.
 * \return The index of the first occurrence of 'keyword' or 
 * (size_t)-1 on failure. */
size_t str_find(const str_t *str, const char *keyword);

/** Replaces all occurrences of 'keyword' with 'src'.
 * This function sets cerror on failure.
 * \param str A pointer to the string to be modified.
 * \param keyword The string to be replaced.
 * \param src The string to replace 'keyword' with. */
void str_replace(str_t *str, const char *keyword, const char *src);

#endif
