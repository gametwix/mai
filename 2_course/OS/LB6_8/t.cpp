#include <zmq.hpp>
#include <string>
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
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.setsockopt(ZMQ_RCVTIMEO,2000);
        socket.recv (&request);
        std::cout << "Received Hello" << std::endl;

        //  Do some 'work'
    	sleep(1);

        //  Send reply back to client
        std::cout << "Received Hello" << std::endl;
        zmq::message_t reply (5);
        std::cout << "Received Hello" << std::endl;
        memcpy (reply.data (), "World", 5);
        std::cout << "Received Hello" << std::endl;
        try{
        socket.send (reply);
        }catch(zmq::error_t e){
        std::cout << e.what()<< std::endl;
        }
    }
    return 0;
}