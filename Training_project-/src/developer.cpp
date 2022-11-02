#include "../headers/developer.h"

#include "../headers/employee.h"
using namespace std;
class Employee;
developer::developer(std::string name,float age ,int salary):Employee(name,age,DEVELOPER,salary){
		cout<<"employee of type developer has been created"<<endl;
}
