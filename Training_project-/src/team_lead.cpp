#include "../headers/team_lead.h"
#include "../headers/employee.h"
using namespace std;
team_lead::team_lead(std::string name,float age,int salary):Employee(name,age,TEAM_LEAD,salary){
		cout<<"employee of type team_lead has been created"<<endl;
}
