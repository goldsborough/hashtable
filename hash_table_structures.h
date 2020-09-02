#pragma once

#ifndef HASH_TABLE_STRUCTURES_INC_
#define HASH_TABLE_STRUCTURES_INC_

/*
separate header -- also included when low level testing 
*/

typedef int (*comparison_t)(void*, void*, size_t);
typedef size_t (*hash_t)(void*, size_t);

/****************** STRUCTURES ******************/

typedef struct HTNode {
	struct HTNode* next;
	void* key;
	void* value;

} HTNode;

typedef struct HashTable {
	size_t size;
	size_t threshold;
	size_t capacity;

	size_t key_size;
	size_t value_size;

	comparison_t compare;
	hash_t hash;

	HTNode** nodes;

} HashTable;

#endif// !HASH_TABLE_STRUCTURES_INC_
