#include "connection.h"
#include <iostream>
#include <string>

using namespace std;

connection connect;
string name;
string id;

enum consent{
    yes,
    no,
    error
};

void success(const string & s){
    cout << "\t\t~~~~~~" << s << "~~~~~~\n";
}

void failure(const string & s){
    cout << "\t\t******" << s << "******\n";
}

consent ask(const string & str){
    string s;
    while (true){
        cout << str << " [Y/n] ";
        if (!(cin >> s)) return error;
        switch (s[0]){
            case 'Y':
            case 'y':
                return yes;
            case 'N':
            case 'n':
                return no;
        }
    }
}

string enter_name(){
    string s;
    cout << "enter your name: ";
    cin >> s;
    return s;
}

bool login(){
    string s = enter_name();
    connect.send("login " + s);
    int my_index = stoi(connect.recieve());
    if (my_index < 0) return false;
    id = to_string(my_index);
    name = s;
    return true;
}

bool registrate(){
    string s = enter_name();
    connect.send("registrate " + s);
    int my_index = stoi(connect.recieve());
    if (my_index < 0) return false;
    id = to_string(my_index);
    name = s;
    return true;
}

bool enter(){
    consent cons = ask("log in?");
    if (cons == error) return false;
    if (cons == yes)
        if (login()) return true;
    cons = ask("registrate?");
    if (cons == no || cons == error) return false;
    while (true){
        if (!registrate()){
            failure("This name is already used");
            cons = ask("Try again?");
            if (cons == no || cons == error) return false;
        }else{
            success("You've been registrated");
            return true;
        }
    }
}

void help(){
    cout    << "\n\tCommands, that you can use:\n"
            << ">\tbalace (show your balnce)\n"
            << ">\ttransfer <name, who will get> <summ> (transfer money to somebody)\n"
            << ">\tget <summ> (get money)\n"
            << ">\tadd <summ> (add money)\n"
            << ">\thelp (show this menu)\n\n";
}

void get_balance(){
    connect.send("balance " + id);
    cout << "Your current balance: " << connect.recieve() << "\n";
}

bool transfer(){
    string whom;
    int summ;
    if (!(cin >> whom >> summ)){
        return false;
    }
    connect.send("transfer " + id + string(" ") + whom + " " + to_string(summ));
    int ans = stoi(connect.recieve());
    if (ans == -1){
        failure("No such person");
    }
    else if (ans == -2){
        failure("You don't have enough money");
    }
    else success("money has been transfered");
    return true;
}

bool get(){
    int summ;
    if (!(cin >> summ)) return false;
    connect.send("get " + id + string(" ") + to_string(summ));
    int ans = stoi(connect.recieve());
    if (ans == 0){
        failure("You don't have enough money");
    }else{
        success("money have been getted");
    }
    return true;
}

bool add(){
    int summ;
    if (!(cin >> summ)) return false;
    connect.send("add " + id + string(" ") + to_string(summ));
    connect.recieve();
    success("money have been added");
    return true;
}

int main(){
    connect.connect(connection::client);
    if (!enter()) return false;
    string command;
    help();
    bool flag = true;
    while (cin >> command && flag){
        switch(command[0]){
            case 'b':
                get_balance();
                break;
            case 't':
                flag = transfer();
                break;
            case 'g':
                flag = get();
                break;
            case 'a':
                flag = add();
                break;
            case 'h':
                help();
                break;
            default:
                cout << "******Wrong command******\n";
        }
    }
//    connect.send("logout " + name);
    return 0;
}