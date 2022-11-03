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
Department::Department(string department_name){
	setDepartmentName(departmentName);
	setDepartmentId(id+=1);
	cout<<"Department with : "<<department_name<<" & ID : "<<this->getDepartmentId()<<" has been created!"<<endl;
}
void Department::setDepartmentId(int department_id){//private function
	this->department_id=department_id;
}
int Department::getDepartmentId(){
	return this->department_id;
}
vector <Employee> *Department::getEmployeesOfDepartment(){
	return &(this->employeesOfDepartment);
}
vector <Employee> *Department::getEmployeesOfDepartment(Company *company_object){
	Department *dep=company_object->findDepartment(this);
	if(!(dep==nullptr)){
		return dep->getEmployeesOfDepartment();
	}
	else{
		cout<<"department not found in company"<<endl;
		return {};
	}

}
bool Department::isAnySubDeps(){
	return getSubDepartments()->size()!=0;
}
vector<Department> *Department::getSubDepartments(){
    return &(subDepartments);
}
vector<Department> *Department::getSubDepartments(Company *company_object){
	Department *dep=company_object->findDepartment(this);
	if(dep!=nullptr){//parent found
				return dep->getSubDepartments();
		}
	else{//parent not found
		cout<<"department not found in company "<<endl;
		return nullptr;
	}
}

string Department::getDepartmentName(){
	return this->departmentName;
}
void Department::setDepartmentName(string department_name){
    this->departmentName=department_name;
}
bool Department::removeEmployeeFromDepartment(Employee employee){//??
	auto i=find(this->employeesOfDepartment.begin(), this->employeesOfDepartment.end(), employee);//searching for emp in Employee of department
		if(i != this->employeesOfDepartment.end()){
			this->employeesOfDepartment.erase(i);
			cout<<"Employee with "<<employee.getEmployeeId()<<" removed successfully from "<<this->departmentName<<endl;
			return true;//emp found in department and has been deleted

		}else{
			cout<<"Employee with "<<employee.getEmployeeId()<<" dose not exists in "<<this->departmentName<<endl;
			return false;//emp did not found in department and has not been deleted
		}
}
void Department::removeEmployeeFromDepartment(Employee employee,Company *company_object){
	Department *dep=company_object->findDepartment(this);//we try to find the department(search for the required department)
	if(!(dep==nullptr)){//the required department is found
		bool deletedFromDep=dep->removeEmployeeFromDepartment(employee);
		if(deletedFromDep==1){//we make sure the emp is found in the required department and has been deleted
			Employee *empInOtherDep=company_object->findEmployeeInDepartment(employee,company_object->getMainDepartments());//we check if the emp belongs to another department in company---using findEmployeeInDep function
			if(empInOtherDep==nullptr){	//if emp  belongs to another dep---we won't delete it form employeesOfAllCompany
				Employee* EmpPtr=company_object->findEmployeeInCompany(employee);
			if(EmpPtr!=nullptr){
				company_object->employeesOfAllCompany.erase(remove(company_object->employeesOfAllCompany.begin(), company_object->employeesOfAllCompany.end(), (*EmpPtr)),  company_object->employeesOfAllCompany.end());
				cout<<"employee found and deleted from employeesOfAllCompany successfully"<<endl;
				return;
			}else{
				cout<<"employee can't be found in employeesOfAllCompany and has not been deleted"<<endl;
				return;
			}
		}
		else{
			cout<<"emp is part of another department and thus can't be deleted from employeesOfAllCompany"<<endl;
			return;
		}

	}else if(deletedFromDep==0){
		return;
		}
	}
	else{
		cout<<" Department not found in Company & Employee not removed !"<<endl;
		return;
	}
}
bool Department::addEmployeeToDepartment(Employee employee){
	auto i=find(this->employeesOfDepartment.begin(), this->employeesOfDepartment.end(), employee);//searching employees of department
		if(i == this->employeesOfDepartment.end()){//if employee not found then add it
	        this->employeesOfDepartment.push_back(employee);
	        cout<<"employee has successfully added in department"<<endl;
	        return true;
	}else if(i != this->employeesOfDepartment.end()){// if found --employee is not added to department and the function will return with false value
		cout<<"employee already exists in department"<<endl;
		return false;
	}
}
void Department::addEmployeeToDepartment(Employee employee,Company *company_object){
	Department *dep=company_object->findDepartment(this);
	if(!(dep==nullptr)){
		if(dep->addEmployeeToDepartment(employee)){
			Employee* EmpPtr=company_object->findEmployeeInCompany(employee);
			if(EmpPtr==nullptr){
				company_object->employeesOfAllCompany.push_back(employee);
				cout<<"employee added to company emp name: "<<employee.getName()<<endl;
				return;
			}else{
				cout<<"employee already found in employeesOfAllCompany"<<endl;
				return;
			}
		}
		else
			return;

	}else{
		cout<<" Department not found in Company & Employee not added !"<<endl;
		return;
	}

}
void Department::RemoveSubDepartment(Department department){
     auto i=find(this->getSubDepartments()->begin(), this->getSubDepartments()->end(),department);
     if(i!=this->getSubDepartments()->end()){
    	 this->getSubDepartments()->erase(i);
   	     cout<<"Sub_department "<<department.departmentName<<" removed successfully from"<<this->departmentName<<endl;
   	     return;
     }else{
    	 cout<<"sub_department "<<department.departmentName<<"dose not exists in "<<this->departmentName<<endl;
    	 return;
     }
	}
void Department::RemoveSubDepartment(Department department,Company *company_object){
	Department *dep=company_object->findDepartment(this);
	if(!(dep==nullptr)){
		dep->RemoveSubDepartment(department);
		this->RemoveSubDepartment(department);
		return;
	}else{
		cout<<"Parent Department not found in Company"<<endl;
		return;
	}
}
void Department::addSubDepartment(Department department){
	subDepartments.push_back(department);
	cout<<"sub-department ("<<department.getDepartmentName()<< ")added successfully"<<endl;

}
void Department::addSubDepartment(Department department,Company *company_object){
	Department* dep=company_object->findDepartment(this);
	cout<<"in the add subDep :  "<<this->getDepartmentName()<<endl;;
		if(dep!=nullptr){
			dep->addSubDepartment(department);
			this->addSubDepartment(department);
			return;
		}else{
			cout<<" Department not found in Company"<<endl;
			return;
		}
delete dep;
}
bool Department::operator == (Department department_object){
	return (department_object.getDepartmentId() == this->getDepartmentId());
}
bool Department::operator == (int const &department_id){
	return (department_id == this->getDepartmentId());
}
Department::~Department(){
}

