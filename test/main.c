#include "../hashtable.h"
#include "common.h"

#include <string.h>

int tests(int argc, const char* argv[]);

/* ------------------------------------------------------ */
typedef struct strng {
	char data[0xFF];
} strng ;

#define strng_data(S_) S_.data

strng new_strng( const int sze_ , const char str_literal_[0xFF] ) 
{
	assert( sze_ < 0xFF );
	strng specimen_ = {0};
	memcpy_s(specimen_.data, 0xFF, str_literal_, sze_);
	return specimen_;
}

strng set_strng(const char str_[0xFF]) {
	return new_strng( strlen(str_), str_ );
}

typedef strng key_type;
typedef strng val_type;

#define VAL_TYPE_FMT "%s"
#define KEY_TYPE_FMT "%s"

/* ------------------------------------------------------ */
/* attempt to use this for strings hash table */
int strings_ht_append(HashTable* table, key_type next_name) {

	int rez = ht_insert(table, &next_name, &next_name);

	assert( rez != HT_ERROR);

	return rez;
}

val_type strings_ht_find(HashTable* table, key_type name) {

	if (ht_contains(table, &name)) {
		/* 
		val_type found_ = *(val_type*)ht_lookup(&table, &name);
		Or use convenience macros 
		*/
		val_type found_ = HT_LOOKUP_AS(val_type, table, &name);
		return found_;
	}
	return set_strng("NULL") ;
}
/* ------------------------------------------------------ */
#define SHOW_FIND(T_, K_)  \
	do { \
		val_type v_ = strings_ht_find(T_, K_); \
		printf("\n" VAL_TYPE_FMT " find result is: " VAL_TYPE_FMT, \
					 K_.data , v_.data );    \
	} while (0)

int strings_ht() {
	// tests(argc, argv);

	HashTable* table = NULL;// DBJ changed to NULL pointer requirement

	/* Choose initial capacity of 10 */
	/* Specify the size of the keys and values you want to store once */
	int errc = ht_setup(&table, sizeof(key_type), sizeof(val_type), 10);

	if (errc == HT_ERROR) return HT_ERROR;

	// ht_reserve(table, 100);

	strng strngs[] = { set_strng("Luke"), set_strng("Layla Vader"), set_strng("D'woku Chuwi") };

	strings_ht_append(table, strngs[0]);
	strings_ht_append(table, strngs[1]);
	strings_ht_append(table, strngs[2]);

	SHOW_FIND(table, strngs[0]);
	SHOW_FIND(table, strngs[1]);
	SHOW_FIND(table, strngs[2]);

	ht_erase(table, & strngs[0]);
	ht_erase(table, & strngs[1]);
	ht_erase(table, & strngs[2]);

	ht_clear(table);
	ht_destroy(table);

	free(table);// DBJ added this

#undef SHOW_FIND
	return EXIT_SUCCESS;
}
/* ------------------------------------------------------ */
int main(int argc, const char* argv[]) {
	tests(argc, argv);
	strings_ht();
	printf(VT100_LIGHT_GREEN "\n\nDONE" VT100_RESET);

	#ifdef _MSC_VER
	system("@pause");
	#endif

	return 42;
}
