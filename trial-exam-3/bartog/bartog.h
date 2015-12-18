#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the number of nodes in the tree.
 * This MUST be called before any other functions.
 */
int getN();

/**
 * Returns the id of the lowest common ancestor of two nodes.
 */
int getLCA(int, int);

/**
 * Called to exit the program. Argument must be an array of N integers,
 * array[0] should have the id of the parent of node 1.
 * array[i] = id of parent of node with id i+1
 */
void finish(int*);

#ifdef __cplusplus
}
#endif
