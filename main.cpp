#include "algorithems.h"
#include "libraries\libsais.h"
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
    std::ifstream is;
    int32_t freq[256];
    is.open("C:\\Users\\FlexStreet\\Documents\\VS Code projects\\akhzip\\image.data");
    is.seekg(0, std::ios::beg);
    uint8_t lesgo[1000];
    is.read((char*)lesgo, 1000);
    int32_t extraspace[1000];
    libsais_bwt(lesgo, lesgo, extraspace, 1000, 0, freq);
    // for (int i = 0; i < 1000; i++) std::cout << "lesgo[" << i << "] = (" << (int)lesgo[i] << ") '" << (char)lesgo[i] << "'" << std::endl;
    // std::cout << lesgo << std::endl;
    for (int i = 0; i < 1000; i++) std::cout << lesgo[i];
    std::cout << std::endl;
    for (int i = 0; i < 256; i++) std::cout << "freq[" << i << "] = " << freq[i] << std::endl;
    
    uint8_t alphabet[0x100];
    for (int i = 0; i < 0x100; i++)
        alphabet[i] = i;
    // mtf();
    return 0;
}
