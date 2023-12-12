#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>


/**
* Constructs the burrows-wheeler transformed string (BWT) of a given string using libsais context.
* @param T [0..n-1] The input string.
* @param U [0..n-1] The output string (can be T).
* @param n The length of the given string.
* @return 0 if no error occurred, -1 or -2 otherwise.
*/
int32_t mtf(uint8_t * T, uint8_t * U, int32_t n, uint8_t * alphabet);


/**
* Constructs the burrows-wheeler transformed string (BWT) of a given string using libsais context.
* @param T [0..n-1] The output string.
* @param U [0..n-1] The input string.
* @param n The length of the given string.
* @return 0 if no error occurred, -1 or -2 otherwise.
*/
int32_t reverse_mtf(uint8_t * T, uint8_t * U, int32_t n, uint8_t * alphabet);

int32_t huffman(uint8_t * T, std::vector<bool>& U, int32_t n, int32_t * freq);