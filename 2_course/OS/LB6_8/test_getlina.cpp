#include <iostream>
#include <sstream>
#include <string>

int main(){
    std::string msg = "send 2 ping 2";
    std::istringstream request(msg);
    std::string comand;
    request >> comand;
    if(comand == "send"){
        int id;
        request >> id;
        std::string str;
        getline(request,str);
        str.erase(0,1);
        std::cout << 111111111111 << std::endl;
        std::cout << str << std::endl;
    }
    return 0;
}