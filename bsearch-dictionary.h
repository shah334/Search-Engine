
// Implementation of a dictionary using an array and binary search
// The class inherits from ArrayDictionary

#include "array-dictionary.h"

class BinarySearchDictionary : public ArrayDictionary {
  // Add any member variables you need
  //for heap
  int n;
  int max;
  ArrayDictionaryNode * heap;

  bool sorted;
public:
  // Constructor
  BinarySearchDictionary();

  void initHeap();
  void insert(KeyType key, DataType record);

  
  bool addRecord( KeyType key, DataType record);
  KeyType removeMin();
  #define left_child(i) (2*(i) + 1);
  #define right_child(i) (2*(i) + 2);
  #define iparent(i) ((i-1)/2);

  // Find a key in the dictionary and return corresponding record or NULL
  // Use binary search
  DataType findRecord( KeyType key);

  // Sort array using heap sort.
  void sort();

    // Removes one element from the table
  //bool removeElement(KeyType key);

  // Returns all the elements in the table as an array of strings.
  // *n is the size of the table and it is returned by reference
  //KeyType * keys(int * n);

  // Add other methods you may need
};

