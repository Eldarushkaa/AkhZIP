#include "algorithems.h"
#include "libraries\libsais.h"
#include "writing.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>


int main(){
    // int weight[0x200];
    // int count = 0;
    // for (auto &i: weight) i = 0;
    // std::ifstream f("C:\\Users\\FlexStreet\\Documents\\VS Code projects\\akhzip\\main.cpp");
    // while (!f.eof())
    // {
    //     unsigned char ch;
    //     f.read((char *)&ch, sizeof(ch));
    //     count++;
    //     weight[ch]++;
    // }
    // std::multimap<int, char> sorted_weight;
    // for (int i = 0; i < 0x100; i++)
    //     sorted_weight.insert(std::make_pair(weight[i], (char)i));
    // for (auto i: sorted_weight)
    //     if (i.first > 0)
    //         std::cout << i.first << " " << i.second << std::endl;
    // std::cout << "count: " << count << std::endl;
    // std::ifstream is;
    // is.open("C:\\Users\\FlexStreet\\Documents\\VS Code projects\\akhzip\\image.data");
    // is.seekg(0, std::ios::end);
    // int length = is.tellg();
    // is.seekg(0, std::ios::beg);
    // char* buffer = new char [20000];
    // buffer[19999] = '\0';
    // is.read(buffer, 19999);
    // std::cout << "\nlength of image.data: " << length << std::endl;
    // std::multimap<int, char> sorted_weight;
    // int weight[0x100];
    // for (auto &i: weight) 
    //     i = 0;
    // for (int i = 0; i < 19999; i++) 
    //     weight[buffer[i] + 128]++;
    // for (int i = 0; i < 0x100; i++)
    //     sorted_weight.insert(std::make_pair(weight[i], (char)i));
    // for (auto i: sorted_weight)
    //     std::cout << i.first << " " << i.second <<std::endl;
    
    // buffer = bwt(buffer, 10);
    // std::cout << buffer << std::endl;
    std::ifstream is("C:\\Users\\FlexStreet\\Documents\\VS Code projects\\akhzip\\enwik8", std::ios::binary);
    int32_t freq[256];

    int32_t length = 400000;
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(is), {});
    std::cout << "buffer size = " << buffer.size() << std::endl;
    uint8_t lesgo[length];
    for (int i = 0; i < length; i++) lesgo[i] = buffer[i];
    // for (int i = length - 4; i < length; i++)
    //     std::cout << "!i = " << i << " lesgo[i] = " << (int)lesgo[i] << std::endl;
    int32_t extraspace[length];
    libsais_bwt(lesgo, lesgo, extraspace, length, 0, NULL);
    // for (int i = 0; i < 1000; i++) std::cout << "lesgo[" << i << "] = (" << (int)lesgo[i] << ") '" << (char)lesgo[i] << "'" << std::endl;
    // std::cout << lesgo << std::endl;
    // for (int i = 0; i < 1000; i++) std::cout << lesgo[i];
    // std::cout << std::endl;
    
    uint8_t alphabet[0x100];
    std::cout << "libsasisi works" << std::endl;
    for (int i = 0; i < 0x100; i++) alphabet[i] = i;
    mtf(lesgo, lesgo, length, alphabet);
    // for (int i = 0; i < 1000; i++) std::cout << (int)lesgo[i] << " ";
    // std::cout << std::endl;

    for (int i = 0; i < 0x100; i++) freq[i] = 0;
    for (int i = 0; i < length; i++) freq[lesgo[i]]++;
    for (int i = 0; i < 0x100; i++) std::cout << "freq[" << i << "] = " << freq[i] << std::endl;

    std::vector<bool> U;
    huffman(lesgo, U, length, freq);
    std::cout <<"Okay lesgo length * 8 = " << length * 8 << " U.size() = " << U.size() << " ratio = " << (float)U.size() / length / 8 << std::endl;

    // uint8_t test[8];
    // uint8_t mtf_test[8];

    // std::string to_test = "bananaaa";
    // for (int i = 0; i < 8; i++) test[i] = to_test[i];
    
    // for (int i = 0; i < 0x100; i++) alphabet[i] = i;
    // mtf(test, test, 8, alphabet);
    // for (int i = 0; i < 8; i++) std::cout << (int)test[i] << std::endl;
    // // for (int i = 0; i < 0x100; i++) std::cout << alphabet[i] << " ";
    // std::cout << std::endl;

    // for (int i = 0; i < 0x100; i++) alphabet[i] = i;
    // reverse_mtf(test, test, 8, alphabet);
    // for (int i = 0; i < 8; i++) std::cout << test[i] << std::endl;
    // // for (int i = 0; i < 0x100; i++) std::cout << alphabet[i] << " ";
    return 0;
}
