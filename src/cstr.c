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

/** Creates a new string.
 * \param src A string to initialize with (can be NULL).
 * \return A pointer to the new string. */
str_t *str_new(const char *src) {
	vec_t *vec = vec_new(sizeof(char));
	if (!vec) {
		g_err = "Failed to create string.";
		return NULL;
	}
	if (src)
		vec_append(vec, (void*)src, strlen(src), sizeof(char));
	char c = '\0';
	vec_push_back(vec, &c, sizeof(char));
	return (str_t*)vec;
}

/** Deletes a string.
 * \param str A pointer to the string object to be deleted. */
void str_del(str_t *str) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vec_t *vec = (vec_t*)str;
	vec_del(vec);
}

/** Returns the length of a string (\0 excluded).
 * \param str A pointer to the string to be accessed.
 * \return The length of the string or (size_t)-1 on failure. */
size_t str_len(const str_t *str) {
	if (!str) {
		g_err = "Invalid argument.";
		return (size_t)-1;
	}
	vec_t *vec = (vec_t*)str;
	return vec_len(vec) - 1;
}

/** Returns a const pointer to the raw string data.
 * \param str A pointer to the string to be accessed.
 * \return A const pointer to internal string or NULL on failure. */
const char *str_view(const str_t *str) {
	if (!str) {
		g_err = "Invalid argument.";
		return NULL;
	}
	vec_t *vec = (vec_t*)str;
	return (const char *)vec_view(vec, 0);
}

/** Returns a pointer to a character in a string.
 * \param str The string to be accessed,
 * \param index The index of the character to be returned.
 * \return A const pointer to the character found at 'index' or NULL. */
const char *str_at(const str_t *str, size_t index) {
	if (!str) {
		g_err = "Invalid argument.";
		return NULL;
	}
	vec_t *vec = (vec_t*)str;
	if (index >= vec_len(vec) - 1) {
		g_err = "Index is out of bounds.";
		return NULL;
	}
	return (const char *)vec_view(vec, index);
}

/** Appends a character at the end of the string.
 * \param str A pointer to the string to be modified.
 * \param c The character to be added. */
void str_push_back(str_t *str, char c) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vec_t *vec = (vec_t*)str;
	vec_insert(vec, vec_len(vec) - 1, &c, sizeof(char));
}

/** Prepends a character at the beginning of the string.
 * \param str A pointer to the string to be modified.
 * \param c The character to be added. */
void str_push_front(str_t *str, char c) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vec_t *vec = (vec_t*)str;
	vec_push_front(vec, &c, sizeof(char));
}

/** Removes the last character of a string.
 * \param str A pointer to the string to be modified. */
void str_pop_back(str_t *str) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vec_t *vec = (vec_t*)str;
	if (vec_len(vec) <= 1) {
		g_err = "Cannot pop empty string.";
		return;
	}
	vec_remove(vec, vec_len(vec) - 2);
}

/** Removes the first character of a string.
 * \param str A pointer to the string to be modified. */
void str_pop_front(str_t *str) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vec_t *vec = (vec_t*)str;
	if (vec_len(vec) <= 1) {
		g_err = "Cannot pop empty string.";
		return;
	}
	vec_pop_front(vec);
}

/** Appends a new string at the end of a string.
 * \param A pointer to the string to be modified.
 * \param src The string to be appended. */
void str_append(str_t *str, const char *src) {
	if (!str || !src) {
		g_err = "Invalid argument.";
		return;
	}
	vec_t *vec = (vec_t*)str;
	vec_replace_range(
		vec,
		vec_len(vec) - 1,
		(void*)src,
		strlen(src),
		0,
		sizeof(char));
}

/** Prepends a new string at the beginning of a string.
 * \param A pointer to the string to be modified.
 * \param src The string to be appended. */
void str_prepend(str_t *str, const char *src) {
	if (!str || !src) {
		g_err = "Invalid argument.";
		return;
	}
	vec_t *vec = (vec_t*)str;
	vec_prepend(vec, (void*)src, strlen(src), sizeof(char));
}

/** Removes a character from the string.
 * \param A pointer to the string to be modified.
 * \param index The index of the character to be removed. */
void str_remove(str_t *str, size_t index) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vec_t *vec = (vec_t*)str;
	if (vec_len(vec) <= 1) {
		g_err = "Cannot remove from empty string.";
		return;
	}
	if (index >= vec_len(vec) - 1) {
		g_err = "Index is out of bounds.";
		return;
	}
	vec_remove(vec, index);
}

/** Inserts a character into the string.
 * \param A pointer to the string to be modified.
 * \param index The index where the character is to be inserted.
 * \param c The character to be inserted. */
void str_insert(str_t *str, size_t index, char c) {
	if (!str) {
		g_err = "Invalid argument.";
		return;
	}
	vec_t *vec = (vec_t*)str;
	if (index >= vec_len(vec) - 1) {
		g_err = "Index is out of bounds.";
		return;
	}
	vec_insert(vec, index, &c, sizeof(char));
}

/** Compares two strings.
 * \param str A pointer to the string to be accessed.
 * \param src The string 'str' is to be compared with.
 * \return 1 if they are the same, 0 if they are different,
 * -1 on failure. */
int str_same(const str_t *str, const char *src) {
	if (!str || !src) {
		g_err = "Invalid argument.";
		return -1;
	}
	vec_t *vec = (vec_t*)str;
	if (!memcmp(vec_view(vec, 0), src, vec_len(vec) * sizeof(char))) {
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
int str_has(const str_t *str, const char *keyword) {
	if (!str || !keyword) {
		g_err = "Invalid argument.";
		return -1;
	}
	vec_t *vec = (vec_t*)str;
	if (strstr(vec_view(vec, 0), keyword)) {
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
size_t str_find(const str_t *str, const char *keyword) {
	if (!str || !keyword) {
		g_err = "Invalid argument.";
		return (size_t)-1;
	}
	vec_t *vec = (vec_t*)str;
	void *ptr = strstr(vec_view(vec, 0), keyword);
	if (!ptr) return (size_t)-1;
	uintptr_t index = (uintptr_t)ptr;
	return index - (uintptr_t)vec_view(vec, 0);
}

/** Replaces all occurrences of 'keyword' with 'src'.
 * \param str A pointer to the string to be modified.
 * \param keyword The string to be replaced.
 * \param src The string to replace 'keyword' with. */
void str_replace(str_t *str, const char *keyword, const char *src) {
	if (!str || !keyword || !src) {
		g_err = "Invalid argument.";
		return;
	}
	vec_t *vec = (vec_t*)str;
	while (str_has(str, keyword)) {
		vec_replace_range(
			vec,
			str_find(str, keyword),
			(void*)src,
			strlen(src),
			strlen(keyword),
			sizeof(char)
		);
	}
}

/** Returns a string containing the latest error information if exists
 * or NULL if it does not. */
const char *str_get_error() {
	return g_err;
}
