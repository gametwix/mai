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
    std::unordered_map<int,int> children_port;
    zmq::socket_t parent;
    int parent_port;

    int id;
    Node(int _id , int _parent_port = -1):   id(_id),
                                            parent(context,ZMQ_REP),
                                            parent_port(_parent_port){
        if(_id != -1){
            //std::cout << "New node" << std::endl;
            my_net::connect(&parent,_parent_port);
            parent.setsockopt(ZMQ_LINGER,300);
            //parent.setsockopt(ZMQ_RCVTIMEO,3000);
            parent.setsockopt(ZMQ_LINGER,100);
            //std::cout << "New node connected" << std::endl;
        }
    }
/*
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
    */
    std::string Ping_child(int _id){
        std::string ans = "Ok: 0";
        //std::cout << "my_id " << id << " _id " << _id << std::endl;
        ans = "Ok: 0";
        if(_id == id){
            //std::cout << "Ping::_id " << _id << " id " << id << std::endl;
            ans = "Ok: 1";
            return ans;
        } else if(children.find(_id) != children.end()){
            //std::cout << "pint not i" << std::endl;
            std::string msg = "ping " + std::to_string(_id);
            //std::cout << msg <<std::endl;
            my_net::send_message(children[_id],msg);
            try{
                msg  = my_net::reseave(children[_id]);
                if(msg == "Ok: 1")
                    ans = msg;
            } catch(int){}
            return ans;
        }else{
            //std::cout << "pint else" << std::endl;
            return ans;
        }

        //if(id != -1)
        //    my_net::send_message(&parent,ans);
        
    } 

    std::string Create_child(int child_id,std::string program_path){
        //std::cout << "Create_child " << id << std::endl;
        std::string program_name = program_path.substr(program_path.find_last_of("/") + 1);
        children[child_id] = new zmq::socket_t(context,ZMQ_REQ);
        //children[child_id]->setsockopt(ZMQ_SNDTIMEO,3000);
        
        int new_port = my_net::bind(children[child_id],child_id);
        children_port[child_id] = new_port;
        int pid = fork();//2;
        
        if(pid == 0){
            //std::cout << "child" << std::endl;
            //std::cout << program_path.c_str() << std::endl;
            execl(program_path.c_str(), program_name.c_str(), std::to_string(child_id).c_str() , std::to_string(new_port).c_str() ,(char*)NULL);
            //execl("./work", "work", child_id, id, (char*)NULL);
        }else{
            //std::cout << "Parent" << std::endl;
            
            //std::cout << "Parent connect" << std::endl;
            std::string child_pid;

            try{
                children[child_id]->setsockopt(ZMQ_SNDTIMEO,3000);
                //children[child_id]->setsockopt(ZMQ_RCVTIMEO,3000);
                children[child_id]->setsockopt(ZMQ_LINGER,300);
                //std::cout <<"Parent send pid request" << std::endl;
                my_net::send_message(children[child_id],"pid");
                //std::cout << "Parent try reseave" << std::endl;
                child_pid = my_net::reseave(children[child_id]);
            } catch(int){
                child_pid = "Error: can't connect to child";
            }
            //std::cout << "children size = " << children.size() << std::endl;
            //for( auto& child: children){
            //    std::cout << "Create " << id << " have child " << child.first << std::endl;
            //}
            return "Ok: " + child_pid;
        }


    }

    std::string Pid(){
        return std::to_string(getpid());
    }

    std::string Send(std::string str,int _id){
        //for( auto& child: children){
        //    std::cout << id << " have child " << child.first << std::endl;
        //}

        //std::cout << str << std::endl;
        if(children.size() == 0){
            return "Error: now find";
        }else if(children.find(_id) != children.end()){
            if(Ping_child(_id) == "Ok: 1"){
                my_net::send_message(children[_id],str);
                std::string ans;
                try{
                    ans = my_net::reseave(children[_id]);
                } catch(int){
                    ans = "Error: now find";
                }
                return ans;
            }
        }else{
            std::string ans = "Error: not find";
            for(auto& child: children ){
                //std::cout << "try ping to send " << child.first << std::endl;
                if(Ping_child(child.first) == "Ok: 1"){
                    //std::cout << child.first << " exist" << std::endl;
                    std::string msg = "send " + std::to_string(_id) + " " + str;
                    //std::cout << child.first << " send msg: " << msg<< std::endl;
                    my_net::send_message(children[child.first],msg);
                    try{
                        msg = my_net::reseave(children[child.first]);
                    } catch(int){
                        msg = "Error: not find";
                    }
                    if(msg != "Error: not find"){
                        ans = msg;
                    }
                }
            }
            return ans;
        }
    }

    std::string Remove(){
        std::string ans;
        if(children.size() > 0){
            for(auto& child: children ){
                if(Ping_child(child.first) == "Ok: 1"){
                    std::string msg = "remove";
                    my_net::send_message(children[child.first],msg);
                    try{
                        msg = my_net::reseave(children[child.first]);
                        //std::cout << msg << std::endl;
                        if(ans.size() > 0)
                            ans = ans + " " + msg;
                        else
                            ans =  msg;
                    } catch(int){}
                }
                my_net::unbind(children[child.first], children_port[child.first]);

            }
            children.clear();
            children_port.clear();
        }
        return ans;
    }

};


