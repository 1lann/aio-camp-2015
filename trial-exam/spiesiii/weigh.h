/**
 * Problem: Spies III
 *
 * Interface for interacting with the judging software.
 *
 * See the problem description for usage.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the number of diamonds.
 *
 * Note that you MUST call this function before you call any other function
 * in this library.
 */
int getN(void);

/**
 * Weigh a set of diamonds.  Returns the weight.
 */
int weight(int diamond_set_size, int *diamond_set);

/**
 * Declare the locations of the diamonds.  Light then heavy.  Exits program.
 */

void diamonds(int a, int b);

#ifdef __cplusplus
}
#endif
