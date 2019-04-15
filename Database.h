#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <list>

using namespace std;

class Person{
public:
    Person(double key, string name);
    Person(double key, string name, size_t sum);

    double getKey();
    string& getName();
    size_t& getSum();
    bool& isActive();

    void AddSum(size_t add_sum);
    bool GetSum(size_t get_sum);
    bool TransferTo(Person& person, size_t sum);
    bool TransferFrom(Person& person, size_t sum);

    ~Person();

private:
    double key;
    string name;
    size_t sum;
    bool active;
};

class Database{
public:
    Database();

    double Login(string name);
    double Register(string name);
    size_t GetBalance(double key);
    void AddMoney(double key, size_t value);
    bool GetMoney(double keu, size_t value);
    bool Transfer(double from, double whom, size_t sum);
    void Remove(double index);

    ~Database();

private:
    vector<Person*> persons;
    list<double> inactive_indexes;
};

#endif