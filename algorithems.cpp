#include "algorithems.h"


int32_t mtf(uint8_t * T, uint8_t * U, int32_t n, uint8_t * alphabet){
    for (int32_t i = 0; i < n; i++){
        int j = 0;
        uint8_t next = alphabet[0];
        while (next != T[i]){
            uint8_t swap = next;
            next = alphabet[j + 1];
            alphabet[j + 1] = swap;
            j++;
        }
        alphabet[0] = next;
        U[i] = j;
    }
    return 0;
}

int32_t reverse_mtf(uint8_t * T, uint8_t * U, int32_t n, uint8_t * alphabet){
    for (int i = 0; i < n; i++){
        T[i] = alphabet[U[i]];
        int j = 0;
        uint8_t next = alphabet[0];
        while (next != T[i]){
            uint8_t swap = next;
            next = alphabet[j + 1];
            alphabet[j + 1] = swap;
            j++;
        }
        alphabet[0] = next;
    }
    return 0;
}


int32_t huffman(uint8_t * T, std::vector<bool>& U, int32_t n, int32_t * freq, std::vector<std::vector<bool> >& symb_code){
    class Node{
            public:
            uint8_t ch;
            int32_t parent;
            int32_t lchild;
            int32_t rchild;
            bool branch;
    };

    std::multimap<uint32_t, uint32_t> sorted_weights; /* <weight, index in the tree> */
    std::vector<Node> tree;
    std::map<uint8_t, uint32_t> symb_first_entering;
    
    for (uint16_t i = 0; i < 0x100; i++) if (freq[i] > 0){
            Node to_push = {(uint8_t)i, -1, -1, -1, false};
            tree.push_back(to_push);
            symb_first_entering[i] = tree.size() - 1;
            sorted_weights.insert(std::make_pair(freq[i], tree.size() - 1));
        }
    std::cout << "freq.size() = " << tree.size() << std::endl;
    
    while (sorted_weights.size() > 1){
        int32_t w0 = std::begin(sorted_weights)->first;
        int32_t n0 = std::begin(sorted_weights)->second;
        sorted_weights.erase(begin(sorted_weights));
        int32_t w1 = std::begin(sorted_weights)->first;
        int32_t n1 = std::begin(sorted_weights)->second;
        sorted_weights.erase(begin(sorted_weights));
        Node to_push = {'\0', -1, n0, n1, false};
        tree.push_back(to_push);
        tree[n0].parent = tree.size() - 1;
        tree[n1].parent = tree.size() - 1;
        tree[n1].branch = true;
        sorted_weights.insert(std::make_pair(w0 + w1, tree.size() - 1));
    }
    
    for (uint16_t i = 0; i < 0x100; i++) if (freq[i] > 0){
        auto cur_node = tree[symb_first_entering[i]];
        while (cur_node.parent != -1){
            symb_code[i].push_back(cur_node.branch);
            cur_node = tree[cur_node.parent];
        }
        // std::cout << "symb_code[" << i << "] = ";
        // for (auto itr : symb_code[i])
        //     std::cout << (int)itr;
        // std::cout << " size = " << symb_code[i].size() << std::endl;
    }

    // int is_it_true = 0;
    // for (uint16_t i = 0; i < 0x100; i++) if (freq[i] > 0) is_it_true += freq[i] * symb_code[i].size();
    // std::cout << "So S.size should be - " << is_it_true << std::endl;

    for (uint64_t i = 0; i < n; i++)
        U.insert(std::end(U), symb_code[T[i]].rbegin(), symb_code[T[i]].rend());

    std::string huffman_code;
    huffman_dict_to_string(symb_code, huffman_code);

    return 0;
}


int32_t huffman_dict_to_string(std::vector<std::vector<bool> >& symb_code, std::string& output_dict){
    std::vector<bool> binary_to_string;
    for (int16_t i = 0; i < 0x100; i++)
        if (symb_code[i].size() == 0)
            binary_to_string.push_back(0);
        else {
            binary_to_string.push_back(1);
            for (auto a : std::bitset<8>(symb_code[i].size()).to_string()) binary_to_string.push_back(a == '1');
            for (bool symb_bit : symb_code[i]) binary_to_string.push_back(symb_bit);
        }
    binary_vector_to_string(binary_to_string, output_dict);
    return binary_to_string.size();
}


int32_t binary_vector_to_string(std::vector<bool>& binary, std::string& output){
    // for (auto ch : binary) std::cout << ch;
    // std::cout << std::endl;
    output = (char) (binary.size() % 8);
    int bit_count = 7;
    uint8_t ch = 0;
    for (auto bit : binary){
        ch |= (bit<<bit_count);
        bit_count--;
        if (bit_count == -1){
            output.push_back(ch);
            bit_count = 7;
            ch = 0;
        }
    }
    if (bit_count < 7) output.push_back(ch);

    return 0;
}

int32_t string_to_binary_vector(std::vector<bool>& binary, std::string& output){
    int poor_bits = (int) output[0];
    if (poor_bits == 0) poor_bits = 8;
    for (int i = 1; i < output.size() - 1; i++)
        for (auto a : std::bitset<8>((int) (uint8_t) output[i]).to_string()) binary.push_back(a == '1');
    for (auto a : std::bitset<8>((int) (uint8_t) output[output.size() - 1]).to_string().substr(8 - poor_bits, poor_bits)) binary.push_back(a == '1');
    // for (auto ch : binary) std::cout << ch;
    // std::cout << std::endl;

    return 0;
}

int32_t huffman_string_to_dict(std::vector<std::vector<bool> >& symb_code, std::string& output_dict){
    std::vector<bool> string_to_binary;
    string_to_binary_vector(string_to_binary, output_dict);
    uint16_t symb = 0;
    uint64_t it = 0;
    int code_length = 0;
    while (it < string_to_binary.size()){
        if (string_to_binary[it]) {
            it++;
            code_length = 0;
            for (int i = it; it - i < 8; it++) code_length = code_length * 2 + (int) string_to_binary[it];
            for (int i = it; it - i < code_length; it++) symb_code[symb].push_back(string_to_binary[it]);
        }
        else it++;
        symb++;
    }
    return 0;
}

int32_t compressed_string(std::string& huffman_code, std::vector<bool>& U, std::string& compressed_data){
    std::string data;
    std::vector<bool> binary;
    std::string size_huffman_code;
    binary_vector_to_string(U, data);
    for (auto a : std::bitset<16>(huffman_code.size()).to_string()) binary.push_back(a == '1');
    binary_vector_to_string(binary, size_huffman_code);
    compressed_data = size_huffman_code + huffman_code + data;
    return 0;
}

int32_t decompressed_string(std::string& huffman_code, std::vector<bool>& U, std::string& compressed_data){
    uint16_t size_huffman;
    std::string dec_data;
    size_huffman = ((int) (uint8_t) compressed_data[1]) * 256 + (int) (uint8_t) compressed_data[2];
    huffman_code = compressed_data.substr(3, size_huffman);
    dec_data = compressed_data.substr(3 + size_huffman, compressed_data.size() - 3 - size_huffman);
    string_to_binary_vector(U, dec_data);
    return 0;
}
