#pragma once

#include <iostream>
#include <zmq.hpp>
#include <sstream>
#include <string>

#define MY_PORT 5000
#define MY_IP "tcp://127.0.0.1"

void bind(zmq::socket_t &socket, int id){
    std::string adress = MY_IP + ':' + std::to_string(MY_PORT + id);
    socket.bind(adress);
}

void connect(zmq::socket_t &socket, int id){
    std::string adress = MY_IP + ':' + std::to_string(MY_PORT + id);
    socket.connect(adress);
}

void unbind(zmq::socket_t &socket, int id) {
    std::string adress = MY_IP + ':' + std::to_string(MY_PORT + id);
    socket.unbind(adress);
}

void disconnect(zmq::socket_t &socket, int id) {
    std::string adress = MY_IP + ':' + std::to_string(MY_PORT + id);
    socket.disconnect(adress);
}

void send_message(zmq::socket_t &socket, const std::string &msg) {
    zmq::message_t message(msg.size());
    memcpy(message.data(), msg.c_str(), msg.size());
    socket.send(message);
}

std::string reseave(zmq::socket_t &socket){
    zmq::message_t message;
    int size = (int)socket.recv(&message);
    std::string str(static_cast<char*>(message.data()), message.size());
    return str;
}

