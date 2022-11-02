#include "../headers/hr.h"

#include "../headers/employee.h"
using namespace std;

hr::hr(std::string name,float age,int salary):Employee(name,age,HR,salary){
		cout<<"employee of type HR has been created"<<endl;
}

