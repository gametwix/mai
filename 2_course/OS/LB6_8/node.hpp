#include <iostream>
#include <zmq.hpp>
#include <sstream>
#include <unordered_map>


class Node{
private:
    std::unordered_map<int,zmq::socket_t> children;
    zmq::socket_t socket;
public:
    int id;

    
};


