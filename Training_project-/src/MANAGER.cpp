#include "../headers/MANAGER.h"
#include "../headers/employee.h"
using namespace std;
class MANAGER;

manager::manager(std::string Name,float Age,int Salary):Employee(Name,Age,MANAGER,Salary){
		cout<<"employee of type MANAGER has been created"<<endl;
}
