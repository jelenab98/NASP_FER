// nasp_1lab.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<algorithm>
#include<string>
#include<iostream>

using namespace std;


class Node {
public:
	char key;
	Node* left;
	Node* right;
	int height;

	Node(char value) {
		key = value;
		left = NULL;
		right = NULL;
		height = 1;
	}
};

int getHeight(Node *node);
int getMaxHeight(Node *node);
int getBalance(Node *node);
Node* rightRotation(Node *parent);
Node* leftRotation(Node *parent);
Node* minNode(Node* node);
Node* maxNode(Node* node);

class AVLTree {
private:
	Node * root;
	Node* deleteElement(Node* node, char key) {
		if (node == NULL) {
			return node;
		}

		if (key < node->key) {
			node->left = this->deleteElement(node->left, key);
		}
		else if (key > node->key) {
			node->right = this->deleteElement(node->right, key);
		}
		else {
			if (node->left == NULL) {
				return node->right;
			}
			else if (node->right == NULL) {
				return node->left;
			}
			else {
				if (getBalance(node) > 0) {
					Node* newNode = maxNode(node->left);
					node->key = newNode->key;
					node->left = this->deleteElement(node->left, newNode->key);
				}
				else {
					Node* newNode = minNode(node->right);
					node->key = newNode->key;
					node->right = this->deleteElement(node->right, newNode->key);
				}
			}
		}

		node->height = 1 + getMaxHeight(node);
		int balance = getBalance(node);

		if (balance > 1 && getBalance(node->left) >= 0) {
			return rightRotation(node);
		}
		if (balance < -1 && getBalance(node->right) <= 0) {
			return leftRotation(node);
		}
		if (balance > 1 && getBalance(node->left) < 0) {
			node->left = leftRotation(node->left);
			return rightRotation(node);
		}
		if (balance < -1 && getBalance(node->right) > 0) {
			node->right = rightRotation(node->right);
			return leftRotation(node);
		}

		return node;
	}
	Node * insertElement(Node* node, char key) {
		if (node == NULL) {
			return new Node(key);
		}

		if (key < node->key) {
			node->left = this->insertElement(node->left, key);
		}
		else if (key > node->key) {
			node->right = this->insertElement(node->right, key);
		}
		else {
			return node;
		}

		node->height = 1 + getMaxHeight(node);
		int balance = getBalance(node);

		if (balance > 1 && getBalance(node->left) >=0) {
			return rightRotation(node);
		}
		if (balance < -1 && getBalance(node->right) <= 0) {
			return leftRotation(node);
		}
		if (balance > 1 && getBalance(node->left) < 0) {
			node->left = leftRotation(node->left);
			return rightRotation(node);
		}
		if (balance < -1 && getBalance(node->right) > 0) {
			node->right = rightRotation(node->right);
			return leftRotation(node);
		}
		return node;
	}
	Node* searchTree(Node* node, char* key) {
		if (node == NULL) {
			return NULL;
		}
		if (node->key == *key) {
			return node;
		}
		else if (node->key < *key) {
			return this->searchTree(node->right, key);
		}
		else {
			return this->searchTree(node->left, key);
		}
	}
	void traverse_pre_order(Node *node, string *s) {
		if (node == NULL) return;
		
		(*s) += node->key; 
		
		this->traverse_pre_order(node->left, s);
		this->traverse_pre_order(node->right, s);
	}
	void traverse_post_order(Node *node, string *s) {
		if (node == NULL) return;
		
		this->traverse_post_order(node->left, s);
		this->traverse_post_order(node->right, s);
		
		(*s) += node->key;
	}

public:
	AVLTree() {
		root = NULL;
	}
	void DeleteElement(char key) {
		root = this->deleteElement(root, key);
	}
	void InsertElement(char key) {
		root = this->insertElement(root, key);
	}
	pair<char*, char*> getChildrenNodesValues(char *key = NULL) {
		Node* node;
		if (root == NULL) {
			return pair<char*, char*>(NULL, NULL);
		}
		
		if (key == NULL or *key == root->key) {
			return pair<char*, char*>(root->left ? &(root->left->key) : NULL, root->right ? &(root->right->key) : NULL);

		}

		node = this->searchTree(root, key);

		if (node == NULL) {
			return pair<char*, char*>(NULL, NULL);
		}

		return pair<char*, char*>(node->left ? &(node->left->key) : NULL, node->right ? &(node->right->key) : NULL);

		
	}
	char *getRootNode() {
		return &(root->key);
	}
	string PreOrderTraversal() {
		string s = "";
		this->traverse_pre_order(root, &s);
		return s;
	} 
	string PostOrderTraversal() {
		string s = "";
		this->traverse_post_order(root, &s);
		return s;
	}
};

int getHeight(Node *node) {
	if (node == NULL) {
		return 0;
	}
	else {
		return node->height;
	}
}

int getMaxHeight(Node *node) {
	return max(getHeight(node->left), getHeight(node->right));
}

int getBalance(Node *node) {
	if (node == NULL) {
		return 0;
	}
	else {
		return getHeight(node->left) - getHeight(node->right);
	}
}

Node* minNode(Node* node) {
	Node* tmp = node;

	while (tmp->left != NULL) {
		tmp = tmp->left;
	}

	return tmp;
}

Node* maxNode(Node* node) {
	Node* tmp = node;

	while (tmp->right != NULL) {
		tmp = tmp->right;
	}

	return tmp;
}

Node *rightRotation(Node *parent) {
	Node *newParent = parent->left;
	Node *newChild = newParent->right;

	newParent->right = parent;
	parent->left = newChild;

	parent->height = 1 + getMaxHeight(parent) ;
	newParent->height = 1 + getMaxHeight(newParent);

	return newParent;
}

Node *leftRotation(Node *parent) {
	Node *newParent = parent->right;
	Node *newChild = newParent->left;

	newParent->left = parent;
	parent->right = newChild;
	
	parent->height = 1 + getMaxHeight(parent);
	newParent->height = 1 + getMaxHeight(newParent);

	return newParent;
}

int main() {
	AVLTree *t = new AVLTree();
	t->InsertElement('A');
	t->InsertElement('C');
	t->InsertElement('B');
	t->InsertElement('L');
	t->InsertElement('D');
	t->InsertElement('K');
	t->InsertElement('G');
	t->InsertElement('H');
	t->InsertElement('R');
	t->InsertElement('I');
	t->InsertElement('U');
	t->InsertElement('E');
	
	cout << t->PreOrderTraversal() << endl;

	t->DeleteElement('R');

	cout << t->PreOrderTraversal() << endl;

	return 0;
}


