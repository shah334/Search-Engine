
// Implementation of a dictionary using an array and binary search
// It will inherit from the ArrayDictionary

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bsearch-dictionary.h"
// Constructor
BinarySearchDictionary::BinarySearchDictionary()
{
	sorted = false;
}
bool
BinarySearchDictionary::addRecord( KeyType key, DataType record) {
	sorted = false;
	return ArrayDictionary::addRecord(key, record);
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
BinarySearchDictionary::findRecord( KeyType key)
{
	if (!sorted) {
		sort();
		sorted = true;
	}
	int l = 0;
	int u = currentNumber - 1;
	while(l<=u){
		int mid = (l+u)/2;
		if(strcmp(key,array[mid].key)<0)
			u = mid - 1;
		else if(strcmp(key,array[mid].key)>0)
			l = mid + 1;
		else
			return array[mid].data;
	}
	// Use binary search
	return NULL;
	// Add your implementation here

	return NULL;
}


// Sort array using heap sort
void
BinarySearchDictionary::sort()
{
	Heap *hVar = new Heap(currentNumber);
	printf("Before\n");
	for (int i = 0; i < currentNumber; i++) {
		hVar->insert(array[i]);
		printf("%s\n", array[i].key);
	}

	printf("After\n");
	for (int i = 0; i < currentNumber; i++) {
		array[i] = hVar->removeMin();

		printf("%s\n", array[i].key);
	}
}




