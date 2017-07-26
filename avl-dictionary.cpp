
// Implementation of a dictionary using an AVL tree
// AVL Trees are balanced binary trees 
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "avl-dictionary.h"

bool debug = false;

// Constructor
AVLDictionary::AVLDictionary()
{
	root = NULL;
	nElements = 0;
}

// Add a record to the dictionary. Returns false if key already exists
bool
AVLDictionary::addRecord( KeyType key, DataType record)
{
	AVLNode *n;
	n = new AVLNode();

	n->key = strdup(key);
    n->data = record;
    n->height = 1;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;

    if(root == NULL)
	{
        root = n;
		nElements++;
		
        return true;
    }

	    AVLNode *curr;
	curr = root;
	
    AVLNode *prev;
	prev = NULL;
	
    while(curr != NULL)
	{
        prev = curr;
        if (strcmp(key, curr->key) < 0)
		{
            curr = curr->left;
        }
        else if (strcmp(key, curr->key) > 0)
		{
            curr = curr->right;
        }
        else
		{
            curr->data = record;
            return false;
        }
    }

	if (strcmp(key, prev->key) < 0)
	{
        prev->left = n;
    }
    else
	{
        prev->right = n;
    }

	n->parent = prev;

	AVLNode *m;
	m = n->parent;
	
    while(m != NULL)
	{
        int maxHeight = 0;
        if(m->left != NULL)
            maxHeight = m->left->height;
        if(m->right != NULL && maxHeight < m->right->height)
            maxHeight = m->right->height;
        m->height = 1+maxHeight;
        m = m->parent;
    }
	nElements++;
	return true;
}

void
AVLDictionary::restructure(AVLNode * n) {
	
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
AVLDictionary::findRecord( KeyType key)
{
	AVLNode *current;
	current = root;
	
	while (current != NULL)
	{
		if (strcmp(current->key, key) > 0)
		{
			current = current->left;
			
		}
		else if (strcmp(current->key, key) < 0)
		{
			current = current->right;
		}
		else
		{
			return (DataType)current->data;//return if equal
		}
	}
	return NULL;
}

// Removes one element from the dictionary
bool
AVLDictionary::removeElement(KeyType key)
{
	// Add your implementation here
	AVLNode * n = root;
	if(findRecord(key)==NULL)
		return false;
	return true;
	/*TODO*/
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
AVLDictionary::keys(int * n)
{
	KeyType * a = (KeyType *) malloc(nElements * sizeof(KeyType));
	*n = 0;
	addKeysRecursive(root, a, n);

	return a;
}

// Add keys recursively
void
AVLDictionary::addKeysRecursive(AVLNode * node, KeyType * a, int * n) {
	if (node==NULL) {
		return;
	}
	a[*n] = node->key;
	(*n)++;
	addKeysRecursive(node->left, a, n);
	addKeysRecursive(node->right, a, n);
}