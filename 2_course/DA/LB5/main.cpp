#include "SuffO3.h"

#include <iostream>
#include <memory>

int main(){
    std::string text;
    std::cin >> text;
    CompactTrie Trie;
    Trie.Init(text);
    Trie.Print();
    return 0;
}