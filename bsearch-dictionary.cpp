
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
	//printf("Inserting %s\n", heap[n].key);
	heap[n].data = record;
	n++;
	int child = n-1;
	int parent = iparent(child);
	while(child > 0){
		if((strcmp(heap[child].key,heap[parent].key))>0)
			break;

		ArrayDictionaryNode temp = heap[child];
		//printf("swapping %s\n", temp.key);
		heap[child]=heap[parent];
		heap[parent]=temp;
	}
}

ArrayDictionaryNode
BinarySearchDictionary::removeMin(){
	if(n>0){

		ArrayDictionaryNode min = heap[0];
		printf("removing %s\n",min.key);
		n--;
		if(n==0){
			return min;
		}
		heap[0] = heap[n-1];
		int parent = 0;
		int left = left_child(parent);
		int right = right_child(parent);

		while(left<n){
			int m = left;
			if(right<n && (strcmp(heap[right].key, heap[left].key) < 0)){
				m = right;
			}  
			if(strcmp(heap[parent].key, heap[m].key)<0){
				break;
			}
			ArrayDictionaryNode temp = heap[m];
			heap[m] = heap[parent];
			heap[parent] = temp;
			parent = m;
			left = left_child(parent);
			right = right_child(parent);
		}

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
	printf("Before\n");
	for (int i = 0; i < currentNumber; i++) {
		insert(array[i].key,array[i].data);
		printf("%s\n", array[i].key);
	}

        

	printf("After\n");
	for (int i = 0; i < currentNumber; i++) {
		array[i] = removeMin();
		printf("%s\n", array[i].key);
	}
}




