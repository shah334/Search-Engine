#include "heap.h"

heap::Heap(int maxSize){
	n = 0;
	nMax = maxSize;
	array = new ArrayDictionaryNode[maxSize];
}

heap::~Heap(){
	delete [] array;
}

void
heap::insert(ArrayDictionaryNode node){
	assert(n<nMax);
	array[n] = node;
	n++;
	int child = n-1;
	int parent = iparent(child);
	while(child>0){
		if(array[child]>array[parent]){
			break;
		}
	}
	ArrayDictionaryNode temp = array[child];
	array[child] = array[parent];
	array[parent] = temp;
}

ArrayDictionaryNode
heap::removeMin(){
	assert(n>0);
	ArrayDictionaryNode node = array[0];
	n--;
	if(n==0){
		return node;
	}
	array[0] = array[n];
	int parent = 0;
	int left = left_child(parent);
	int right = right_child(parent);
	while(left<n){
		int minChild = left;
		if(right<n && array[right]<array[left]){
			minChild = right;
		}
		if(array[parent]<array[minChild]){
			break;
		}
		ArrayDictionaryNode node = array[child];
		array[child] = array[minChild];
		array[minChild] = node;
		parent = minChild;
		left = left_child(parent);
		right = right_child(parent);
	}
	return node;
}
