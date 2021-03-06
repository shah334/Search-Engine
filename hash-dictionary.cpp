
// Implementation of a dictionary using a hash table

#include <stdlib.h>
#include <string.h>
#include "hash-dictionary.h"

// Constructor
HashDictionary::HashDictionary()
{
  // Add your code here
	nElements = 0;
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
    return true;
  	}else{
    while(node!=NULL){
      if(strcmp(node->key,key)==0){
        node->data = record;
        return false;
      }
      node = node->next;
      }
	}

    HashNode * temp = new HashNode();
    temp->data = record;
    temp->key = strdup(key);
    temp->next = buckets[h];
    buckets[h] = temp;
    nElements++;
  return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
HashDictionary::findRecord( KeyType key)
{
	int h = hash(key);
  	HashNode * ent = buckets[h];

  	if(ent==NULL){
    	return false;
  	}else{
    while(ent!=NULL){
      if(strcmp(ent->key,key)==0){
      	 return ent->data;  
      }
      ent = ent->next;
    }
    return NULL;
  }
  delete ent;
}

// Removes one element from the table
bool
HashDictionary::removeElement(KeyType key)
{
  int h = hash(key);
  HashNode * node = buckets[h];
  HashNode * prev = NULL;
  while(node!=NULL){
	  if(strcmp(node->key,key)==0){
		  break;
	  }
	  prev = node;
	  node = node->next;
  }

  if(node==NULL)
  	return false;
  if(prev==NULL){
	  buckets[h] = node->next;
  }else{
	  prev->next = node->next;
  }
  //free(node);
  delete node;
  nElements--;
  return true;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
HashDictionary::keys(int * n)
{
	//KeyType * a = (KeyType *) malloc(nElements * sizeof(KeyType));
	int count = 0;
	*n = nElements;
	int i = 0;
	for (int h = 0; h < MaxBuckets; h++) {
		HashNode * n = buckets[h];
		while (n!=NULL) {
			count ++;
			n = n->next;
		}
	}

	KeyType * arr = new KeyType[count];
	for (int h = 0; h < MaxBuckets; h++) {
		HashNode * n = buckets[h];
		while (n!=NULL) {
			arr[i] = strdup(n->key);
			i++;
			n = n->next;
		}
	}
	*n = count;
	return arr;
}

