#include <iostream>
#include "net_func.hpp"
#include <sstream>
#include <unordered_map>
#include "unistd.h"


class Node{
private:
    zmq::context_t context;
public:
    std::unordered_map<int,zmq::socket_t*> children;
    zmq::socket_t socket;
    zmq::socket_t parent;
    int id;
    int id_parent;
    Node(int _id , int _id_parent = -1):  id(_id),
                                id_parent(_id_parent),
                                socket(context,ZMQ_REP),
                                parent(context,ZMQ_REQ){
        my_net::bind(&socket,id);
        if(_id_parent != -1){
            my_net::connect(&parent,id_parent);
        }
    }

    bool Create(int _id, int id_child, std::string prog_path){
        if(id == _id){
            int pid = fork();
            if(pid == 0){
                std::string name = prog_path.substr(prog_path.find_last_of("/"));
                execl(prog_path.c_str(),name.c_str(),id_child,id,(char*)NULL);
            }else{
                children[id_child] = new zmq::socket_t(context,ZMQ_REQ);
                my_net::connect(children[id_child],id_child);
                my_net::send_message(&parent,"OK");
            }
        }else{
            std::string msg;
            msg = "create " + std::to_string(id_child) + " " + "_id";
            Send(_id,id,msg);
        }
    }

    bool Send(int _id,int sender, std::string str){
        if(children.find(_id) != children.end()){
            if(Ping(_id,id)){
                std::string msg = str;
                my_net::send_message(children[_id],msg);
                try{
                    msg = my_net::reseave(&socket,1000);
                    if(id != sender)
                        my_net::send_message(&parent,msg);
                    return true;
                }catch(int){
                    if(id != sender)
                        my_net::send_message(&parent,"Error");
                    return false;
                }
            } else{
                if(id != sender)
                    my_net::send_message(&parent,"Error");
                return false;
            }
        }else{
            bool ans = false;
            std::string to_ans;
            for(auto& child: children ){
                if(Ping(child.first,id)){
                    std::string msg = "send " + std::to_string(_id) + " " + std::to_string(sender) + " " + str;
                    my_net::send_message(children[_id],msg);
                    try{
                        msg = my_net::reseave(&socket,1000);
                        if(msg != "Error"){
                            to_ans = msg;
                            ans = true;
                        }
                    }catch(int){}
                }
            }
            if(ans){
                if(id != sender)
                    my_net::send_message(&parent,to_ans);
                return true;
            }else{
                if(id != sender)
                    my_net::send_message(&parent,"Error");
                return false;
            }
        }

    }

    bool Ping(int _id, int sender){
        if(id == _id){
            if(id != sender)
                my_net::send_message(&parent,"Success");
            return true;
        }else if(children.size() == 0){
            if(id != sender)
                my_net::send_message(&parent,"Error");
            return false;
        }
        if(children.find(_id) != children.end()){
            std::string msg = "ping " + std::to_string(_id) + " " + std::to_string(sender);
            my_net::send_message(children[_id],msg);
            try{
                msg = my_net::reseave(&socket,1000);
                if(msg == "Success"){
                    if(id != sender)
                        my_net::send_message(&parent,"Success");
                    return true;
                } else{
                    if(id != sender)
                        my_net::send_message(&parent,"Error");
                    return false;
                }
            }
            catch(int){
                if(id != sender)
                    my_net::send_message(&parent,"Error");
                return false;
            }
        }else{
            bool ans = false;
            for(auto& child: children ){
                if(Ping(child.first,id)){
                    std::string msg = "ping " + std::to_string(_id) + " " + std::to_string(sender);
                    my_net::send_message(children[_id],msg);
                    try{
                        msg = my_net::reseave(&socket,1000);
                        if(msg == "Success"){
                            bool ans = true;
                        }
                    }catch(int){}
                    break;
                }
            }
            if(ans){
                if(id != sender)
                    my_net::send_message(&parent,"Success");
                return true;
            }else{
                if(id != sender)
                    my_net::send_message(&parent,"Error");
                return false;
            }
        }
    }
    
};


