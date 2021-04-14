#include "node.hpp"
#include "net_func.hpp"
#include "set"
#include <signal.h>



int main(){
    std::set<int> all_nodes;
    std::set<int> not_availvable;
    std::string prog_path = "./worker";
    Node me(-1);
    all_nodes.insert(-1);
    std::string command;
    while(std::cin >> command){
        if(command == "create"){
            int id_child, id_parent;
            std::cin >> id_child >> id_parent;
            if(all_nodes.find(id_child) != all_nodes.end()){
                std::cout << "Error: Already exists" << std::endl;
            }else if(not_availvable.find(id_child) != not_availvable.end()){
                std::cout << "Error: It was not available before " << std::endl;
            } else if(all_nodes.find(id_parent) == all_nodes.end()){
                std::cout << "Error: Parent not found" << std::endl;
            }else if(id_parent == me.id){
                std::string ans = me.Create_child(id_child, prog_path);
                std::cout << ans << std::endl;
                all_nodes.insert(id_child);
            } else{
                std::string str = "create " + std::to_string(id_child);
                std::string ans = me.Send(str, id_parent);
                std::cout << ans << std::endl;
                if(ans == "Error: not find"){
                    not_availvable.insert(id_parent);
                }
                all_nodes.insert(id_child);
            }   
        } else if(command == "ping"){
            int id_child;
            std::cin >> id_child;
            if(all_nodes.find(id_child) == all_nodes.end()){
                std::cout << "Error: Not found" << std::endl;
            }else if(not_availvable.find(id_child) != not_availvable.end()){
                std::cout << "Error: It was not available before " << std::endl;
            }else if(me.children.find(id_child) != me.children.end()){
                std::string ans = me.Ping_child(id_child);
                if(ans == "Ok: 0"){
                    not_availvable.insert(id_child);
                }
                //std::cout << "Try ping" << std::endl;
                std::cout << ans << std::endl;
            }else{
                //std::cout << "Error: Not my child" << std::endl;
                std::string str = "ping " + std::to_string(id_child);
                std::string ans = me.Send(str, id_child);
                if(ans == "Error: not find"){
                    ans = "Ok: 0";
                }
                if(ans == "Ok: 0"){
                    not_availvable.insert(id_child);
                }
                std::cout << ans << std::endl;
            }
        }else if(command == "exec"){
            int id;
            std::string str;
            std::string pattern;
            std::cin >> id >> str >> pattern;
            std::string msg = "exec " + str + " " + pattern;
            //std::cout << msg << std::endl;
            if(all_nodes.find(id) == all_nodes.end()){
                std::cout << "Error: Not found" << std::endl;
            }else if(not_availvable.find(id) != not_availvable.end()){
                std::cout << "Error: It was not available before " << std::endl;
            }else{
                std::string ans = me.Send(msg,id);
                if(ans == "Error: not find"){
                    not_availvable.insert(id);
                }
                std::cout << ans << std::endl;
            }
            
        }else if(command == "remove"){
            int id;
            std::cin >> id;
            std::string msg = "remove";
            if(all_nodes.find(id) == all_nodes.end()){
                std::cout << "Error: Not found" << std::endl;
            }else if(not_availvable.find(id) != not_availvable.end()){
                std::cout << "Error: It was not available before " << std::endl;
            }else{
                std::string ans = me.Send(msg,id);
                if(ans == "Error: not find"){
                    not_availvable.insert(id);
                }else{
                    std::istringstream ids(ans);
                    int tmp;
                    //std::cout << ans  << " gcount " << ids.gcount() << std::endl;
                    while(ids >> tmp){
                        //std::cout << tmp << std::endl;
                        all_nodes.erase(tmp);
                        not_availvable.erase(tmp);
                    }
                    ans = "Ok";
                }
                std::cout << ans << std::endl;
                //std::cout << "remove " << std::endl;
                if(me.children.find(id) != me.children.end()){
                    my_net::unbind(me.children[id],me.children_port[id]);
                    me.children[id]->close();
                    //std::cout << "remove " << std::endl;
                    me.children.erase(id);
                    //std::cout << "remove " << std::endl;
                    me.children_port.erase(id);
                    //std::cout << "remove " << std::endl;
                }
               
            }
        }
    }
    //std::cout << "exit" << std::endl;
    me.Remove();
    //kill(getpid(),SIGKILL);
    return 0;
}