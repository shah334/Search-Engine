#include <stdlib.h>
#include <stdio.h>
#include "array-dictionary.h"
#include <string.h>
#include <assert.h>

class Heap : public ArrayDictionary {
	public:
	int n;
	int nMax;
	ArrayDictionaryNode * arrray;
	Heap(int maxSize);
	void insert(ArrayDictionaryNode node);
	ArrayDictionaryNode removeMin();
	~Heap();

};
#define left_child(i) (2*(i)+1)
#define right_child(i) (2*(i)+2)
#define iparent(i) ((i-1)/2)