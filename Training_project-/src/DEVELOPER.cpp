#include "../headers/DEVELOPER.h"
#include "../headers/employee.h"
using namespace std;
class Employee;
developer::developer(std::string Name,float Age ,int Salary):Employee(Name,Age,DEVELOPER,Salary){
		cout<<"employee of type developer has been created"<<endl;
}
