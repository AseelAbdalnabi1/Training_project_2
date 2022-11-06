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

Employee::Employee(string name,float age ,ROLE role,int salary):Person(name,age){//constructor of employee
	this->setRole(role);//set the role
	this->setSalary(salary);//set the salay
	this->setEmployeeId(id+=1);//set the id
	cout<<"Employee created! with empId : "<<this->getEmployeeId()<<endl;
}

Employee* Employee::create(string name,float age ,ROLE roleType,int salary){//factory design pattern on employee ROLE-----creates an employee based on his role
	if (roleType == CEO){//if the role required is ceo then creates a ceo object and returns it
		return new ceo(name,age,salary);
	}
	else if (roleType == MANAGER){//if the role required is manager then creates a manager object and returns it
		return new manager(name,age,salary);
	}
	else if (roleType == TEAM_LEAD){//if the role required is team_load then creates a team_lrad object and returns it
		return new team_lead(name,age,salary);
	}else if (roleType == DEVELOPER){//if the role required is developer then creates a developer object and returns it
		return new developer(name,age,salary);
	}else if (roleType == TESTER){//if the role required is tester then creates a tester object and returns it
		return new tester(name,age,salary);
	}else if (roleType == HR){//if the role required is hr then creates a hr object and returns it
		return new hr(name,age,salary);
	}
	else//otherwise returns NULL
		return NULL;
}
void Employee::setRole(ROLE role){//set the role of this employee
	this->role=role;
}
void Employee::setRole(ROLE role,Company *company_object){//set the role of this employee if belongs to company
	Employee *Emp=company_object->findEmployeeInDepartment(*this,company_object->getMainDepartments());//check if this employee belongs to any department of the company
	if(Emp!=nullptr){//if found in department of company then set role of this employee, then returns
	    Emp->setRole(role);
	    this->setRole(role);
	}else{//if employee is not in any department of company then check if it is a floating employee
		Emp=company_object->findEmployeeInCompany(*this);//check if employee is a floating employee
		if(Emp!=nullptr){//if employee is a floating employee then set the role of employee
			Emp->setRole(role);
			this->setRole(role);
		}else{//employee is not a floating employee
		    cout<<"Employee not found in Company"<<endl;
		}
	}
	return;
}
string Employee::getRole(){//returns the role of this employee
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
string Employee::getRole(Company *company_object){//returns the role of this employee if belongs to a company
	Employee *Employee=company_object->findEmployeeInCompany(*this);//check if employee is in company
	if(Employee!=nullptr){//if employee found in company then returns the role
		return Employee->getRole();
	}else{//if employee is not found in company then returns no_role sting
		cout<<"Employee not found in Company"<<endl;
        return 	"NO_ROLE";
	}
}
void Employee::setSalary(int salary){//set the salary of this employee
	this->salary=salary;
}
void Employee::setSalary(int salary,Company *company_object){//set the salary of this employee if he is part of the company
	Employee *Emp=company_object->findEmployeeInDepartment(*this,company_object->getMainDepartments());//check if this employee object belongs to department in the company by getting the iterator of it
	if(Emp!=nullptr){//if found then set the salary of this employee then return
	     Emp->setSalary(salary);
	     this->setSalary(salary);
	     return;
	}else{//if not found in any department of company
		Emp=company_object->findEmployeeInCompany(*this);//check if the employee is a floating employee of the company
		if(Emp!=nullptr){//if the employee is a floating employee of the company then set the salary
			Emp->setSalary(salary);
			this->setSalary(salary);
		}else{//if not a floating employee then return
			cout<<"Employee Not found in Company"<<endl;
			return;
		}
	}
}
int Employee::getSalary(){//get the salary of this employee
		return this->salary;
}
int Employee::getSalary(Company *company_object){//get the salary of this employee if he is part of the company
    Employee *Emp=company_object->findEmployeeInCompany(*this);//check if the employee is in the company
	if(Emp!=nullptr){//if the employee is found then return the salary
		 return Emp->getSalary();
	}else{//if employee not found then returns -99999
		cout<<"Employee Not found in Company"<<endl;
		return -99999;
	}
}
void Employee::setEmployeeId(int employee_id){//private function to set a unique value of this employee(called be the constructor)
	this->employee_id=employee_id;
}

int Employee::getEmployeeId(){//returns the id of this employee object
    return this->employee_id;
}
bool Employee::operator == (Employee Employee){//overload operator == with Employee object parameter
	return (Employee.getEmployeeId() == this->getEmployeeId());
}
bool Employee::operator == (int const &employee_id){//overload operator == with employee_id parameter
	return (employee_id == this->getEmployeeId());
}
Employee::~Employee(){//destructor
}



