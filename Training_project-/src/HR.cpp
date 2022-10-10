#include "../headers/HR.h"
#include "../headers/employee.h"
using namespace std;

hr::hr(std::string Name,float Age,int Salary):Employee(Name,Age,HR,Salary){
		cout<<"employee of type HR has been created"<<endl;
}

