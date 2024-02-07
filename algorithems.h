#include <stdint.h>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <bitset>


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

int32_t huffman(uint8_t * T, std::vector<bool>& U, int32_t n, int32_t * freq, std::vector<std::vector<bool> >& symb_code);

int32_t huffman_dict_to_string(std::vector<std::vector<bool> >& symb_code, std::string& output_dict);

int32_t binary_vector_to_string(std::vector<bool>& binary, std::string& output);

int32_t string_to_binary_vector(std::vector<bool>& binary, std::string& output);

int32_t huffman_string_to_dict(std::vector<std::vector<bool> >& symb_code, std::string& output_dict);

int32_t compressed_string(std::string& huffman_code, std::vector<bool>& U, std::string& compressed_data);

int32_t decompressed_string(std::string& huffman_code, std::vector<bool>& U, std::string& compressed_data);
