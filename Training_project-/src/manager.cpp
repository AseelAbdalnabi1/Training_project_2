#include "../headers/manager.h"

#include "../headers/employee.h"
using namespace std;
class MANAGER;

manager::manager(std::string name,float age,int salary):Employee(name,age,MANAGER,salary){
		cout<<"employee of type MANAGER has been created"<<endl;
}
