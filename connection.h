#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <cstdlib>
#include <string>

#include <string.h>
#include <unistd.h>
#include <zmq.h>

const char * localhost = "tcp://localhost:4040";
const char * serverhost = "tcp://*:4040";

const int MESSAGE_LENGTH = 256;

using namespace std;

class connection{
public:
    connection(int type);

    void send_message(string message);
    string recieve_message();

    ~connection();

private:
    typedef enum my_type{
        server,
        client
    }my_type;

    void * context;
    void * socket;
    my_type me;
};

#include "connection.cpp"

#endif