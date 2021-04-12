#include "net_func.hpp"
#include <iostream>


int main () {
    zmq::context_t context(1);
    zmq::socket_t* socket = new zmq::socket_t(context,ZMQ_REQ);
    std::cout << 1 << std::endl;
    int port = my_net::bind(socket,9);
    std::cout << 1 << std::endl;
    while(1){
    try{
        std::cout << "res" << std::endl;
        std::cout << my_net::reseave(socket,2000) << std::endl;;
    }
    catch(int i){
        std::cout << "Don't have client" << i<< std::endl;
        break;
    }
    }
    std::cout << "exit" <<std::endl;
    return 0;
}