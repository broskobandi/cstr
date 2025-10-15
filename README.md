# cstr
## Dynamic string written in C.
The goal of the project is to provide fast and reliable abstractions for
handling dynamic strings in C.
## Prerequisites
- cmake (for building the library)
- [cvec](https://github.com/broskobandi/cvec.git)
- [carena](https://github.com/broskobandi/carena.git)
- [ctest](https://github.com/broskobandi/ctest.git) (for running the tests)
## Installation
```bash
git clone https://github.com/broskobandi/cstr.git &&
cd cstr &&
mkdir build &&
cd build &&
cmake .. &&
make &&
sudo make install
```
## Testing
```bash
cd cstr/build &&
make test &&
./test
```
## Usage
```c
#include <stdio.h>

/* Include the library. */
#include <cstr.h>

int main(void) {
	/* Create a new string.
	 * Optionally, NULL can be passed to create an 
	 * empty string that consists of a single '\0'. */
	cstr_t *str = cstr_new("Hi, World");

	/* Append data at the end of the string. */
	cstr_push_back(str, '!');
	cstr_append(str, " How are you??");

	/* Prepend data at the beginning of the string. */
	cstr_prepend(str, "Hi, I'm World. ");
	cstr_push_front(str, 'H');

	/* Remove the last character. */
	cstr_pop_back(str);

	/* Remove the first character. */
	cstr_pop_front(str);

	/* Insert a character anywhere. */
	cstr_insert(str, 5, '-');

	/* Remove a character from anywhere. */
	cstr_remove(str, 5);

	/* Replace all occurrences of a word. */
	cstr_replace(str, "Hi", "Hello");

	/* Query the length of the string. */
	printf("%lu\n", cstr_len(str));

	/* Get a const pointer to the raw string. */
	printf("%s\n", cstr_view(str));

	/* Delete the string. */
	cstr_del(str);

	return 0;
}
```
