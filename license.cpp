#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
#include "license.h"
#include "person.h"

License::License(string name, unsigned int salary, unsigned int counter) : name{name}, salary{salary}, counter{counter}{
  if (name.empty())
    throw runtime_error{"name is empty"};
  if (salary <= 0)
    throw runtime_error{"salary must be > 0"};
}

string License::get_guildname() const{
  return name;
}

unsigned int License::get_salary() const{
  return salary;
}

bool License::valid() const{
  if (counter <= 3)
    return true;
  else
    return false;
}

bool License::use(){
  if (!valid())
    return false;
  else{
    ++counter;
    return true;
  }
}

ostream& License::print(ostream& o) const {
  return o << "[License for " << name << ", Salary: " << salary << ", Used: " << counter << ']';
}
