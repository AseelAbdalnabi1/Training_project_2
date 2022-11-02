#include "../headers/ceo.h"

#include "../headers/employee.h"
using namespace std;
class Employee;

ceo::ceo(std::string name,float age,int salary):Employee(name,age,CEO,salary){
		cout<<"employee of type CEO has been created"<<endl;
}
