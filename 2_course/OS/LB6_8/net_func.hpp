#pragma once

#include <iostream>
#include <zmq.hpp>
#include <sstream>
#include <string>

namespace my_net{

    #define MY_PORT 4040
    #define MY_IP "tcp://127.0.0.1:"

    int bind(zmq::socket_t *socket, int id){
        int port  = MY_PORT + id;
        while(true){
            std::string adress = MY_IP  + std::to_string(port);
            try{
                socket->bind(adress);
                break;
            } catch(...){
                port++;
            }    
        }
        return port;
    }

    void connect(zmq::socket_t *socket, int port){
        std::string adress = MY_IP + std::to_string(port);
        socket->connect(adress);
    }

    void unbind(zmq::socket_t *socket, int port) {
        std::string adress = MY_IP + std::to_string(port);
        socket->unbind(adress);
    }

    void disconnect(zmq::socket_t *socket, int port) {
        std::string adress = MY_IP + std::to_string(port);
        socket->disconnect(adress);
    }

    void send_message(zmq::socket_t *socket, const std::string msg) {
        //std::cout << "c:send" << std::endl;
        zmq::message_t message(msg.size());
        //std::cout << "c:send" << std::endl;
        
        memcpy(message.data(), msg.c_str(), msg.size());
        
        //std::cout << "c:send " << msg << std::endl;
        try{
        socket->send(message);
        }catch(...){}
    }

    std::string reseave(zmq::socket_t *socket){
        //std::cout << "c:reseave" << std::endl;
        //std::cout << "c:reseave" << std::endl;
        zmq::message_t message;
        //std::cout << "c:reseave" << std::endl;
        bool success = true;
        //std::cout << "c:reseave" << std::endl;
        try{
            //std::cout << "c:reseave" << std::endl;
            socket->recv(&message,0);
        }catch(...){
            success = false;
        }
        if(!success || message.size() == 0){
            //std::cout << "c:Throw" << std::endl;
            throw -1;
        }
        std::string str(static_cast<char*>(message.data()), message.size());
        //std::cout << str << std::endl;
        //std::cout << "c:reseave" << std::endl;
        
        //std::cout << "c:reseave" << std::endl;
       
        return str;
    }

}