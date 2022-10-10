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
Employee * findEmployeeInDep(Employee NeededEmp,Company *compObj,vector<Department>* RangeOfDeps);

Department * findDepartment(Department *neededDep,Company *compObj);

Employee *findEmployeeInCompany(Employee emp,Company *compObj);
set<string> Department::NameOFDepartments ={};
Department::Department(string DepName,vector<Department> SubDeps,vector<Employee> EmpsOfDep){
    this->setSubDeps(SubDeps);
	this->setEmpsOfDep(EmpsOfDep);
	if(this->setDepName(DepName)){
	cout<<"department created with DepName :"<<this->getDepName()<<endl;
	}
	else{
		cout<<"department name already exits, this object will be destroyed"<<endl;
		Department::~Department();
	}
}
vector <Employee> *Department::getEmpsOfDep(){
	return &(this->EmpsOfDep);
}
vector <Employee> *Department::getEmpsOfDep(Company *compObj){
	Department *dep=findDepartment(this,compObj);
	if(!(dep==nullptr)){
		return dep->getEmpsOfDep();
	}
	else{
		cout<<"department not found in company"<<endl;
		return {};
	}

}
void Department::setEmpsOfDep(vector <Employee> EmpsOfDep){
	this->EmpsOfDep=EmpsOfDep;
}
void Department::setEmpsOfDep(vector <Employee> EmpsOfDep,Company *compObj){
	Department *dep=findDepartment(this,compObj);
	if(!(dep==nullptr)){
		dep->setEmpsOfDep(EmpsOfDep);//added to department
		this->setEmpsOfDep(EmpsOfDep);
		for(auto i=EmpsOfDep.begin();i!=EmpsOfDep.end();i++){
			if(find(compObj->EmpsOfAllCompany.begin(),compObj->EmpsOfAllCompany.end(),(*i))==compObj->EmpsOfAllCompany.end()){
				compObj->EmpsOfAllCompany.push_back((*i));//added to EmpsOfAllCompany
			}
		}
		return;
	}
	else{
		cout<<"department not found in company "<<endl;
		cout<<"Employees are not inserted in department "<<endl;
		return;
	}

}
bool Department::isAnySubDeps(){
	return getSubDeps()->size()!=0;
}
vector<Department> *Department::getSubDeps(){
    return &(SubDeps);
}
vector<Department> *Department::getSubDeps(Company *compObj){
	Department *dep=findDepartment(this,compObj);
	if(dep!=nullptr){//parent found
				return dep->getSubDeps();
		}
	else{//parent not found
		cout<<"department not found in company "<<endl;
		return nullptr;
	}
}
void Department::setSubDeps(vector<Department> SubDeps){
	this->SubDeps=SubDeps;
}
void Department::setSubDeps(vector<Department> SubDeps,Company *compObj){
	Department *dep=findDepartment(this,compObj);
	cout<<dep->getDepName()<<endl;
	if(!(dep==nullptr)){
		cout<<"in setSubDep: "<<dep->getDepName()<<endl;
			dep->setSubDeps(SubDeps);
			this->setSubDeps(SubDeps);
		}
		else{
			cout<<"department not found in company "<<endl;
			cout<<"SubDeps are not inserted in department "<<endl;
			return;
		}
}
string Department::getDepName(){
	return this->DepName;
}
bool Department::setDepName(string DepName){
	if (this->NameOFDepartments.find(DepName) == this->NameOFDepartments.end()) {
		this->NameOFDepartments.insert(DepName);
		this->DepName=DepName;
		return true;
	}
	return false;

}
bool Department::removeEmpFromDep(Employee emp){
	auto i=find(this->EmpsOfDep.begin(), this->EmpsOfDep.end(), emp);//searching for emp in Employee of department
		if(i != this->EmpsOfDep.end()){
			this->EmpsOfDep.erase(i);
			cout<<"Employee with "<<emp.getEmpId()<<" removed successfully from "<<this->DepName<<endl;
			return true;//emp found in department and has been deleted

		}else{
			cout<<"Employee with "<<emp.getEmpId()<<" dose not exists in "<<this->DepName<<endl;
			return false;//emp did not found in department and has not been deleted
		}
}
void Department::removeEmpFromDep(Employee emp,Company *compObj){
	Department *dep=findDepartment(this,compObj);//we try to find the department(search for the required department)
	if(!(dep==nullptr)){//the required department is found
		bool deletedFromDep=dep->removeEmpFromDep(emp);
		if(deletedFromDep==1){//we make sure the emp is found in the required department and has been deleted
			Employee *empInOtherDep=findEmployeeInDep(emp,compObj,compObj->getMainDeps());//we check if the emp belongs to another department in company---using findEmployeeInDep function
			if(empInOtherDep==nullptr){	//if emp  belongs to another dep---we won't delete it form EmpsOfAllCompany
				Employee* EmpPtr=findEmployeeInCompany(emp,compObj);
			if(EmpPtr!=nullptr){
				compObj->EmpsOfAllCompany.erase(remove(compObj->EmpsOfAllCompany.begin(), compObj->EmpsOfAllCompany.end(), (*EmpPtr)),  compObj->EmpsOfAllCompany.end());
				cout<<"employee found and deleted from EmpsOfAllCompany successfully"<<endl;
				return;
			}else{
				cout<<"employee can't be found in EmpsOfAllCompany and has not been deleted"<<endl;
				return;
			}
		}
		else{
			cout<<"emp is part of another department and thus can't be deleted from EmpsOfAllCompany"<<endl;
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
bool Department::addEmpToDep(Employee emp){
	auto i=find(this->EmpsOfDep.begin(), this->EmpsOfDep.end(), emp);//searching employees of department
		if(i == this->EmpsOfDep.end()){//if employee not found then add it
	        this->EmpsOfDep.push_back(emp);
	        cout<<"employee has successfully added in department"<<endl;
	        return true;
	}else if(i != this->EmpsOfDep.end()){// if found --employee is not added to department and the function will return with false value
		cout<<"employee already exists in department"<<endl;
		return false;
	}
}
void Department::addEmpToDep(Employee emp,Company *compObj){
	Department *dep=findDepartment(this,compObj);
	if(!(dep==nullptr)){
		if(dep->addEmpToDep(emp)){
			Employee* EmpPtr=findEmployeeInCompany(emp,compObj);
			if(EmpPtr==nullptr){
				compObj->EmpsOfAllCompany.push_back(emp);
				cout<<"employee added to company emp name: "<<emp.getName()<<endl;
				return;
			}else{
				cout<<"employee already found in EmpsOfAllCompany"<<endl;
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
void Department::RemoveSubDep(Department department){
     auto i=find(this->getSubDeps()->begin(), this->getSubDeps()->end(),department);
     if(i!=this->getSubDeps()->end()){
    	 this->getSubDeps()->erase(i);
   	     cout<<"Sub_department "<<department.DepName<<" removed successfully from"<<this->DepName<<endl;
   	     return;
     }else{
    	 cout<<"sub_department "<<department.DepName<<"dose not exists in "<<this->DepName<<endl;
    	 return;
     }
	}
void Department::RemoveSubDep(Department department,Company *compObj){
	Department *dep=findDepartment(this,compObj);
	if(!(dep==nullptr)){
		dep->RemoveSubDep(department);
		this->RemoveSubDep(department);
		return;
	}else{
		cout<<"Parent Department not found in Company"<<endl;
		return;
	}
}
void Department::addSubDep(Department dep){
	SubDeps.push_back(dep);
	cout<<"sub-department ("<<dep.getDepName()<< ")added successfully"<<endl;

}
void Department::addSubDep(Department department,Company *compObj){
	Department* dep=findDepartment(this,compObj);
	cout<<"in the add subDep :  "<<this->getDepName()<<endl;;
		if(dep!=nullptr){
			dep->addSubDep(department);
			this->addSubDep(department);
			return;
		}else{
			cout<<" Department not found in Company"<<endl;
			return;
		}
delete dep;
}
Department::~Department(){
}
bool Department::operator == (Department depObj) {
        if(depObj.getDepName() == this->getDepName()) {
        	return true;
        } else {
        	return false;
        }
    }
bool Department::operator == (string nameOfDep) {
        if(nameOfDep == this->getDepName()) {
        	return true;
        } else {
        	return false;
        }
    }
