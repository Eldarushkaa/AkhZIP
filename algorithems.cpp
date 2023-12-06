#include "algorithems.h"
#include <string>


int32_t mtf(const uint8_t * T, uint8_t * U, int32_t n, uint8_t * alphabet){
    for (int i = 0; i < n; i++){
        uint8_t j = 0;
        uint8_t next = alphabet[0];
        while (alphabet[j] != T[i]){
            next = alphabet[j + 1];
            alphabet[j + 1] = alphabet[j];
            j++;
        }
        alphabet[0] = next;
        U[i] = j;
    }
    return 0;
}
