#include <assert.h>
#include <stdio.h>

#include "hashtable.h"

int main(int argc, const char* argv[]) {
	int i, key, value;

	printf("TESTING SETUP ...\n");
	HashTable table = HT_INITIALIZER;
	assert(!ht_is_initialized(&table));
	ht_setup(&table, sizeof(int), sizeof(int), 0);
	assert(ht_is_initialized(&table));

	printf("TESTING INSERT ...\n");

	for (key = 0, value = 1; key <= 1000; ++key, ++value) {
		assert(ht_insert(&table, &key, &value) == HT_INSERTED);
		assert(table.size == value);
	}

	printf("TESTING UPDATE ...\n");

	size_t previous_size = table.size;
	for (i = 1; i <= 1000; ++i) {
		assert(ht_insert(&table, &i, &i) == HT_UPDATED);
		assert(table.size == previous_size);
	}

	printf("TESTING CONTAINS ...\n");

	for (i = 1; i <= 1000; ++i) {
		assert(ht_contains(&table, &i) == HT_FOUND);
	}

	for (i = 1001; i < 1100; ++i) {
		assert(ht_contains(&table, &i) == HT_NOT_FOUND);
	}

	printf("TESTING LOOKUP ...\n");

	for (i = 1; i <= 1000; ++i) {
		assert(HT_LOOKUP_AS(int, &table, &i) == i);
	}

	for (i = 1001; i < 1100; ++i) {
		assert(ht_lookup(&table, &i) == NULL);
	}

	printf("TESTING REMOVAL ...\n");

	for (i = table.size - 1; !ht_is_empty(&table); --i) {
		assert(ht_erase(&table, &i) == HT_SUCCESS);
		assert(table.size == i);
	}

	printf("TESTING RESERVE ...\n");
	assert(ht_reserve(&table, 200) == HT_SUCCESS);
	assert(table.size == 0);
	assert(table.capacity == 200 / HT_LOAD_FACTOR);

	printf("TESTING CLEAR ...\n");
	assert(ht_clear(&table) == HT_SUCCESS);

	assert(table.size == 0);
	assert(ht_is_empty(&table));
	assert(table.capacity == HT_MINIMUM_CAPACITY);

	ht_destroy(&table);

	printf("\033[92mALL TEST PASSED\033[0m\n");
}
