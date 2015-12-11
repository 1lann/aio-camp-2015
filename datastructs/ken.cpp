#include <fstream>
#include <iostream>
#include <stdlib.h>

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

node* rootNode = NULL;

node* newNode() {
	node thisNode;
	thisNode.height = -1;
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
		if (g->left == newParent) {
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
	newParent->right = rotateNode->left;
	newParent->right->parent = newParent;
	rotateNode->left = newParent;
	if (g) {
		if (g->right == newParent) {
			g->right = rotateNode;
		} else {
			g->left == rotateNode;
		}
	}
	rotateNode->parent = g;
}

void rotate(node* rotateNode) {
	if (rotateNode->parent == NULL) {
		if (DEBUG) {
			cout << "warning: attempt to rotate already rooted node (no parent)." << endl;
		}
		return;
	}

	if (rotateNode->parent->left == rotateNode) {
		rotateLeft(rotateNode);
		return;
	}

	if (rotateNode->parent->right == rotateNode) {
		rotateRight(rotateNode);
		return;
	}
}
 
void splay(node* splayNode) {
	while 1 {
		if (splayNode->parent == NULL) {
			rootNode = splayNode;
			return;
		}

		if (splayNode->parent->parent == NULL) {
			// A zig
			rotate(splayNode);
			rootNode = splayNode;
			return;
		}

		int firstSide;

		if (splayNode->parent->left == splayNode) {
			firstSide = LEFT;
		} else if (splayNode->parent->right == splayNode) {
			firstSide = RIGHT;
		} else {
			if (DEBUG) {
				cout << "fatal: primary node claiming to be a child of a parent that it isn't." << endl;
				cout << "node parent: " << splayNode->parent->location << endl;
				cout << "node parent left: " << splayNode->parent->left->location << endl;
				cout << "node parent right: " << splayNode->parent->right->location << endl;
			}
			exit(1);
		}

		node* parentNode = splayNode->parent;

		int secondSide;

		if (parentNode->parent->left == parentNode) {
			secondSide = LEFT;
		} else if (parentNode->parent->right == parentNode) {
			secondSide = RIGHT;
		} else {
			if (DEBUG) {
				cout << "fatal: secondary node claiming to be a child of a parent that it isn't." << endl;
				cout << "node parent: " << parentNode->parent->location << endl;
				cout << "node parent left: " << parentNode->parent->left->location << endl;
				cout << "node parent right: " << parentNode->parent->right->location << endl;
			}
			exit(1);
		}

		if (firstSide == secondSide) {
			// A zig-zig
			rotate(splayNode->parent);
			rotate(splayNode);
		} else {
			// A zig-zag
			rotate(splayNode);
			rotate(splayNode);
		}
	}
}

void updateParentNodes(node* startNode) {
	if (startNode->parent == NULL) {
		return;
	}

	if (startNode->height > startNode->maxHeight) {
		startNode->maxHeight = startNode->height;
	}

	if (startNode->maxHeight > startNode->parent->maxHeight) {
		startNode->parent->maxHeight = startNode->maxHeight;
		updateParentNodes(startNode->parent);
		return;
	}
}

void incrementParents(node* startNode) {
	if (startNode->parent == NULL) {
		return;
	}

	startNode->parent->numChildren++;
	incrementParents(startNode->parent)
}

node* find(int position) {

}

int getPosition(node* thisNode) {
	if (thisNode->parent == NULL) {
		if (thisNode->left) == NULL {
			return 0;
		} else {
			return thisNode->left->numChildren;
		}
	} else {
		if (thisNode->left) == NULL {
			return getPosition(thisNode->parent) + 1;
		} else {
			return getPosition(thisNode->parent) + thisNode->left->numChildren;
		}
	}
}

void move(int position, int newPosition) {

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