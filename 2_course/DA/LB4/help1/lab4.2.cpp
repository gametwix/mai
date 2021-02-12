#include"Trie.h"
#include <iostream>
#include<vector>

int main()
{
    TTrie trie;
    std::vector<std::pair<int, std::vector<uint32_t>>> lk = { {1, {1, 2}}, {4, {1, 2}} };
    trie.Create(lk);

    std::cout << "Hello World!\n";
}
