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


int32_t huffman(uint8_t * T, std::vector<bool>& U, int32_t n, int32_t * freq){
    struct Node{
        uint8_t ch;
        int32_t parent;
        int32_t lchild;
        int32_t rchild;
        bool branch;
    };

    std::multimap<uint32_t, uint32_t> sorted_weights; /* <weight, index in the tree> */
    std::vector<Node> tree;
    std::map<uint8_t, uint32_t> symb_first_entering;
    std::vector<std::vector<bool>> symb_code(0x100);
    
    for (uint16_t i = 0; i < 0x100; i++) if (freq[i] > 0){
            tree.push_back(Node{(uint8_t)i, -1, -1, -1, false});
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
        tree.push_back(Node{'\0', -1, n0, n1, false});
        tree[n0].parent = tree.size() - 1;
        tree[n1].parent = tree.size() - 1;
        tree[n1].branch = true;
        sorted_weights.insert(std::make_pair(w0 + w1, tree.size() - 1));
    }
    
    for (uint16_t i = 0; i < 0x100; i++) if (freq[i] > 0){
        std::vector<bool> code;
        symb_code[i] = code;
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

    return 0;
}

