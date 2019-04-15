#include "Database.h"

Person::Person(double key, string name){
    this->key = key;
    this->name = name;
    this->sum = 0;
    active = true;
}

Person::Person(double key, string name, size_t sum){
    this->key = key;
    this->name = name;
    this->sum = sum;
    active = true;
}

double Person::getKey(){ return key; }
string& Person::getName(){ return name; }
size_t& Person::getSum(){ return sum; }
bool& Person::isActive(){ return active; }

void Person::AddSum(size_t sum){ this->sum += sum; }
bool Person::GetSum(size_t sum){
    if (this->sum >= sum){
        this->sum -= sum;
        return true;
    }else return false;
}
bool Person::TransferTo(Person& person, size_t sum){
    if (this->sum >= sum){
        person.getSum() += sum;
        this->sum -= sum;
        return true;
    }else return false;
}
bool Person::TransferFrom(Person& person, size_t sum){
    if (person.getSum() >= sum){
        person.getSum() -= sum;
        this->sum += sum;
        return true;
    }else return false;
}

Person::~Person(){}

///////////////////////////////////////////////////////////////////////////////////////////

Database::Database(){}

double Database::Login(string name){
    for (auto i : persons){
        if (i->getName() == name){
            if (i->isActive()) return i->getKey();
            else return -2;
        }
    }
    return -1;
}
double Database::Register(string name){
    if (!inactive_indexes.empty()){
        double index = inactive_indexes.front();
        inactive_indexes.pop_front();
        persons[index]->getName() = name;
        persons[index]->getSum() = 0;
        persons[index]->isActive() = true;
        return index;
    }else{
        persons.push_back(new Person(persons.size(), name));
        return persons.size() - 1;
    }
}

size_t Database::GetBalance(double key){return persons[key]->getSum();}
void Database::AddMoney(double key, size_t value){ persons[key]->AddSum(value);}
bool Database::GetMoney(double key, size_t value){ return persons[key]->GetSum(value);}
bool Database::Transfer(double from, double whom, size_t value){ return persons[from]->TransferTo(*persons[whom], value);}

void Database::Remove(double index){
    persons[index]->isActive() = false;
}

Database::~Database(){
    for (auto i : persons) delete i;
}