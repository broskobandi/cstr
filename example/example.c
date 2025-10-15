#include <stdio.h>

/* Include the library. */
#include <cstr.h>

int main(void) {
	/* Create a new string.
	 * Optionally, NULL can be passed to create an 
	 * empty string that consists of a single '\0'. */
	str_t *str = str_new("Hi, World");

	/* Append data at the end of the string. */
	str_push_back(str, '!');
	str_append(str, " How are you??");

	/* Prepend data at the beginning of the string. */
	str_prepend(str, "Hi, I'm World. ");
	str_push_front(str, 'H');

	/* Remove the last character. */
	str_pop_back(str);

	/* Remove the first character. */
	str_pop_front(str);

	/* Insert a character anywhere. */
	str_insert(str, 5, '-');

	/* Remove a character from anywhere. */
	str_remove(str, 5);

	/* Replace all occurrences of a word. */
	str_replace(str, "Hi", "Hello");

	/* Query the length of the string. */
	printf("%lu\n", str_len(str));

	/* Get a const pointer to the raw string. */
	printf("%s\n", str_view(str));

	/* Delete the string. */
	str_del(str);

	return 0;
}
