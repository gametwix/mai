#pragma once

#include <iostream>
#include <zmq.hpp>
#include <sstream>
#include <string>

namespace my_net{

    #define MY_PORT 5000
    #define MY_IP "tcp://*:"

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
        zmq::message_t message(msg.size());
        memcpy(message.data(), msg.c_str(), msg.size());
        socket->send(message,0);
    }

    std::string reseave(zmq::socket_t *socket,int time = -1){
        std::cout << 1 << std::endl;
        socket->setsockopt(ZMQ_RCVTIMEO,time);
        std::cout << 1 << std::endl;
        zmq::message_t message;
        std::cout << 1 << std::endl;
        bool success = true;
        std::cout << 1 << std::endl;
        try{
            std::cout << 1 << std::endl;
        socket->recv(&message,0);
        std::cout << 1 << std::endl;
        }catch(...){
            success = false;
        }
        std::cout << 2 <<std::endl; 
        if(!success || message.size() == 0)
            throw -1;
        std::cout << 2 <<std::endl; 
        std::string str(static_cast<char*>(message.data()), message.size());
        return str;
    }

}