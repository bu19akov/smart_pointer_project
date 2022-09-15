#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<stdexcept>
#include<set>
#include<algorithm>
#include<map>
#include "guild.h"
#include "license.h"
#include "person.h"

Guild::Guild(string name, unsigned fee, unsigned sal, const vector<shared_ptr<Person>>& members1) : name{name}, fee{fee}, salary{sal}{
    for(const auto& m : members1){
    for (const auto& m2 : members){
      if (m2.second->get_name() == m->get_name())
        throw runtime_error{"not unique Persons in members"};
    }
    members.insert({m->get_name(), move(m)});
  }
  if (name.empty())
      throw runtime_error{"name is empty"};
  if (fee <= 0)
    throw runtime_error{"illegal fee"};
  if (salary <= 0)
      throw runtime_error{"illegal salary"};
}
    
bool Guild::add_member(shared_ptr<Person> p){
  if (members.count(p->get_name()) > 0)
    return false;
  members.insert(make_pair(p->get_name(), move(p)));
  return true;
}

bool Guild::remove_member(string n){
  if (!members.count(n))
    return false;
  auto it = members.find(n);
  members.erase(it);
  return true;
}

void Guild::grant_license(string n){
  if (!members.count(n))
    throw runtime_error{"no such member"};
  auto it = members.find(n);
  if (!it->second->pay_fee(fee))
    throw runtime_error{"no wealth to pay"};
  unique_ptr<License> l = make_unique<License>(name, salary);
  it->second->receive_license(move(l));
}

bool Guild::offer_job(shared_ptr<Person> p) const{
  if (members.count(p->get_name()) > 0) {
    p->work(salary*2);
    return true;
  }
  else if (p->eligible(name)) {
    p->work(name);
    return true;
  }
  return false;
}

ostream& Guild::print(ostream& o) const{
  o << '[' << name << ", License fee: " << fee << ", Job salary: " << salary << ", {";
  bool first{true};
  for (const auto& m : members){
    if (first)
      first = false;
    else
      o << ", ";
    o << m.second->get_name();
  }
  return o << "}]";
}
