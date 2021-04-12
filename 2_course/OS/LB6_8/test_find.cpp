#include <iostream>
#include <string>
#include <vector>

int main(){
    std::string str;
    std::string pattern;
    std::cin >> str >> pattern;
    std::vector<int> ans;
    int start = 0;
    while(str.find(pattern,start) != -1){
        start = str.find(pattern,start);
        ans.push_back(start);
        start++;
    }
    std::string to_send;
    if(ans.size() == 0){
        to_send = "-1";
    }else{
        to_send = std::to_string(ans[0]);
        for(int i = 1; i < ans.size();++i){
            to_send = to_send + ";" + std::to_string(ans[i]);
        }
    }
    std::cout << to_send << std::endl;

    return 0;
}