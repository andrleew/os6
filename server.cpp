#include <iostream>
#include <sstream>

#include <unistd.h>
#include <pthread.h>
#include <zmq.h>

#include "connection.h"
#include "Database.h"

using namespace std;

bool sl;

void ok(){ cout << "ok\n";}

void fsleep(){
    string s;
    while (cin >> s){
        if (s == "sleep"){
            cout << "sleep...\n";
            sl = true;
        }else if (s == "wake"){
            cout << "wake!\n";
            sl = false;
        }
    }
}

void* thread_sleep(void * argv){
    fsleep();
    return NULL;
}

int main(){
    Database database;
    pthread_t thread;
    string command;
    ostringstream oss;
    sl = false;
    pthread_create(&thread, NULL, thread_sleep, NULL);
    connection connect(ZMQ_REP);
    cout << "server start\n";
    while (true){
        ok();
        while (sl) sleep(1);
        istringstream iss(connect.recieve_message());
        iss >> command;
        if (command == "login"){
            string name;
            iss >> name;
            oss << database.Login(name);
            connect.send_message(oss.str());
        }else if (command == "registrate"){
            string name;
            iss >> name;
            oss << database.Register(name);
            connect.send_message(oss.str());
        }else if (command == "balance"){
            double key;
            iss >> key;
            oss << database.GetBalance(key);
            connect.send_message(oss.str());
        }else if(command == "add"){
            double key;
            size_t value;
            iss >> key >> value;
            database.AddMoney(key, value);
        }else if (command == "get"){
            double key;
            size_t value;
            iss >> key >> value;
            oss << database.GetMoney(key, value);
            connect.send_message(oss.str());
        }else if (command == "transfer"){
            double from, to;
            size_t value;
            iss >> from >> to >> value;
            oss << database.Transfer(from, to, value);
            connect.send_message(oss.str());
        }else if (command == "logout"){
            double key;
            iss >> key;
            database.Remove(key);
        }
        ok();
        oss.clear();
        ok();
    }
    return 0;
}