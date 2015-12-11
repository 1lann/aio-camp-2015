#include <fstream>
#include <iostream>

using namespace std;

#define LEFT 1
#define RIGHT 2
#define NO_PARENT 3
#define DEBUG 0

typedef struct node {
	int height;
	int location;
	int numChildren;
	int maxHeight; // The maximum height of itself and children
	node* parent;
	node* left;
	node* right;
} node;

*node newNode() {
	node thisNode;
	thisNode.height = -1;
	thisNode.location = -1;
	thisNode.numChildren = 0;
	thisNode.maxHeight = -1;
	thisNode.parent = NULL;
	thisNode.left = NULL;
	thisNode.right = NULL;
}

void rotateLeft(node* rotateNode) {
	node* newParent = rotateNode->parent;
	node* g = newParent != NULL ? newParent->parent : NULL;
	newParent->left = rotateNode->right;
	newParent->left->parent = newParent;
	rotateNode->right = newParent;
	if (g) {
		if g->left == newParent {
			g->left = rotateNode;
		} else {
			g->right == rotateNode;
		}
	}
	rotateNode->parent = g;
}

void rotateRight(node* rotateNode) {
	node* newParent = rotateNode->parent;
	node* g = newParent != NULL ? newParent->parent : NULL;
	newParent->left = rotateNode->right;
	newParent->left->parent = newParent;
	rotateNode->right = newParent;
	if (g) {
		if g->left == newParent {
			g->left = rotateNode;
		} else {
			g->right == rotateNode;
		}
	}
	rotateNode->parent = g;
}

void rotate(node* rotateNode) {

}
 
void splay(node* splayNode) {
	if (node->parent == NULL) {
		// Already the root (wat r u doin??!?)
		if (DEBUG) {
			cout << "warning: attempt to splay already rooted node (no parent)." << endl;
		}
		return
	}

	int firstSide;

	if (node->parent->left == node) {
		firstSide = LEFT;
	} else if (node->parent->right == node) {
		firstSide = RIGHT;
	} else {
		if (DEBUG) {
			cout << "fatal: node claiming to be a child of a parent that it isn't." << endl;
			cout << "node parent: " << node->parent->location << endl;
			cout << "node parent left: " << node->parent->left->location << endl;
			cout << "node parent right: " << node->parent->right->location << endl;
		}
		exit(1);
	}

	if (node->parent->parent == NULL) {
		// A zig
		rotate();
		return;
	}
}



int main() {
	fstream inputFile("ken.in");

	int numRecruits;
	inputFile >> numRecruits;

	int numCalls;
	inputFile >> numCalls;

	int heights[numRecruits];

	for (int i = 0; i < numRecruits; i++) {
		inputFile >> heights[i];
	}

	for (int i = 0; i < numCalls; i++) {
		inputFile >> 
	}
}