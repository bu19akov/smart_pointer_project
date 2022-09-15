#ifndef GUILD_H
#define GUILD_H
#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
#include "person.h"

using namespace std;

class Person;
class License;

class Guild{
  string name;
  unsigned int fee;
  unsigned int salary;
  map<string,shared_ptr<Person>> members;
public:
  Guild(string, unsigned, unsigned, const vector<shared_ptr<Person>>& = {});
  bool add_member(shared_ptr<Person>);
  bool remove_member(string);
  void grant_license(string);
  bool offer_job(shared_ptr<Person>) const;
  ostream& print(ostream&) const;
};

inline ostream& operator<<(ostream& o, const Guild& g){
  return g.print(o);
}

#endif
