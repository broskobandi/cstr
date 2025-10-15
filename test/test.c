#include <ctest.h>
#include <string.h>
#include "cstr.h"
#include <stdio.h>

void test_str_basic_functions() {
	str_t *str = str_new(NULL);
	CTEST(str);
	CTEST(str_len(str) == 0);
	CTEST(!strcmp(str_view(str), ""));
	CTEST(str_same(str, ""));
	CTEST(!str_has(str, "Hello"));
	CTEST(str_find(str, "Hello") == (size_t)-1);
	str_del(str);
	CTEST(!str_get_error());
	

	str_t *str2 = str_new("Hello, World!");
	CTEST(str2);
	CTEST(str_len(str2) == strlen("Hello, World!"));
	CTEST(!strcmp(str_view(str2), "Hello, World!"));
	CTEST(str_same(str2, "Hello, World!"));
	CTEST(str_has(str2, "Hello"));
	CTEST(str_find(str2, "World") == 7);
	str_del(str2);
	CTEST(!str_get_error());
}

void test_str_push_pop() {
	str_t *str = str_new(NULL);

	for (int i = 0; i < 1024; i++) {
		str_push_back(str, (char)i);
		CTEST(str_len(str) == (size_t)i + 1);
	}

	for (int i = 1024; i > 0; i--) {
		CTEST(*str_at(str, (size_t)(i - 1)) == (char)(i - 1));
		str_pop_back(str);
		CTEST(str_len(str) == (size_t)i - 1);
	}

	for (int i = 0; i < 1024; i++) {
		str_push_front(str, (char)i);
		CTEST(str_len(str) == (size_t)i + 1);
	}

	for (int i = 1024; i > 0; i--) {
		CTEST(*str_at(str, str_len(str) - 1) == 0);
		str_pop_front(str);
		CTEST(str_len(str) == (size_t)i - 1);
	}
	
	str_del(str);
	CTEST(!str_get_error());
}

void test_str_append_prepend() {
	str_t *str = str_new(NULL);

	str_append(str, "World!");
	CTEST(str_same(str, "World!"));

	str_prepend(str, "Jello");
	CTEST(str_same(str, "JelloWorld!"));

	str_insert(str, 5, ' ');
	CTEST(str_same(str, "Jello World!"));

	str_insert(str, 5, ',');
	CTEST(str_same(str, "Jello, World!"));

	str_insert(str, 5, ',');
	CTEST(str_same(str, "Jello,, World!"));

	str_remove(str, 5);
	CTEST(str_same(str, "Jello, World!"));
	str_replace(str, "Jello", "Hello");
	CTEST(str_has(str, "Hello"));
	CTEST(str_same(str, "Hello, World!"));
	fprintf(stderr, "%s\n", str_get_error());

	str_del(str);
	CTEST(!str_get_error());
}

void test_str_replace_expand() {
	str_t *str = str_new("Some short text.");
	str_replace(str, "short", "super duper long and absolutely awesome");
	CTEST(str_same(str, "Some super duper long and absolutely awesome text."));

	str_del(str);
	CTEST(!str_get_error());
}

void test_str_replace_shrink() {
	str_t *str = str_new("Some super duper long and absolutely awesome text.");
	str_replace(str, "super duper long and absolutely awesome", "short");
	CTEST(str_same(str, "Some short text."));

	str_del(str);
	CTEST(!str_get_error());
}

int main(void) {
	test_str_basic_functions();
	test_str_push_pop();
	test_str_append_prepend();
	test_str_replace_expand();
	test_str_replace_shrink();

	ctest_print_results();
	return 0;
}
