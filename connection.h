#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <string>
#include <string.h>

#include <zmq.h>

using namespace std;

class connection{
public:
    static const int server = ZMQ_REP;
    static const int client = ZMQ_REQ;

    connection();
    connection(int type);
    ~connection();

    void connect(int type);
    void send(const string & str);
    string recieve();

private:
    int type;
    void *context, *socket;
};

#endif