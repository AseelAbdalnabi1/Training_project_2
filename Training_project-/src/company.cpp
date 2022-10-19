/*
 * company.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: aseel
 */
#include "../headers/company.h"
#include "../headers/hash.h"
#include <thread>
#include <algorithm>
#include <set>
using namespace std;

 Company * Company::compObject;
 vector<Employee> Company::allEmpsOfDepartments  = {};//ALL EMPS FILLED BY A FUNCTION IN COMPANY-with duplication
 vector<Employee> Company::EmpsOfAllCompany = {};
 set<string> Company::ChildsOfDeps={};
 vector<Employee> Company::listOfFloatingEmps={};
 vector<Employee> Company::empsOfMultiDeps_Results={};
 vector<Employee> Company::empsOfDeps={};//all employees in company without multiplication
Company::Company(){
	this->CeoEmp=new Employee("Tareq",35,CEO,50000);
	 EmpsOfAllCompany.push_back(*CeoEmp);
     cout<<"company created successfully!"<<endl;
}

Employee Company::getCeoEmp(){
     return *CeoEmp;
}
void Company::setCeoEmp(Employee CeoEmp){
     this->CeoEmp=&CeoEmp;
     EmpsOfAllCompany[0]=CeoEmp;

}
void Company::setMainDeps(vector<Department> MainDeps){
     this->MainDeps=MainDeps;
}
vector<Department> *Company::getMainDeps(){
     return &MainDeps;
}
void Company::addMainDepToCompany(Department dep){
	if(find(getMainDeps()->begin(),getMainDeps()->end(), dep) == getMainDeps()->end()){
		MainDeps.push_back(dep);
		cout<<"Main-Department "<<dep.getDepName()<<" has added successfully!"<<endl;
	}else{
		cout<<dep.getDepName()<<" is already a main department !"<<endl;
	}
}

void Company::removeMainDepFromCompany(Department dep){
	auto i=find(getMainDeps()->begin(),getMainDeps()->end(), dep);
	if(i != this->getMainDeps()->end()){
		  MainDeps.erase(i);
          cout<<"department has bee deleted successfully"<<endl;
	 }else{
		 cout<<"Department with  "<< dep.getDepName() <<"  dose not exists in company"<<endl;
	     return;
	 }
}
void Company::removeMainDepFromCompany(string depName){
	auto i=find(getMainDeps()->begin(),getMainDeps()->end(), depName);
	if(i != this->getMainDeps()->end()){
		  MainDeps.erase(i);
          cout<<"Main_Department has been deleted successfully"<<endl;
	 }else{
		 cout<<"Department with  "<<depName<<"  is NOT a MAIN department of the company"<<endl;
	     return;
	 }
}

void allEmpsFun(Department dep,Company *obj ){
     obj->allEmpsOfDepartments.insert(obj->allEmpsOfDepartments.end(), dep.getEmpsOfDep()->begin(),dep.getEmpsOfDep()->end() );//allowing duplicating) for further use in employees of multiple departments API
     for(auto it =dep.getEmpsOfDep()->begin();it !=dep.getEmpsOfDep()->end();it++){
    	 if(find(obj->empsOfDeps.begin(),obj->empsOfDeps.end(),(*it))==obj->empsOfDeps.end()){//Checking of this employee is already in empsOfDeps--if found don't add it
    		 obj->empsOfDeps.push_back((*it));//if not found --> add it
    	 }
     }
    if(dep.isAnySubDeps()==1){//checking if department has sub department or not ---if it has,it calls allEmpsFun function on each sub department of that department
    	for(auto f=dep.getSubDeps()->begin();f!=dep.getSubDeps()->end();f++){
         allEmpsFun((*f),obj);
    	}
    }
    else{
       return ;
    }
}
vector<Employee> Company::allEmployees(){
	allEmpsOfDepartments.clear();// a vector of employees in departments (allowing duplicating) for further use in employees of multiple departments API
	empsOfDeps.clear();// a vector of employees in departments(without allowing duplicating)
    int size=(int) MainDeps.size();
    for(int i=0;i<size;i++){
    	 thread th(allEmpsFun,MainDeps.at(i),this);//a thread for each Main Department in company
    	 th.join();
    }
    return this->empsOfDeps;
}

vector<Employee> Company::empsWithSameSalary(){//API to find employees with same salaries
	if(EmpsOfAllCompany.size()!=0){//checking if we have any employees in company
		   Hash hashForEmpsWithSameSalary(EmpsOfAllCompany.size());//creating a hash table with the same size as employees of company
		   for(auto i=EmpsOfAllCompany.begin();i!=EmpsOfAllCompany.end();i++){//loop through out the employees of company and inserting them into the hash table
			   hashForEmpsWithSameSalary.insertItem((*i));
		   }
		   return hashForEmpsWithSameSalary.displayEmployeesWithSameSalary();//returning a vector of Employees with same salary and displaying them

	}else{
		cout<<"Company has NO employees "<<endl;
		return {};
	}
}

void Company::addEmpToCompany(Employee emp){//employees who are in company but not in department
	auto i=find(this->EmpsOfAllCompany.begin(), this->EmpsOfAllCompany.end(), emp);
	if(i != this->EmpsOfAllCompany.end()){
		cout<<"employee already exists in Company"<<endl;
		return;
	}else{
		this->EmpsOfAllCompany.push_back(emp);
		cout<<"Employee added successfully to the Company!"<<endl;
		return;
	}
}
void Company::removeEmpFromCompany(Employee emp){//employees who are in company but not in department
	auto i=find(this->EmpsOfAllCompany.begin(), this->EmpsOfAllCompany.end(), emp);
	if(i != this->EmpsOfAllCompany.end()){
		this->EmpsOfAllCompany.erase(i);
	}
	else{
		cout<<"employee with empID number: "<<emp.getEmpId()<<" is not part of the company"<<endl;
	}
}
vector<Employee> Company::empsOfMultiDeps(){ //finding employees of multiple departments
	allEmployees();
	vector<Employee>  EmpsOfDeps=this->allEmpsOfDepartments;//getting employees of department (with multiplication)
	 empsOfMultiDeps_Results={};//vector to store the employees of multiple departments
	set<int> SetOfEmps;//set of employees in department without Repetition
	for(auto i=EmpsOfDeps.begin();i!=EmpsOfDeps.end();i++){
		if(SetOfEmps.find((*i).getEmpId())==SetOfEmps.end()){// if not found in setOfEmps add it in SetOfEmps
			SetOfEmps.insert((*i).getEmpId());
		}else{//if found -then it is an employee of multiDep--we add it to empsOfMultiDeps_Results
			empsOfMultiDeps_Results.push_back((*i));
		}
	}
	cout<<"Employees of multi-Departments : "<<endl;//printing Employees of multi-Departments
	for(auto i=empsOfMultiDeps_Results.begin();i!=empsOfMultiDeps_Results.end();i++){
		cout<<"Employee name & ID : "<<	i->getName()<<"  |  "<<i->getEmpId()<<endl;;
	}
	return empsOfMultiDeps_Results;
}
bool Company::loop_IN_Deps(){//returns true if we have a department has two parent departments
	ChildsOfDeps={}; //clear set<string> ChildsOfDeps since it is a static
	bool result;//to return the result
	for(auto it1=this->getMainDeps()->begin();it1!=this->getMainDeps()->end();it1++){//searching in Main Departments of the company
		for(auto it2=(*it1).getSubDeps()->begin();it2!=(*it1).getSubDeps()->end();it2++){//children of main deps
			if(ChildsOfDeps.find((*it2).getDepName())==ChildsOfDeps.end()){//if department is already in ChildsOfDeps then returns true --if not add it to ChildsOfDeps
				ChildsOfDeps.insert((*it2).getDepName());
			}else{
				return true;
			}
			if((*it2).isAnySubDeps()==1){ //checking if department has subDepartments ---if yes we call loop_IN_Deps_hand on that department
				result=loop_IN_Deps_hand((*it2));
				if(result==1){
					return true;
				}
			}

		}
	}
	return false;
}
bool Company::loop_IN_Deps_hand(Department 	ParentDep){//recursion function to search for loops in subDepartments
	bool result;
	for(auto it1=ParentDep.getSubDeps()->begin();it1!=ParentDep.getSubDeps()->end();it1++){
		if(ChildsOfDeps.find((*it1).getDepName())==ChildsOfDeps.end()){
				ChildsOfDeps.insert((*it1).getDepName());
		}else{
			return true;//child already exists
		}
		if((*it1).isAnySubDeps()==1){
			result=loop_IN_Deps_hand((*it1));
			if(result==1){
				return true;
			}
		}
	}
	return false;
}
bool Company::floatingEmps(){
	 listOfFloatingEmps={};// clearing vector<Empolyee> listOfFloatingEmps since it is static data member
	vector<Employee> AllEmpsOfDeps=allEmployees();//getting Employees of all departments
	for(auto i=EmpsOfAllCompany.begin(); i!=EmpsOfAllCompany.end();i++){//loop in EmpsOfAllCompany (contains employees of departments and employees with no department)
		if(find(AllEmpsOfDeps.begin(),AllEmpsOfDeps.end(),(*i))==AllEmpsOfDeps.end()){//cheacking if employee in EmpsOfAllCompany is also an employee in  department --if no
			if((*i).getRole(this)!="CEO"){//if this employee(with no department) is NOT the CEO then add it to listOfFloatingEmps
				listOfFloatingEmps.push_back((*i));
			}
		}
	}
	if(!listOfFloatingEmps.empty()){//printing the floating employees of company
		cout<<"-----------------------------------------------------------------------"<<endl;
		cout<<"Floating employees in company are: "<<endl;
		for(auto i=listOfFloatingEmps.begin();i!=listOfFloatingEmps.end();i++){
			cout<<"Employee name : "<<(*i).getName()<<"  |  Employee ID : "<<(*i).getEmpId()<<endl;
		}
		cout<<"-----------------------------------------------------------------------"<<endl;
		return true;
	}
	cout<<"Company doesn't have any floating employees "<<endl;
	return false;
}
Company::~Company(){
	cout<<"Company has deleted successfully, in Company destructor"<<endl;
}



