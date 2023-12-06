typedef signed char int8_t;
typedef unsigned char   uint8_t;
typedef short  int16_t;
typedef unsigned short  uint16_t;
typedef int  int32_t;
typedef unsigned   uint32_t;

/**
* Constructs the burrows-wheeler transformed string (BWT) of a given string using libsais context.
* @param T [0..n-1] The input string.
* @param U [0..n-1] The output string (can be T).
* @param n The length of the given string.
* @return 0 if no error occurred, -1 or -2 otherwise.
*/
int32_t mtf(const uint8_t * T, uint8_t * U, int32_t n);
