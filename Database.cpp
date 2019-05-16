#include "Database.h"

Person::Person(){
    this->sum = 0;
}

Person::Person(size_t sum){
    this->sum = sum;
}

size_t& Person::getSum(){ return sum; }

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

double Database::Login(const string & name){
    auto it = db.find(name);
    if (it != db.end()) return it->second;
    else return -1;
}

double Database::Register(const string & name){
    if (Login(name) > 0) return -1;
    double new_index;
    if (!inactive_indexes.empty()){
        new_index = inactive_indexes.front();
        db.insert(make_pair(name, new_index));
        persons[new_index] = new Person();
        inactive_indexes.pop_front();
    }else{
        new_index = persons.size();
        persons.push_back(new Person());
        db.insert(make_pair(name, new_index));
    }
    return new_index;
}

size_t Database::GetBalance(double key){return persons[key]->getSum();}
void Database::AddMoney(double key, size_t value){ persons[key]->AddSum(value);}
bool Database::GetMoney(double key, size_t value){ return persons[key]->GetSum(value);}

int Database::Transfer(double from, const string & whom, size_t value){
    auto it = db.find(whom);
    if (it == db.end()) return -1;
    if (!persons[from]->TransferTo(*persons[it->second], value)) return -2;
    else return 0;
}

void Database::Remove(const string & name){
    auto it = db.find(name);
    if (it == db.end()) return;
    delete persons[it->second];
    persons[it->second] = nullptr;
    db.erase(it);
}

Database::~Database(){
    for (auto i : persons) delete i;
}