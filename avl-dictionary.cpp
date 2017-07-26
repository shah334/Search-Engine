
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
	
	
	AVLNode *n = new AVLNode();
	
    n->key = key;
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

    AVLNode *curr = root;
	
    AVLNode *prev = NULL;
	
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
        int maxheight = 0;
        if(m->left != NULL)
            maxheight = m->left->height;
        if(m->right != NULL && maxheight < m->right->height)
            maxheight = m->right->height;
        m->height = 1+maxheight;
        m = m->parent;
    }
	restructure(n);
	nElements++;
		
	return true;
}

void
AVLDictionary::restructure(AVLNode * n) {
	//Balance the tree starting at n 
	AVLNode *z;
	z = n->parent;
	
    while(z != NULL)
	{
        int hl = 0;
        if(z->left != NULL)
		{
            hl = z->left->height;
        }
		
        int hr = 0;
        if(z->right != NULL)
		{
            hr = z->right->height;
        }

        int heightdiff = hl - hr;
        if(heightdiff < 0)
            heightdiff = -heightdiff;

        if(hl > hr)
            z->height = 1+hl;
        else
            z->height = 1+hr;

        if(heightdiff <= 1)
		{
            z = z->parent;
            continue;
        }

        AVLNode *y = NULL;
        int maxheight = 0;
        if(z->left != NULL)
		{
            y = z->left;
            maxheight = y->height;
        }
        if(z->right != NULL && z->right->height > maxheight)
		{
            y = z->right;
            maxheight = y->height;
        }

        AVLNode *x = NULL;
        maxheight = 0;
        if(y->left != NULL)
		{
            x = y->left;
            maxheight = x->height;
        }
        if(y->right != NULL && y->right->height > maxheight)
		{
            x = y->right;
            maxheight = x->height;
        }
        assert(x != NULL);

        AVLNode * a, * b, * c, * t0, * t1, * t2, * t3;
        if(z->right == y)
		{
            if(y->right == x)
			{
                a = z;
                b = y;
                c = x;
                t0 = z->left;
                t1 = y->left;
                t2 = x->left;
                t3 = x->right;
            }
            else
			{
                a = z;
                b = x;
                c = y;
                t0 = z->left;
                t1 = x->left;
                t2 = y->left;
                t3 = y->right;
            }
        }
        else 
		{
            if(y->left == x)
			{
                a = x;
                b = y;
                c = z;
                t0 = x->left;
                t1 = x->right;
                t2 = y->right;
                t3 = z->right;
            }
            else
			{
                a = y;
                b = x;
                c = z;
                t0 = y->left;
                t1 = x->left;
                t2 = x->right;
                t3 = z->right;
            }
        }

        AVLNode *p;
		p = z->parent;
        if(p == NULL)
		{
            root = b;
        }
        else
		{
            if(b->left == z)
                p->left = b;
            else
                p->right = b;
        }
		
        b->parent = p;
        b->left = a;
        b->right = c;
        a->parent = b;
        a->left = t0;
        a->right = t1;
        c->parent = b;
        c->left = t2;
        c->right = t3;

        if(t0 != NULL)
            t0->parent = a;
        if(t1 != NULL)
            t1->parent = a;
        if(t2 != NULL)
            t2->parent = c;
        if(t3 != NULL)
            t3->parent = c;

        maxheight = 0;
        if(a->left != NULL)
            maxheight = a->left->height;
        if(a->right != NULL && a->right->height > maxheight)
            maxheight = a->right->height;
        a->height = 1+maxheight;

        maxheight = 0;
        if(c->left != NULL)
            maxheight = c->left->height;
        if(c->right != NULL && c->right->height > maxheight)
            maxheight = c->right->height;
        c->height = 1+maxheight;

        maxheight = 0;
        if(b->left != NULL)
            maxheight = b->left->height;
        if(b->right != NULL && b->right->height > maxheight)
            maxheight = b->right->height;
        b->height = 1+maxheight;

        z = z->parent;
    }
	//Go upwards until root is found

        // See class notes

	// Add your implementation here
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
AVLDictionary::findRecord( KeyType key)
{
        // Add your implementation here
	AVLNode * n = root;

	while(n!=NULL){
		if(strcmp(key,n->key)==0){
			return n->data;
		}
		else if(strcmp(key,n->key)<0){
			n = n->left;
		}else{
			n = n->right;
		}
	}
	return NULL;
}

// Removes one element from the dictionary
bool
AVLDictionary::removeElement(KeyType key)
{
	if (debug) {
		printf("------------------------------------\n");
		printf("removeElement(\"%s\")\n",  key);
		printf("---------- Before -----------------\n");
		printNode("", root, 0);
	}


	// Add your implementation here
	if(findRecord(key)==NULL){
		return false;
	}else{
		AVLNode * n = root;
		AVLNode * prev = NULL;
		while(n!=NULL){
			prev = n;
			if(strcmp(key, n->key) < 0){
				n = n->left;
			}else if(strcmp(key, n->key) > 0){
				n = n->right;
			}else{
			
			}
		}
	}
	return false;
	
	if (debug) {
		printf("---------- After -----------------\n");
		printNode("", root, 0);

		checkRecursive(root);
	}
	
	return true;
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

