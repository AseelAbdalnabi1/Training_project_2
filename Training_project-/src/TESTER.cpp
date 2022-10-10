#include "../headers/TESTER.h"
#include "../headers/employee.h"
using namespace std;
tester::tester(std::string Name,float Age,int Salary):Employee(Name,Age,TESTER,Salary){
		cout<<"employee of type TESTER has been created"<<endl;
}
