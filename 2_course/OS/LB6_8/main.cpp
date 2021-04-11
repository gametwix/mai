#include "node.hpp"
#include "net_func.hpp"



int main(){

    Node me(-1);
    
    while(1){
        std::string message;
        std::string command;
        std::cin >> command;

        if(command == "create"){
            int id_child, id_parent;
            std::string prog_path = "./work";
            std::cin >> id_child >> id_parent;
            me.Create(id_parent, id_child, prog_path);
        }
    }
    return 0;
}