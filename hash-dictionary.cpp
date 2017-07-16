
// Implementation of a dictionary using a hash table

#include <stdlib.h>
#include <string.h>
#include "hash-dictionary.h"

// Constructor
HashDictionary::HashDictionary()
{
  // Add your code here
	for(int i=0;i<MaxBuckets;i++){
		buckets[i] = NULL;
	}
}

int
HashDictionary::hash(KeyType key) {
  // Add your code here
  int sum = 0;
  int len = strlen(key);
  for (int i = 0; i < len; i++) {
		sum += i*key[i];
  }
  return sum%MaxBuckets;
}

// Add a record to the dictionary. Returns false if key already exists
bool
HashDictionary::addRecord( KeyType key, DataType record)
{
  // Add your code here
	int h = hash(key);
	HashNode * node = buckets[h];
	if(node==NULL){
    HashNode * ent = new HashNode();
    ent->key = strdup(key);
    ent->data = record;
    ent->next = NULL;
    buckets[h] = ent;
    return false;
  	}else{
    while(node!=NULL){
      if(strcmp(node->key,key)==0){
        node->data = record;
        return true;
      }
      node = node->next;
      }
	}

    HashNode * temp = new HashNode();
    temp->data = record;
    temp->key = strdup(key);
    temp->next = buckets[h];
    buckets[h] = temp;

  return false;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
HashDictionary::findRecord( KeyType key)
{
	return NULL;
}

// Removes one element from the table
bool
HashDictionary::removeElement(KeyType key)
{
  // Add your code here
	return true;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
HashDictionary::keys(int * n)
{
	KeyType * a = (KeyType *) malloc(nElements * sizeof(KeyType));

	*n = nElements;
	int i = 0;
	for (int h = 0; h < MaxBuckets; h++) {
		HashNode * n = buckets[h];
		while (n!=NULL) {
			a[i] = n->key;
			i++;
			n = n->next;
		}
	}
	*n = nElements;
	return a;
}

