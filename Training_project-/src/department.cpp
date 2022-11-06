 /*
 * department.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: aseel
 */

#include "../headers/department.h"
#include <iostream>
#include "../headers/company.h"
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
using namespace std;
class Department;
class Company;
int Department::id=0;
Department::Department(string department_name){//department constructor
	setDepartmentName(department_name);//set the name of department
	setDepartmentId(id+=1);//set the id of department
	cout<<"Department with : "<<department_name<<" & ID : "<<this->getDepartmentId()<<" has been created!"<<endl;
}
void Department::setDepartmentId(int department_id){//private function
	this->department_id=department_id;//function to make the id of the each department unique
}
int Department::getDepartmentId(){//get the id of department
	return this->department_id;
}
vector <Employee> *Department::getEmployeesOfDepartment(){//returns the vector of employees of this department
	return &(this->employeesOfDepartment);
}
vector <Employee> *Department::getEmployeesOfDepartment(Company *company_object){//returns the vector of employees of this department if it is a part of the company
	Department *dep=company_object->findDepartment(this);//first --check if this department is part of the company by getting the iterator of department in company
	if(dep!=nullptr){//if department is found in company
		return dep->getEmployeesOfDepartment(); //return the employees vector of the department
	}
	else{//if not found in comapny --returns empty vector
		cout<<"department not found in company"<<endl;
		return {};
	}

}
bool Department::isAnySubDepartments(){//check if there is any sub departments -----used in some APIs
	return getSubDepartments()->size()!=0;
}
vector<Department> *Department::getSubDepartments(){//returns the subDepartments vector for this department
    return &(subDepartments);
}
vector<Department> *Department::getSubDepartments(Company *company_object){//returns the subDepartments vector for this department if it is a part of company
	Department *dep=company_object->findDepartment(this);//first --check if this department is part of the company by getting the iterator of department in company
	if(dep!=nullptr){//if parent(this) department found in company , then returns subDepartments vector of it
				return dep->getSubDepartments();
		}
	else{//if parent (this) department not found in company then returns empty vector
		cout<<"department not found in company "<<endl;
		return {};
	}
}

string Department::getDepartmentName(){//retruns the department name
	return this->departmentName;
}
void Department::setDepartmentName(string department_name){//sets the department name
    this->departmentName=department_name;
}
bool Department::removeEmployeeFromDepartment(Employee employee){//to remove employee object from this department
	auto i=find(this->employeesOfDepartment.begin(), this->employeesOfDepartment.end(), employee);//searching for employee object in Employees vector of this department
	if(i != this->employeesOfDepartment.end()){//if employee is found in this department, then erase it & return true
		this->employeesOfDepartment.erase(i);
		cout<<"Employee with "<<employee.getEmployeeId()<<" removed successfully from "<<this->departmentName<<endl;
		return true;//emp found in department and has been deleted
	}//if employee not found in department then return false
	cout<<"Employee with "<<employee.getEmployeeId()<<" dose not exists in "<<this->departmentName<<endl;
	return false;//emp did not found in department and has not been deleted

}
void Department::removeEmployeeFromDepartment(Employee employee,Company *company_object){//to remove employee object from this department if it is a part of company
	Department *dep=company_object->findDepartment(this);//first --check if this department is part of the company by getting the iterator of department in company
	if(dep!=nullptr){//if the required department is found in comapny
		if(dep->removeEmployeeFromDepartment(employee)){//we make sure the employee is found in the required department and has been deleted
			Employee *employeeInOtherDepartment=company_object->findEmployeeInDepartment(employee,company_object->getMainDepartments());//we check if the employee belongs to another department in company---using findEmployeeInDepartment function
			if(employeeInOtherDepartment==nullptr){	//if employee does not belong to another department in company---we will delete it form employeesOfAllCompany vector
				company_object->removeEmployeeFromCompany(employee);
			}
			else{
				cout<<"employee is part of another department and thus can't be deleted from employeesOfAllCompany"<<endl;
			}
		}
	}
	else{//if the department is not part of company
		cout<<" Department : "<<this->getDepartmentName()<<"not found in Company & Employee not removed !"<<endl;
	}
	return;
}
bool Department::addEmployeeToDepartment(Employee employee){//to add employee to this department
	auto i=find(this->employeesOfDepartment.begin(), this->employeesOfDepartment.end(), employee);//searching in employees of department---to make sure that this employee is not already in this department
		if(i == this->employeesOfDepartment.end()){//if employee not found then add it & return true
	        this->employeesOfDepartment.push_back(employee);
	        cout<<"employee has successfully added in department"<<endl;
	        return true;
	}else if(i != this->employeesOfDepartment.end()){// if found --employee is not added to department and the function will return false
		cout<<"employee already exists in department"<<endl;
		return false;
	}
}
void Department::addEmployeeToDepartment(Employee employee,Company *company_object){//to add employee to this department if it is a part of company
	Department *dep=company_object->findDepartment(this);//check if this department is part of the company
	if(dep!=nullptr){//if this department is found in company then add the employee to it
		if(dep->addEmployeeToDepartment(employee)){//if the employee is added successfully to department ,we add the employee to the employeesOfAllCompany vector
			company_object->addEmployeeToCompany(employee);
		}
	}else{//if department is not found in company
		cout<<" Department not found in Company & Employee not added !"<<endl;
		return;
	}

}
void Department::RemoveSubDepartment(Department department){//to remove a sub department from this department
     auto i=find(this->getSubDepartments()->begin(), this->getSubDepartments()->end(),department);//looking for the required sub department in the vector of sub departments in this department
     if(i!=this->getSubDepartments()->end()){//if the required sub department found ,then delete it and return
    	 this->getSubDepartments()->erase(i);
   	     cout<<"Sub_department "<<department.departmentName<<" removed successfully from"<<this->departmentName<<endl;
   	     return;
     }else{//if the required sub department is not found then return
    	 cout<<"sub_department "<<department.departmentName<<"dose not exists in "<<this->departmentName<<endl;
    	 return;
     }
}
void Department::RemoveSubDepartment(Department department,Company *company_object){//to remove a sub department from this department if it is a part of company
	Department *dep=company_object->findDepartment(this);//first --check if this department is part of the company by getting the iterator of department in company
	if(dep!=nullptr){//if this department is found in company, then delete the required sub department of it
		dep->RemoveSubDepartment(department);
		this->RemoveSubDepartment(department);
		return;
	}else{//if this department is not found in company, then return
		cout<<"Parent Department not found in Company"<<endl;
		return;
	}
}
void Department::addSubDepartment(Department department){//to add a sub department to this department
	subDepartments.push_back(department);
	cout<<"sub-department ("<<department.getDepartmentName()<< ")added successfully"<<endl;

}
void Department::addSubDepartment(Department department,Company *company_object){//to add a sub department to this department if it is a part of company
	Department* dep=company_object->findDepartment(this);//first --check if this department is part of the company by getting the iterator of department in company
		if(dep!=nullptr){//if this department is found in company, then add the required sub department to it
			dep->addSubDepartment(department);
			this->addSubDepartment(department);
			return;
		}else{//if this department is not found in company, then return
			cout<<" Department not found in Company"<<endl;
			return;
		}
delete dep;
}
bool Department::operator == (Department department_object){//overload operator == with department_object parameter
	return (department_object.getDepartmentId() == this->getDepartmentId());
}
bool Department::operator == (int const &department_id){//overload operator == with department_id parameter
	return (department_id == this->getDepartmentId());
}
Department::~Department(){//destructor
}

