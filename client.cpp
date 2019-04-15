#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

#include <unistd.h>
#include <string.h>
#include <zmq.h>

#include "connection.h"

using namespace std;

double key;
string name;

void ok(){ cout << "ok\n";}

string get_name(){
    cout << "Enter your name: ";
    cin >> name;
    return name;
}

bool _login(connection connect){
    ostringstream oss;
    oss << "login " << name;
    connect.send_message(oss.str());
    istringstream iss(connect.recieve_message());
    double success;
    iss >> success;
    if (success > 0){
        iss >> key;
        return true;
    }
    return false;
}

void registrate(connection connect){
    ostringstream oss;
    oss << "registrate " << name;
    connect.send_message(oss.str());
    istringstream iss(connect.recieve_message());
    iss >> key;
}

void enter(connection connect){
    name = get_name();
    if (!_login(connect)){
        char c;
        bool flag = true;;
        while (flag){
            cout << "We can't found you in our database.\nDo you want to registrate? Y/N : ";
            cin >> c;
            switch (c)
            {
                case 'y':
                case 'Y':
                    registrate(connect);
                case 'n':
                case 'N':
                    flag = false;
                    break;
            }
        }
    }
}

size_t balance(connection connect){
    ostringstream oss;
    oss << "balance " << key;
    connect.send_message(oss.str());
    istringstream iss(connect.recieve_message());
    size_t sum;
    iss >> sum;
    return sum;
}

void add(connection connect, size_t value){
    ostringstream oss;
    oss << "add " << key << " " << value;
    connect.send_message(oss.str());
}

bool get(connection connect, size_t value){
    ostringstream oss;
    oss << "get " << key << " " << value;
    istringstream iss(connect.recieve_message());
    bool success;
    iss >> success;
    return success;
}

bool transfer(connection connect, size_t value, string whom){
    ostringstream oss;
    oss << "transfer " << key << " " << value << " " << whom;
    connect.send_message(oss.str());
    bool success;
    istringstream iss(connect.recieve_message());
    iss >> success;
    return success;
}

void logount(connection connect){
    ostringstream oss;
    oss << "logout " << key;
    connect.send_message(oss.str());
}

int main(){
    connection connect(ZMQ_REQ);
    cout << "client start\n";
    enter (connect);
    string command, whom_transfer;
    size_t value;
    while (cin >> command){
        cout << command << endl;
        if (command == "balance"){
            cout << "Your current balance : " << balance(connect) << "\n";
        }else if (command == "add"){
            cin >> value;
            add(connect, value);
            cout << "Success\n";
        }else if (command == "get"){
            cin >> value;
            if (get(connect, value)){
                cout << "Success\n";
            }else cout << "You don't have enough money\n";
        }else if (command == "transfer"){
            cin >> whom_transfer >> value;
            if (transfer(connect, value, whom_transfer)){
                cout << "Success\n";
            }else cout << "You don't have enougn money\n";
        }else{
            cout << "Can't understand this command";
        }
    }
    logount(connect);
    return 0;
}