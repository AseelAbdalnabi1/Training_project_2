/*
 * company.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: aseel
 */
#include "../headers/company.h"
#include <thread>
#include <algorithm>
#include <set>
#include <unordered_map>
using namespace std;

 Company * Company::companyObject;
 vector<Employee> Company::allEmployeesOfDepartmentsWithDuplicate  = {};//ALL EMPS FILLED BY A FUNCTION IN COMPANY-with duplication
 vector<Employee> Company::employeesOfAllCompany = {};
 int Company::flag=0;
 Department *Company::foundDepartment=nullptr;
Company::Company(){
	this->ceoEmployee=new Employee("Tareq",35,CEO,50000);
	employeesOfAllCompany.push_back(*ceoEmployee);
     cout<<"company created successfully!"<<endl;
}

Employee Company::getCeoEmployee(){
     return *ceoEmployee;
}
void Company::setCeoEmployee(Employee ceo_employee){
     this->ceoEmployee=&ceo_employee;
     employeesOfAllCompany[0]=ceo_employee;

}
vector<Department> *Company::getMainDepartments(){
     return &mainDepartments;
}
Department* Company::addMainDepartmentToCompany(Department department){
	cout<<department.getDepartmentName()<<endl;
	auto department_iterator=find(getMainDepartments()->begin(),getMainDepartments()->end(), department) ;
	if(department_iterator== getMainDepartments()->end()){
		mainDepartments.push_back(department);
		cout<<"Main-Department "<<department.getDepartmentName()<<" has added successfully!"<<endl;
	}else{
		cout<<department.getDepartmentName()<<" is already a main department !"<<endl;
		return &(*department_iterator);
	}
}
void Company::removeMainDepartmentFromCompany(Department department){
	auto department_iterator=find(getMainDepartments()->begin(),getMainDepartments()->end(), department);
	if(department_iterator != this->getMainDepartments()->end()){
		mainDepartments.erase(department_iterator);
          cout<<"Department : "<< department_iterator->getDepartmentName() <<" has bee deleted successfully"<<endl;
	 }else{
		 cout<<"Department with : "<< department.getDepartmentName() <<"  dose not exists in company"<<endl;
	     return;
	 }
}
void Company::removeMainDepartmentFromCompany(int department_id){
	auto department_iterator=find(getMainDepartments()->begin(),getMainDepartments()->end(), department_id);
	if(department_iterator != this->getMainDepartments()->end()){
		mainDepartments.erase(department_iterator);
          cout<<"Main_Department : "<<department_iterator->getDepartmentId() <<" has been deleted successfully"<<endl;
	 }else{
		 cout<<"Department with  id: "<<department_id<<"  is NOT a MAIN department of the company"<<endl;
	     return;
	 }
}
void Company::getAllEmployeesUsingThreads(Department department, vector<Employee> *employeesOfDepartments){
	allEmployeesOfDepartmentsWithDuplicate.insert(allEmployeesOfDepartmentsWithDuplicate.end(), department.getEmployeesOfDepartment()->begin(),department.getEmployeesOfDepartment()->end() );//allowing duplicating) for further use in employees of multiple departments API
     for(auto it =department.getEmployeesOfDepartment()->begin();it !=department.getEmployeesOfDepartment()->end();it++){
    	 if(find(employeesOfDepartments->begin(),employeesOfDepartments->end(),(*it))==employeesOfDepartments->end()){//Checking of this employee is already in empsOfDeps--if found don't add it
    		 employeesOfDepartments->push_back((*it));//if not found --> add it
    	 }
     }
    if(department.isAnySubDeps()==1){//checking if department has sub department or not ---if it has,it calls allEmpsFun function on each sub department of that department
    	for(auto f=department.getSubDepartments()->begin();f!=department.getSubDepartments()->end();f++){
    		getAllEmployeesUsingThreads((*f),employeesOfDepartments);
    	}
    }
    else{
       return ;
    }
}
vector<Employee> Company::getAllEmployees(){
	allEmployeesOfDepartmentsWithDuplicate.clear();// a vector of employees in departments (allowing duplicating) for further use in employees of multiple departments API
    vector<Employee> employeesOfDepartments={};
	int size=(int) mainDepartments.size();
    for(int i=0;i<size;i++){
    	 thread th(getAllEmployeesUsingThreads,mainDepartments.at(i),&employeesOfDepartments);
    	 th.join();
    }
    return employeesOfDepartments;
}
int Company::getEmployeesWithSameSalary(){
	int numberOfEmploeesWithSameSalaries=0;//number of all the employees getting the same salaries all together
	unordered_map<int, int> sameSalayMap;//unordered_map to store <salary,number of employees getting this salary>
	for(auto i=employeesOfAllCompany.begin();i!=employeesOfAllCompany.end();i++){//loop through the employees in company to fill the unordered_map
		sameSalayMap[i->getSalary()]++;
	}
    for (auto i = sameSalayMap.begin(); i != sameSalayMap.end(); i++){//loop to print the salaries taken by multiple employees and the number of employees getting this salary
    	if(i->second>1){
		 cout << i->first << "   :   " << i->second<< endl;
		 numberOfEmploeesWithSameSalaries+=i->second;
    	}
    }
	return numberOfEmploeesWithSameSalaries;
}
void Company::addEmployeeToCompany(Employee emp){//employees who are in company but not in department
	auto i=find(this->employeesOfAllCompany.begin(), this->employeesOfAllCompany.end(), emp);
	if(i != this->employeesOfAllCompany.end()){
		cout<<"employee already exists in Company"<<endl;
		return;
	}else{
		this->employeesOfAllCompany.push_back(emp);
		cout<<"Employee added successfully to the Company!"<<endl;
		return;
	}
}
void Company::removeEmployeeFromCompany(Employee emp){//employees who are in company but not in department
	auto i=find(this->employeesOfAllCompany.begin(), this->employeesOfAllCompany.end(), emp);
	if(i != this->employeesOfAllCompany.end()){
		this->employeesOfAllCompany.erase(i);
	}
	else{
		cout<<"employee with empID number: "<<emp.getEmployeeId()<<" is not part of the company"<<endl;
	}
}
vector<Employee> Company::getEmployeesOfMultipleDepartments(){ //finding employees of multiple departments
	getAllEmployees();
	vector<Employee> employeesOfMultiDepartmentsResults={};//vector to store the employees of multiple departments
	set<int> SetOfEmployees;//set of employees in department without Repetition
	for(auto i=allEmployeesOfDepartmentsWithDuplicate.begin();i!=allEmployeesOfDepartmentsWithDuplicate.end();i++){//getting employees of department (with multiplication)
		if(SetOfEmployees.count((*i).getEmployeeId())==0){// if not found in setOfEmps add it in SetOfEmps
			SetOfEmployees.insert((*i).getEmployeeId());
		}else{//if found -then it is an employee of multiDep--we add it to empsOfMultiDeps_Results
			employeesOfMultiDepartmentsResults.push_back((*i));
		}
	}
	cout<<"Employees of multi-Departments : "<<endl;//printing Employees of multi-Departments
	for(auto i=employeesOfMultiDepartmentsResults.begin();i!=employeesOfMultiDepartmentsResults.end();i++){
		cout<<"Employee name & ID : "<<	i->getName()<<"  |  "<<i->getEmployeeId()<<endl;;
	}
	return employeesOfMultiDepartmentsResults;
}
bool Company::isThereAnyLoopsInDepartments(){//returns true if we have a department has two parent departments
	set<string> childrenOfDepartments={};
	bool result;//to return the result
	for(auto it1=this->getMainDepartments()->begin();it1!=this->getMainDepartments()->end();it1++){//searching in Main Departments of the company
		for(auto it2=(*it1).getSubDepartments()->begin();it2!=(*it1).getSubDepartments()->end();it2++){//children of main deps
			if(childrenOfDepartments.find((*it2).getDepartmentName())==childrenOfDepartments.end()){//if department is already in ChildsOfDeps then returns true --if not add it to ChildsOfDeps
				childrenOfDepartments.insert((*it2).getDepartmentName());
			}else{
				return true;
			}
			if((*it2).isAnySubDeps()==1){ //checking if department has subDepartments ---if yes we call loop_IN_Deps_hand on that department
				result=isThereAnyLoopsInDepartmentsHand((*it2),&childrenOfDepartments);
				if(result==1){
					return true;
				}
			}

		}
	}
	return false;
}
bool Company::isThereAnyLoopsInDepartmentsHand(Department parent_department ,set<string> *childrenOfDepartments){//recursion function to search for loops in subDepartments
	bool result;
	for(auto it1=parent_department.getSubDepartments()->begin();it1!=parent_department.getSubDepartments()->end();it1++){
		if(childrenOfDepartments->count((*it1).getDepartmentName())==0){
			childrenOfDepartments->insert((*it1).getDepartmentName());
		}else{
			return true;//child already exists
		}
		if((*it1).isAnySubDeps()==1){
			result=isThereAnyLoopsInDepartmentsHand((*it1),childrenOfDepartments);
			if(result==1){
				return true;
			}
		}
	}
	return false;
}
vector<Employee> Company::getfloatingEmployees(){
	vector<Employee> floatingEmployees={};// clearing vector<Empolyee> floatingEmployees
	vector<Employee> all_employees_of_departments=getAllEmployees();//getting Employees of all departments
	for(auto i=employeesOfAllCompany.begin(); i!=employeesOfAllCompany.end();i++){//loop in employeesOfAllCompany (contains employees of departments and employees with no department)
		if(find(all_employees_of_departments.begin(),all_employees_of_departments.end(),(*i))==all_employees_of_departments.end()){//cheacking if employee in employeesOfAllCompany is also an employee in  department --if no
			if((*i).getRole(this)!="CEO"){//if this employee(with no department) is NOT the CEO then add it to listOfFloatingEmps
				floatingEmployees.push_back((*i));
			}
		}
	}
	if(!floatingEmployees.empty()){//printing the floating employees of company
		cout<<"-----------------------------------------------------------------------"<<endl;
		cout<<"Floating employees in company are: "<<endl;
		for(auto i=floatingEmployees.begin();i!=floatingEmployees.end();i++){
			cout<<"Employee name : "<<(*i).getName()<<"  |  Employee ID : "<<(*i).getEmployeeId()<<endl;
		}
		cout<<"-----------------------------------------------------------------------"<<endl;
		return floatingEmployees;
	}
	cout<<"Company doesn't have any floating employees "<<endl;
	return {};
}

Department * Company::findDepartment(Department *needed_department){
	foundDepartment=nullptr;
	flag=0;//department not found
	int size=(int) this->getMainDepartments()->size();
	    for(int i=0;i<size;i++){
	    	Company::findDepartmenthand(needed_department,&(this->getMainDepartments()->at(i)),flag);
	    	if(foundDepartment!=nullptr && flag==1){
	    		return foundDepartment;
	    		break;
	    	}else if(foundDepartment==nullptr && flag==0){
	    		continue;
	    	}
	    }
	    return nullptr;
}
Department *Company::findDepartmenthand(Department *needed_department,Department *parent_department,int &flag){
	if (flag==1){
		return foundDepartment;
	}
	if((*needed_department)==(*parent_department)){
		flag=1;
		foundDepartment = parent_department;
		return foundDepartment;
	}if(flag==0){
	if(parent_department->isAnySubDeps()==1){
	    	for(auto f=parent_department->getSubDepartments()->begin();f!=parent_department->getSubDepartments()->end();f++){
	    		Company::findDepartmenthand(needed_department,&(*f),flag);
	    	}
	  }
	return nullptr;
	}


}
Employee * Company::findEmployeeInDepartment(Employee needed_employee,vector<Department>* range_of_departments){//for hirarichy
	for( auto it1=range_of_departments->begin();it1!=range_of_departments->end();it1++){
		auto it2=find((*it1).getEmployeesOfDepartment()->begin(),(*it1).getEmployeesOfDepartment()->end(),needed_employee);
		if(it2 != (*it1).getEmployeesOfDepartment()->end()){
			return &(*it2);
		}
		return findEmployeeInDepartment(needed_employee,(*it1).getSubDepartments());//for hirarichy
	}
}


Employee *Company::findEmployeeInCompany(Employee employee){
	auto i=find(this->employeesOfAllCompany.begin(),this->employeesOfAllCompany.end(),employee);
	if(i != this->employeesOfAllCompany.end()){
		cout<<"employee found in employeesOfAllCompany"<<endl;
		return &(*i);
	}
	else{
		cout<<"employee not found in company"<<endl;
		return nullptr;
	}
}



