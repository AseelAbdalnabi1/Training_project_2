/*
 * employee.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: aseel
 */
#include "../headers/employee.h"
#include "../headers/company.h"
#include "../headers/CEO.h"
#include "../headers/HR.h"
#include "../headers/TESTER.h"
#include "../headers/MANAGER.h"
#include "../headers/TEAM_LEAD.h"
#include "../headers/DEVELOPER.h"
#include <iostream>
using namespace std;
#include <string>
#include <algorithm>
class Company;
class Employee;
Employee * findEmployeeInDep(Employee NeededEmp,Company *compObj,vector<Department>* RangeOfDeps);
Employee *findEmployeeInCompany(Employee emp,Company *compObj);
int Employee::ID=0;

Employee::Employee(string Name,float Age ,ROLE Role,int Salary):Person(Name,Age){
	this->setRole(Role);
	this->setSalary(Salary);
	this->setEmpId(ID+=1);
	cout<<"Employee created! with empId : "<<this->getEmpId()<<endl;
}

Employee* Employee::Create(string Name,float Age ,ROLE RoleType,int Salary){//factory design pattern on employee ROLE
	Employee *emp=nullptr;
	if (RoleType == CEO){
		emp=new ceo(Name,Age,Salary);
		return emp;
	}
	else if (RoleType == MANAGER){
		return new manager(Name,Age,Salary);
	}
	else if (RoleType == TEAM_LEAD){
		return new team_lead(Name,Age,Salary);
	}else if (RoleType == DEVELOPER){
		return new developer(Name,Age,Salary);
	}else if (RoleType == TESTER){
		return new tester(Name,Age,Salary);
	}else if (RoleType == HR){
		return new hr(Name,Age,Salary);
	}
	else
		return NULL;
}
void Employee::setAgeInComapny(float Age,Company *compObj){
	Employee *Emp=findEmployeeInDep(*this,compObj,compObj->getMainDeps());
	if(!(Emp==nullptr)){
	    Emp->Person::setAge(Age);
	    this->Person::setAge(Age);
	    return;
	}else{
		Emp=findEmployeeInCompany(*this,compObj);
		if(!(Emp==nullptr)){
			Emp->Person::setAge(Age);
			this->Person::setAge(Age);
		}else{
		    cout<<"Employee not found in Company"<<endl;
		    return;
		}
	}

}
float Employee::getAgeFromCompany(Company *compObj){
	Employee *Emp=findEmployeeInDep(*this,compObj,compObj->getMainDeps());
	if(!(Emp==nullptr)){
		return Emp->Person::getAge();
	}else{
		Emp=findEmployeeInCompany(*this,compObj);
		if(!(Emp==nullptr)){
			return Emp->Person::getAge();
		}else{
			cout<<"Employee not found in Company"<<endl;
	        return 	-9999;
		}
	}
}
void Employee::setNameInCompany(std::string Name,Company *compObj){
	Employee *Emp=findEmployeeInDep(*this,compObj,compObj->getMainDeps());
	if(!(Emp==nullptr)){
	    Emp->Person::setName(Name);
	    this->setName(Name);
	    return;
	}else{
		Emp=findEmployeeInCompany(*this,compObj);
		if(!(Emp==nullptr)){
			Emp->Person::setName(Name);
			this->setName(Name);
		}else{
		    cout<<"Employee not found in Company"<<endl;
		    return;
		}
	}
}
string Employee::getNameFromComp(Company *compObj){
	Employee *Emp=findEmployeeInDep(*this,compObj,compObj->getMainDeps());
	if(!(Emp==nullptr)){
		return Emp->Person::getName();
	}else{
		Emp=findEmployeeInCompany(*this,compObj);
		if(!(Emp==nullptr)){
			return Emp->Person::getName();
		}else{
			cout<<"Employee not found in Company"<<endl;
		    return 	this->Person::getName();
		}
	}
}

void Employee::setRole(ROLE Role){
	this->Role=Role;
}
void Employee::setRole(ROLE Role,Company *compObj){
	Employee *Emp=findEmployeeInDep(*this,compObj,compObj->getMainDeps());
	if(!(Emp==nullptr)){
	    Emp->setRole(Role);
	    this->setRole(Role);
	    return;
	}else{
		Emp=findEmployeeInCompany(*this,compObj);
		if(!(Emp==nullptr)){
			Emp->setRole(Role);
			this->setRole(Role);
		}else{
		    cout<<"Employee not found in Company"<<endl;
		    return;
		}
	}

}
string Employee::getRole(){
	switch(this->Role){
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
string Employee::getRole(Company *compObj){
	Employee *Emp=findEmployeeInDep(*this,compObj,compObj->getMainDeps());
	if(!(Emp==nullptr)){
	    return Emp->getRole();
	}else{
		Emp=findEmployeeInCompany(*this,compObj);
		if(!(Emp==nullptr)){
			return Emp->getRole();
		}else{
			cout<<"Employee not found in Company"<<endl;
            return 	"NO_ROLE";
		}
	}
}
void Employee::setSalary(int salary){
	this->Salary=salary;
}
void Employee::setSalary(int salary,Company *compObj){
	Employee *Emp=findEmployeeInDep(*this,compObj,compObj->getMainDeps());
	if(!(Emp==nullptr)){
	     Emp->setSalary(salary);
	     this->setSalary(salary);
	     return;
	}else{
		Emp=findEmployeeInCompany(*this,compObj);
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
		return this->Salary;
}
int Employee::getSalary(Company *compObj){
	Employee *Emp=findEmployeeInDep(*this,compObj,compObj->getMainDeps());
	if(!(Emp==nullptr)){
        return Emp->getSalary();

	}else{
		Emp=findEmployeeInCompany(*this,compObj);
		if(!(Emp==nullptr)){
			 return Emp->getSalary();
		}else{
			cout<<"Employee Not found in Company"<<endl;
			return -99999;
		}
	}
}
void Employee::setEmpId(int empID){//private function
	this->empID=empID;
}

int Employee::getEmpId(){
    return this->empID;
}
bool Employee::operator == (Employee Emp){
	return (Emp.getEmpId() == this->getEmpId());
}
bool Employee::operator == (int const &empID){
	return (empID == this->getEmpId());
}
Employee::~Employee(){
}



