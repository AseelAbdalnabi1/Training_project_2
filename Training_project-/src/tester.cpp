#include "../headers/tester.h"

#include "../headers/employee.h"
using namespace std;
tester::tester(std::string name,float age,int salary):Employee(name,age,TESTER,salary){
		cout<<"employee of type TESTER has been created"<<endl;
}
