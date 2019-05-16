#include "connection.h"

connection::connection(int type){
    connect(type);
}

connection::connection(){
    socket = NULL;
    context = NULL;
}

void
connection::connect(int type){
    this->type = type;
    context = zmq_ctx_new();
    socket = zmq_socket(context, type);
    if (type == client)
        zmq_connect(socket, "tcp://localhost:4040");
    else
        zmq_bind(socket, "tcp://*:4040");
}

void connection::send(const string & s){
    zmq_msg_t msg;
    zmq_msg_init_size(&msg, s.size());
    memcpy(zmq_msg_data(&msg), s.data(), s.size());
    zmq_msg_send(&msg, socket, 0);
    zmq_msg_close(&msg);
}

string connection::recieve(){
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    zmq_msg_recv(&msg, socket, 0);
    string s((char*)zmq_msg_data(&msg));
    s.resize(zmq_msg_size(&msg));
    zmq_msg_close(&msg);
    return s;
}

connection::~connection(){
    if(socket) zmq_close(socket);
    if(context) zmq_ctx_destroy(context);
}
