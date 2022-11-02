/*
 * employee.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: aseel
 */
#include "../headers/employee.h"
#include "../headers/company.h"
#include <iostream>

#include "../headers/ceo.h"
#include "../headers/developer.h"
#include "../headers/hr.h"
#include "../headers/manager.h"
#include "../headers/team_lead.h"
#include "../headers/tester.h"
using namespace std;
#include <string>
#include <algorithm>
class Company;
class Employee;
int Employee::id=0;

Employee::Employee(string name,float age ,ROLE role,int salary):Person(name,age){
	this->setRole(role);
	this->setSalary(salary);
	this->setEmployeeId(id+=1);
	cout<<"Employee created! with empId : "<<this->getEmployeeId()<<endl;
}

Employee* Employee::create(string name,float age ,ROLE roleType,int salary){//factory design pattern on employee ROLE
	Employee *emp=nullptr;
	if (roleType == CEO){
		emp=new ceo(name,age,salary);
		return emp;
	}
	else if (roleType == MANAGER){
		return new manager(name,age,salary);
	}
	else if (roleType == TEAM_LEAD){
		return new team_lead(name,age,salary);
	}else if (roleType == DEVELOPER){
		return new developer(name,age,salary);
	}else if (roleType == TESTER){
		return new tester(name,age,salary);
	}else if (roleType == HR){
		return new hr(name,age,salary);
	}
	else
		return NULL;
}
void Employee::setRole(ROLE role){
	this->role=role;
}
void Employee::setRole(ROLE role,Company *company_object){
	Employee *Emp=company_object->findEmployeeInDepartment(*this,company_object->getMainDepartments());
	if(!(Emp==nullptr)){
	    Emp->setRole(role);
	    this->setRole(role);
	    return;
	}else{
		Emp=company_object->findEmployeeInCompany(*this);
		if(!(Emp==nullptr)){
			Emp->setRole(role);
			this->setRole(role);
		}else{
		    cout<<"Employee not found in Company"<<endl;
		    return;
		}
	}

}
string Employee::getRole(){
	switch(this->role){
	case 0:
		return "CEO";
	case 1:
		return "MANAGER";
	case 2:
		return "TEAM_LEAD";
	case 3:
		return "DEVELOPER";
	case 4:
		return "TESTER";
	case 5:
		return "HR";
	default:
		return "No_Role";
	}

}
string Employee::getRole(Company *company_object){
	Employee *Emp=company_object->findEmployeeInDepartment(*this,company_object->getMainDepartments());
	if(!(Emp==nullptr)){
	    return Emp->getRole();
	}else{
		Emp=company_object->findEmployeeInCompany(*this);
		if(!(Emp==nullptr)){
			return Emp->getRole();
		}else{
			cout<<"Employee not found in Company"<<endl;
            return 	"NO_ROLE";
		}
	}
}
void Employee::setSalary(int salary){
	this->salary=salary;
}
void Employee::setSalary(int salary,Company *company_object){
	Employee *Emp=company_object->findEmployeeInDepartment(*this,company_object->getMainDepartments());
	if(!(Emp==nullptr)){
	     Emp->setSalary(salary);
	     this->setSalary(salary);
	     return;
	}else{
		Emp=company_object->findEmployeeInCompany(*this);
		if(!(Emp==nullptr)){
			Emp->setSalary(salary);
			this->setSalary(salary);
		}else{
			cout<<"Employee Not found in Company"<<endl;
			return;
		}
	}
}
int Employee::getSalary(){
		return this->salary;
}
int Employee::getSalary(Company *company_object){
	Employee *Emp=company_object->findEmployeeInDepartment(*this,company_object->getMainDepartments());
	if(!(Emp==nullptr)){
        return Emp->getSalary();

	}else{
		Emp=company_object->findEmployeeInCompany(*this);
		if(!(Emp==nullptr)){
			 return Emp->getSalary();
		}else{
			cout<<"Employee Not found in Company"<<endl;
			return -99999;
		}
	}
}
void Employee::setEmployeeId(int employee_id){//private function
	this->employee_id=employee_id;
}

int Employee::getEmployeeId(){
    return this->employee_id;
}
bool Employee::operator == (Employee Employee){
	return (Employee.getEmployeeId() == this->getEmployeeId());
}
bool Employee::operator == (int const &employee_id){
	return (employee_id == this->getEmployeeId());
}
Employee::~Employee(){
}



