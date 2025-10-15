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

/** \file src/cstr.c
 * \brief Implementation for the cstr library.
 * \details This file contains the definitions for the cstr library. */

#include "cstr.h"
#include <cvec.h>
#include <string.h>
#include <stdint.h>
#include <carena.h>

_Thread_local static const char *g_err;

CVEC_TYPEDEF(char);

/** Creates a new string.
 * \param src A string to initialize with (can be NULL).
 * \return A pointer to the new string. */
cstr_t *cstr_new(const char *src) {
	vchar_t *vec = vchar_new();
	if (!vec) {
		g_err = "Failed to create string.";
		return NULL;
	}
	if (src)
		vchar_append(vec, (void*)src, strlen(src));
	vchar_push_back(vec, '\0');
	return (cstr_t*)vec;
}

/** Deletes a string.
 * \param str A pointer to the string object to be deleted. */
void cstr_del(cstr_t *str) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vchar_t *vec = (vchar_t*)str;
	vchar_del(vec);
}

/** Returns the length of a string (\0 excluded).
 * \param str A pointer to the string to be accessed.
 * \return The length of the string or (size_t)-1 on failure. */
size_t cstr_len(const cstr_t *str) {
	if (!str) {
		g_err = "Invalid argument.";
		return (size_t)-1;
	}
	vchar_t *vec = (vchar_t*)str;
	return vchar_len(vec) - 1;
}

/** Returns a const pointer to the raw string data.
 * \param str A pointer to the string to be accessed.
 * \return A const pointer to internal string or NULL on failure. */
const char *cstr_view(const cstr_t *str) {
	if (!str) {
		g_err = "Invalid argument.";
		return NULL;
	}
	vchar_t *vec = (vchar_t*)str;
	return (const char *)vchar_view(vec, 0);
}

/** Returns a pointer to a character in a string.
 * \param str The string to be accessed,
 * \param index The index of the character to be returned.
 * \return A const pointer to the character found at 'index' or NULL. */
const char *cstr_at(const cstr_t *str, size_t index) {
	if (!str) {
		g_err = "Invalid argument.";
		return NULL;
	}
	vchar_t *vec = (vchar_t*)str;
	if (index >= vchar_len(vec) - 1) {
		g_err = "Index is out of bounds.";
		return NULL;
	}
	return (const char *)vchar_view(vec, index);
}

/** Appends a character at the end of the string.
 * \param str A pointer to the string to be modified.
 * \param c The character to be added. */
void cstr_push_back(cstr_t *str, char c) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vchar_t *vec = (vchar_t*)str;
	vchar_insert(vec, c, vchar_len(vec) - 1);
}

/** Prepends a character at the beginning of the string.
 * \param str A pointer to the string to be modified.
 * \param c The character to be added. */
void cstr_push_front(cstr_t *str, char c) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vchar_t *vec = (vchar_t*)str;
	vchar_push_front(vec, c);
}

/** Removes the last character of a string.
 * \param str A pointer to the string to be modified. */
void cstr_pop_back(cstr_t *str) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vchar_t *vec = (vchar_t*)str;
	if (vchar_len(vec) <= 1) {
		g_err = "Cannot pop empty string.";
		return;
	}
	vchar_remove(vec, vchar_len(vec) - 2);
}

/** Removes the first character of a string.
 * \param str A pointer to the string to be modified. */
void cstr_pop_front(cstr_t *str) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vchar_t *vec = (vchar_t*)str;
	if (vchar_len(vec) <= 1) {
		g_err = "Cannot pop empty string.";
		return;
	}
	vchar_pop_front(vec);
}

/** Appends a new string at the end of a string.
 * \param A pointer to the string to be modified.
 * \param src The string to be appended. */
void cstr_append(cstr_t *str, const char *src) {
	if (!str || !src) {
		g_err = "Invalid argument.";
		return;
	}
	vchar_t *vec = (vchar_t*)str;
	vchar_replace_range(
		vec,
		vchar_len(vec) - 1,
		(void*)src,
		strlen(src),
		0);
}

/** Prepends a new string at the beginning of a string.
 * \param A pointer to the string to be modified.
 * \param src The string to be appended. */
void cstr_prepend(cstr_t *str, const char *src) {
	if (!str || !src) {
		g_err = "Invalid argument.";
		return;
	}
	vchar_t *vec = (vchar_t*)str;
	vchar_prepend(vec, (void*)src, strlen(src));
}

/** Removes a character from the string.
 * \param A pointer to the string to be modified.
 * \param index The index of the character to be removed. */
void cstr_remove(cstr_t *str, size_t index) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vchar_t *vec = (vchar_t*)str;
	if (vchar_len(vec) <= 1) {
		g_err = "Cannot remove from empty string.";
		return;
	}
	if (index >= vchar_len(vec) - 1) {
		g_err = "Index is out of bounds.";
		return;
	}
	vchar_remove(vec, index);
}

/** Inserts a character into the string.
 * \param A pointer to the string to be modified.
 * \param index The index where the character is to be inserted.
 * \param c The character to be inserted. */
void cstr_insert(cstr_t *str, size_t index, char c) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vchar_t *vec = (vchar_t*)str;
	if (index >= vchar_len(vec) - 1) {
		g_err = "Index is out of bounds.";
		return;
	}
	vchar_insert(vec, c, index);
}

/** Compares two strings.
 * \param str A pointer to the string to be accessed.
 * \param src The string 'str' is to be compared with.
 * \return 1 if they are the same, 0 if they are different,
 * -1 on failure. */
int cstr_same(const cstr_t *str, const char *src) {
	if (!str || !src) {
		g_err = "Invalid argument.";
		return -1;
	}
	vchar_t *vec = (vchar_t*)str;
	if (!memcmp(vchar_view(vec, 0), src, vchar_len(vec) * sizeof(char))) {
		return 1;
	} else {
		return 0;
	}
}

/** Checks if 'keyword' can be found in 'str'.
 * \param str A pointer to the string to be accessed.
 * \param keyword The string to find in 'str'.
 * \return 1 if they 'keyword' can be found, 0 if it cannot,
 * -1 on failure. */
int cstr_has(const cstr_t *str, const char *keyword) {
	if (!str || !keyword) {
		g_err = "Invalid argument.";
		return -1;
	}
	vchar_t *vec = (vchar_t*)str;
	if (strstr(vchar_view(vec, 0), keyword)) {
		return 1;
	} else {
		return 0;
	}
}

/** Checks if 'keyword' can be found in 'str'.
 * \param str A pointer to the string to be accessed.
 * \param keyword The string to find in 'str'.
 * \return The index of the first occurrence of 'keyword' or 
 * (size_t)-1 on failure. */
size_t cstr_find(const cstr_t *str, const char *keyword) {
	if (!str || !keyword) {
		g_err = "Invalid argument.";
		return (size_t)-1;
	}
	vchar_t *vec = (vchar_t*)str;
	void *ptr = strstr(vchar_view(vec, 0), keyword);
	if (!ptr) return (size_t)-1;
	uintptr_t index = (uintptr_t)ptr;
	return index - (uintptr_t)vchar_view(vec, 0);
}

/** Replaces all occurrences of 'keyword' with 'src'.
 * \param str A pointer to the string to be modified.
 * \param keyword The string to be replaced.
 * \param src The string to replace 'keyword' with. */
void cstr_replace(cstr_t *str, const char *keyword, const char *src) {
	if (!str || !keyword || !src) {
		g_err = "Invalid argument.";
		return;
	}
	vchar_t *vec = (vchar_t*)str;
	while (cstr_has(str, keyword)) {
		vchar_replace_range(
			vec,
			cstr_find(str, keyword),
			(void*)src,
			strlen(src),
			strlen(keyword));
	}
}

/** Returns a string containing the latest error information if exists
 * or NULL if it does not. */
const char *cstr_get_error() {
	return g_err;
}
