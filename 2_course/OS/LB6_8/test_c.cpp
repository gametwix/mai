#include <zmq.hpp>
#include <string>
#include "net_func.hpp"
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>

#define sleep(n)	Sleep(n)
#endif

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);
    my_net::connect(&socket,4049);
    while (true) {
        //  Wait for next request from client
        //my_net::send_message(&socket,"Hi");
        std::string msg("Hi");
        std::cout << 1 << std::endl;
        zmq::message_t message(msg.size());
        std::cout << 1 << std::endl;
        memcpy(message.data(), msg.c_str(), msg.size());
        std::cout << 1 << std::endl;
        socket.send(message);
        std::cout << "Received Hello" << std::endl;

        //  Do some 'work'
    	sleep(1);
    }
    return 0;
}