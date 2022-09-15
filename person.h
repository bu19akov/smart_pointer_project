#ifndef PERSON_H
#define PERSON_H
#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
#include"license.h"

using namespace std;

class License;

class Person{
  string name;
  unsigned int wealth;
  map<string,unique_ptr<License>> licenses;
public:
  Person(string, unsigned int = 0);
  virtual ~Person() = default;
  void work(string);
  virtual void work(unsigned int) = 0;
  void increase_wealth(unsigned int);
  string get_name() const;
  bool pay_fee(unsigned int);
  void receive_license(unique_ptr<License>);
  void transfer_license(string, shared_ptr<Person>);
  bool eligible(string) const;
  virtual ostream& print(ostream&) const;
};

inline ostream& operator<<(ostream& o, const Person& p){
  return p.print(o);
}

class Worker: public Person{
public:
  Worker(string, unsigned int = 0);
  void work(unsigned int);
  ostream& print(ostream& o) const;
};

class Superworker: public Person{
  unsigned int fee;
public:
  Superworker(unsigned int, string, unsigned int = 0);
  void work(unsigned int);
  ostream& print(ostream&) const;
};

#endif
