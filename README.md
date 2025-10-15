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
	str_t *str = str_new("Hi, World");
	printf("%s\n", str_view(str));

	/* Append data at the end of the string. */
	str_push_back(str, '!');
	str_append(str, " How are you??");
	printf("%s\n", str_view(str));

	/* Prepend data at the beginning of the string. */
	str_prepend(str, "Hi, I'm World. ");
	str_push_front(str, 'H');
	printf("%s\n", str_view(str));

	/* Remove the last character. */
	str_pop_back(str);
	printf("%s\n", str_view(str));

	/* Remove the first character. */
	str_pop_front(str);
	printf("%s\n", str_view(str));

	/* Insert a character anywhere. */
	str_insert(str, 5, '-');
	printf("%s\n", str_view(str));

	/* Remove a character from anywhere. */
	str_remove(str, 5);
	printf("%s\n", str_view(str));

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
```
