#include "node.hpp"
#include "net_func.hpp"



int main(int argc, char **argv){
    if(argc != 3){
        return -1;
    }
    Node me(atoi(argv[1]),atoi(argv[2]));
    
    while(1){
        std::string message;
        std::string command;
        std::string prog_path;
        message = my_net::reseave(&(me.parent));
        std::istringstream request(message);
        request >> command;

        if(command == "create"){
            int id_child, id_parent;
            std::string prog_path = "./work";
            request >> id_child >> id_parent;
            me.Create(id_parent, id_child, prog_path);
        }
    }
    return 0;
}



