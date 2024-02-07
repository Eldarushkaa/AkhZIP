#include "algorithems.h"
#include "libraries/libsais.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>


int main(){
    int32_t freq[256];
    std::string DATA_FILE_NAME = "../huffman_test.txt";
    
    std::ifstream t(DATA_FILE_NAME);
    std::stringstream buffer;
    buffer << t.rdbuf();

    int32_t length = buffer.str().size();
    std::cout << "Data from " << DATA_FILE_NAME << " has been red. Size is " << length << " bytes" << std::endl;
    uint8_t lesgo[length + 1];
    lesgo[length] = 0;
    for (int i = 0; i < length; i++) lesgo[i] = buffer.str()[i];

    if (length < 100) std::cout << "ORIGINAL TEXT: " << lesgo << std::endl;

    int32_t extraspace[length];
    libsais_bwt(lesgo, lesgo, extraspace, length, 0, NULL);

    if (length < 100) std::cout << "LIBSAIS TEXT: " << lesgo << std::endl;
    
    uint8_t alphabet[0x100];
    
    for (int i = 0; i < 0x100; i++) alphabet[i] = i;
    mtf(lesgo, lesgo, length, alphabet);

    if (length < 100){
        std::cout << "MTF TEXT: ";
        for (int i = 0; i < length; i++) std::cout << lesgo[i] << "(" << (int) lesgo[i] << ")";
        std::cout << std::endl;
    }

    for (int i = 0; i < 0x100; i++) freq[i] = 0;
    for (int i = 0; i < length; i++) freq[lesgo[i]]++;

    std::vector<bool> U;
    std::vector<std::vector<bool> > symb_code(0x100);
    huffman(lesgo, U, length, freq, symb_code);
    std::cout <<"Okay lesgo length * 8 = " << length * 8 << " U.size() = " << U.size() << ". Compression ratio = " << (float)U.size() / length / 8 << std::endl;

    std::string huffman_code;
    huffman_dict_to_string(symb_code, huffman_code);

    std::string compressed_data;
    compressed_string(huffman_code, U, compressed_data);
    std::vector<bool> U2;
    decompressed_string(huffman_code, U2, compressed_data);
    std::cout << "U2.size() = " << U2.size() << std::endl;

    return 0;
}
