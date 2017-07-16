
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary

#include <stdlib.h>
#include <string.h>

#include "array-dictionary.h"

// Constructor
ArrayDictionary::ArrayDictionary()
{
  // Add your code here
	int maxNumber = 10000;
	array = new ArrayDictionaryNode[maxNumber];
	int currentNumber = 0;
}

// Add a record to the dictionary. Returns false if key already exists
bool
ArrayDictionary::addRecord( KeyType key, DataType record)
{
        // Add your code here
	for(int i=0;i<currentNumber;i++){
		if(strcmp(array[i].key,key)==0)
			return false;
	}

	if(currentNumber == maxNumber){
		maxNumber = 2 * maxNumber;
		ArrayDictionaryNode * arr = new ArrayDictionaryNode[maxNumber];
		for(int i=0;i<maxNumber/2;i++){
			arr[i] = array[i];
		}

		delete [] array;
		array = arr;
	}
	array[currentNumber].key = strdup(key);
	array[currentNumber].data = record;
	currentNumber ++;
	return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
ArrayDictionary::findRecord( KeyType key)
{
        // add your code here
	for(int i=0;i<currentNumber;i++){
		if(strcmp(array[i].key,key)==0){
			return array[i].data;
		}
	}
	return NULL;
}

// Removes one element from the table
bool
ArrayDictionary::removeElement(KeyType key)
{
        // Add your code here
	for(int i=0;i<currentNumber;i++){
		if(!strcmp(array[i].key,key)){
			for(int j=i+1;j<currentNumber;j++){
				array[j-1] = array[j];
			}
			currentNumber --;
			return true;//done removing		
		}
	}
	return false;//could not remove
	
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
ArrayDictionary::keys(int * n)
{
        // Add yoru code here
	 if(currentNumber == 0)
		return NULL;
	 KeyType * arr = new KeyType[currentNumber];//this will be returned

	 for(int i=0;i<currentNumber;i++){
	 	arr[i] = strdup(array[i].key);
	 }
	 return arr;
}
