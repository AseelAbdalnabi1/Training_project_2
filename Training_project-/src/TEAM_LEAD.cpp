#include "../headers/TEAM_LEAD.h"
#include "../headers/employee.h"
using namespace std;
team_lead::team_lead(std::string Name,float Age,int Salary):Employee(Name,Age,TEAM_LEAD,Salary){
		cout<<"employee of type team_lead has been created"<<endl;
}
