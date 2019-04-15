//#include "connection.h"

connection::connection(int type){
    context = zmq_ctx_new();
    socket = zmq_socket(context, type);
    if (type == ZMQ_REQ){
        me = client;
        bool doing = true;
        string s;
        while (zmq_connect(socket, localhost) && doing){
        cout << "\nCan't connect to server. Try agin?\nY/N : ";
            if (cin >> s){
                switch (s[0])
                {
                    case 'Y':
                    case 'y':
                        break;
                    case 'N':
                    case 'n':
                        doing = false;
                        break;
                    default:
                        cout << "\nWrong answer\n";
                        break;
                }
            }else cout << "\n";
        }
    }else{
        me = server;
        zmq_bind(socket, serverhost);
    }
}

void connection::send_message(string message){
    zmq_msg_t msg;
    zmq_msg_init_size(&msg, message.size());
    char * msg_str = new char[message.size() + 1];
    strcpy(msg_str, message.c_str());
    msg_str[message.size()] = '\0';
    memcpy(zmq_msg_data(&msg), msg_str, message.size());
    cout << msg_str;
    zmq_msg_send(&msg, socket, 0);
    zmq_msg_close(&msg);
    delete msg_str;
}

string connection::recieve_message(){
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    zmq_msg_recv(&msg, socket, 0);
    int size = zmq_msg_size(&msg);
    char * message = new char [size + 1];
    memcpy(message, zmq_msg_data(&msg), size);
    zmq_msg_close(&msg);
    cout << message << endl;
    return string(message);
}

connection::~connection(){
    if (me == client) zmq_disconnect(socket, localhost);
    else zmq_disconnect(socket, serverhost);
    zmq_close(socket);
    zmq_ctx_destroy(context);
}