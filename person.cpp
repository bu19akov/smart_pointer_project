#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
#include "person.h"
#include "license.h"

Person::Person(string name, unsigned int wealth) : name{name}, wealth{wealth}{
  if (name.empty())
    throw runtime_error{"name is empty"};
}

void Person::work(string guild){
  bool check {false};
  for (auto& l : licenses){
    if (l.first == guild && l.second->use()){
      work(l.second->get_salary());
      check = true;
    }
  }
  if (check == false)
    throw runtime_error{"no licenses or no more available"};
}

void Person::increase_wealth(unsigned int i){
  wealth += i;
}

string Person::get_name() const{
  return name;
}

bool Person::pay_fee(unsigned int i){
  if (i == 0 || wealth < i)
    return false;
  else wealth -= i;
  return true;
}

void Person::receive_license(unique_ptr<License> l){
  bool check{false};
  if (!licenses.empty()){
    for (auto& li : licenses){
      if (li.first == l->get_guildname()){
        auto it = licenses.find(l->get_guildname());
        it->second.release();
        it->second = move(l);
        check = true;
      }
    }
  }
  if (check == false)
    licenses.insert(make_pair(l->get_guildname(),move(l)));
}

void Person::transfer_license(string l, shared_ptr<Person> p){
  bool check{false};
  for (auto it = licenses.begin(); it != licenses.end(); ){
    if (it->second->get_guildname() == l){
      p->receive_license(move(licenses.find(l)->second));
      it = licenses.erase(it);
      check = true;
    }
    else
      ++it;
  }
  if (check == false)
    throw runtime_error{"no License l in this-Object"};
}

bool Person::eligible(string l) const{
  bool out{false};
  for (const auto& li : licenses){
    if (li.second->get_guildname() == l && li.second->valid())
      out = true;
  }
  return out;
}

ostream& Person::print(ostream& o) const{
  o << name << ", " << wealth << " Coins, {";
  bool first{true};
  for (const auto& l : licenses){
    if (first)
      first = false;
    else
      o << ", ";
    o << *l.second;
  }
  return o << "}]";
}

Worker::Worker(string s, unsigned int i) : Person(s, i){}

void Worker::work(unsigned int i){
  Person::increase_wealth(i);
}

ostream& Worker::print(ostream& o) const{
  cout << "[Worker ";
  return Person::print(o);
}

Superworker::Superworker(unsigned int fee, string s, unsigned int w) : Person(s, w), fee{fee} {}

void Superworker::work(unsigned int i){
  Person::increase_wealth(i+fee);
}

ostream& Superworker::print(ostream& o) const{
  cout << "[Superworker ";
  return Person::print(o);
}
