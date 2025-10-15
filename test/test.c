#include <ctest.h>
#include <string.h>
#include "cstr.h"
#include <stdio.h>

void test_cstr_basic_functions() {
	cstr_t *str = cstr_new(NULL);
	CTEST(str);
	CTEST(cstr_len(str) == 0);
	CTEST(!strcmp(cstr_view(str), ""));
	CTEST(cstr_same(str, ""));
	CTEST(!cstr_has(str, "Hello"));
	CTEST(cstr_find(str, "Hello") == (size_t)-1);
	cstr_del(str);
	CTEST(!cstr_get_error());
	

	cstr_t *str2 = cstr_new("Hello, World!");
	CTEST(str2);
	CTEST(cstr_len(str2) == strlen("Hello, World!"));
	CTEST(!strcmp(cstr_view(str2), "Hello, World!"));
	CTEST(cstr_same(str2, "Hello, World!"));
	CTEST(cstr_has(str2, "Hello"));
	CTEST(cstr_find(str2, "World") == 7);
	cstr_del(str2);
	CTEST(!cstr_get_error());
}

void test_cstr_push_pop() {
	cstr_t *str = cstr_new(NULL);

	for (int i = 0; i < 1024; i++) {
		cstr_push_back(str, (char)i);
		CTEST(cstr_len(str) == (size_t)i + 1);
	}

	for (int i = 1024; i > 0; i--) {
		CTEST(*cstr_at(str, (size_t)(i - 1)) == (char)(i - 1));
		cstr_pop_back(str);
		CTEST(cstr_len(str) == (size_t)i - 1);
	}

	for (int i = 0; i < 1024; i++) {
		cstr_push_front(str, (char)i);
		CTEST(cstr_len(str) == (size_t)i + 1);
	}

	for (int i = 1024; i > 0; i--) {
		CTEST(*cstr_at(str, cstr_len(str) - 1) == 0);
		cstr_pop_front(str);
		CTEST(cstr_len(str) == (size_t)i - 1);
	}
	
	cstr_del(str);
	CTEST(!cstr_get_error());
}

void test_cstr_append_prepend() {
	cstr_t *str = cstr_new(NULL);

	cstr_append(str, "World!");
	CTEST(cstr_same(str, "World!"));

	cstr_prepend(str, "Jello");
	CTEST(cstr_same(str, "JelloWorld!"));

	cstr_insert(str, 5, ' ');
	CTEST(cstr_same(str, "Jello World!"));

	cstr_insert(str, 5, ',');
	CTEST(cstr_same(str, "Jello, World!"));

	cstr_insert(str, 5, ',');
	CTEST(cstr_same(str, "Jello,, World!"));

	cstr_remove(str, 5);
	CTEST(cstr_same(str, "Jello, World!"));
	cstr_replace(str, "Jello", "Hello");
	CTEST(cstr_has(str, "Hello"));
	CTEST(cstr_same(str, "Hello, World!"));
	fprintf(stderr, "%s\n", cstr_get_error());

	cstr_del(str);
	CTEST(!cstr_get_error());
}

void test_cstr_replace_expand() {
	cstr_t *str = cstr_new("Some short text.");
	cstr_replace(str, "short", "super duper long and absolutely awesome");
	CTEST(cstr_same(str, "Some super duper long and absolutely awesome text."));

	cstr_del(str);
	CTEST(!cstr_get_error());
}

void test_cstr_replace_shrink() {
	cstr_t *str = cstr_new("Some super duper long and absolutely awesome text.");
	cstr_replace(str, "super duper long and absolutely awesome", "short");
	CTEST(cstr_same(str, "Some short text."));

	cstr_del(str);
	CTEST(!cstr_get_error());
}

int main(void) {
	test_cstr_basic_functions();
	test_cstr_push_pop();
	test_cstr_append_prepend();
	test_cstr_replace_expand();
	test_cstr_replace_shrink();

	ctest_print_results();
	return 0;
}
