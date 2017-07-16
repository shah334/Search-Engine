
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
void
BinarySearchDictionary::initHeap(){
	n = 0;
	max = maxNumber;
	heap = new ArrayDictionaryNode[max];
}
void 
BinarySearchDictionary::insert(KeyType key, DataType record){
	if(n==max){
		max = max * 2;
		ArrayDictionaryNode * arr = new ArrayDictionaryNode[max];
		for(int i=0;i<max/2;i++){
			arr[i] = heap[i];
		}

		delete [] heap;
		heap = arr;
	}//resize if full
	heap[n].key = strdup(key);
	heap[n].data = record;
	n++;
	int child = n-1;
	int parent = iparent(child);
	while(child > 0){
		if((strcmp(heap[child].key,heap[parent].key))>0)
			break;

		ArrayDictionaryNode temp = heap[child];
		heap[child]=heap[parent];
		heap[parent]=temp;
	}
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
	
	// Use binary search

	// Add your implementation here

	return NULL;
}


// Sort array using heap sort
void
BinarySearchDictionary::sort()
{
	//printf("Before\n");
	//for (int i = 0; i < currentNumber; i++) {
	//	printf("%s\n", array[i].key);
	//}

        // Add your code here

	//printf("After\n");
	//for (int i = 0; i < currentNumber; i++) {
	//	printf("%s\n", array[i].key);
	//}
}




