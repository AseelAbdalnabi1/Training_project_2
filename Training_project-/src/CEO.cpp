#include "../headers/CEO.h"
#include "../headers/employee.h"
using namespace std;
class Employee;

ceo::ceo(std::string Name,float Age,int Salary):Employee(Name,Age,CEO,Salary){
		cout<<"employee of type CEO has been created"<<endl;
}
