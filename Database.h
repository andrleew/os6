#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>

using namespace std;

class Person{
public:
    Person();
    Person(size_t sum);

    size_t& getSum();

    void AddSum(size_t add_sum);
    bool GetSum(size_t get_sum);
    bool TransferTo(Person& person, size_t sum);
    bool TransferFrom(Person& person, size_t sum);

    ~Person();

private:
    size_t sum;
};

class Database{
public:
    Database();

    double Login(const string & name);
    double Register(const string & name);
    size_t GetBalance(double key);
    void AddMoney(double key, size_t value);
    bool GetMoney(double keu, size_t value);
    int Transfer(double from, const string & whom, size_t sum);
    void Remove(const string & name);

    ~Database();

private:
    vector<Person*> persons;
    list<double> inactive_indexes;
    unordered_map <string, double> db;
};

#endif