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

 Company * Company::companyObject;//private and static company object
 vector<Employee> Company::allEmployeesOfDepartmentsWithDuplicate  = {};//all employees of departments-with duplication ---for further use in employees of multiple departments API
 vector<Employee> Company::employeesOfAllCompany = {};//vector of all employees in company (belongs to department and floating )
 int Company::flag=0;//static flag for further use in recursion in (find department)
 Department *Company::foundDepartment=nullptr;//static pointer to department for further use in recursion in (find department)
Company::Company(){//private constructor
	this->ceoEmployee=new Employee("Tareq",35,CEO,50000);//creates the ceo
	employeesOfAllCompany.push_back(*ceoEmployee);//push the ceo in the vector employeesOfAllCompany
     cout<<"company created successfully!"<<endl;
}

Employee Company::getCeoEmployee(){//returns the ceo
     return *ceoEmployee;
}
void Company::setCeoEmployee(Employee ceo_employee){//set the ceo
     this->ceoEmployee=&ceo_employee;
     employeesOfAllCompany[0]=ceo_employee;

}
vector<Department> *Company::getMainDepartments(){//returns the main departments vector of the company
     return &mainDepartments;
}
Department* Company::addMainDepartmentToCompany(Department department){// add a main department to company
	auto department_iterator=find(getMainDepartments()->begin(),getMainDepartments()->end(), department) ;//checks if the required department is already a main department in company or not by finding the iterator
	if(department_iterator== getMainDepartments()->end()){//if the department is not a main department , then add it to main departments of company
		mainDepartments.push_back(department);
		cout<<"Main-Department "<<department.getDepartmentName()<<" has added successfully!"<<endl;
	}else{//if the department is already a main department then returns the pointer to the found main department
		cout<<department.getDepartmentName()<<" is already a main department !"<<endl;
		return &(*department_iterator);
	}
}
void Company::removeMainDepartmentFromCompany(Department department){//remove a main department from the company
	auto department_iterator=find(getMainDepartments()->begin(),getMainDepartments()->end(), department);//checks if the required department is already a main department in company or not by finding the iterator
	if(department_iterator != this->getMainDepartments()->end()){//if the department is already a main department , then remove it from main departments of company
		mainDepartments.erase(department_iterator);
          cout<<"Department : "<< department_iterator->getDepartmentName() <<" has bee deleted successfully"<<endl;
	 }else{//if not found then return
		 cout<<"Department with : "<< department.getDepartmentName() <<"  dose not exists in company"<<endl;
	     return;
	 }
}
void Company::removeMainDepartmentFromCompany(int department_id){//to remove a main department from the company using the department_id
	auto department_iterator=find(getMainDepartments()->begin(),getMainDepartments()->end(), department_id);//checks if the required department is already a main department in company or not by finding the iterator
	if(department_iterator != this->getMainDepartments()->end()){//if department found in the main department ,then delete it
		mainDepartments.erase(department_iterator);
          cout<<"Main_Department : "<<department_iterator->getDepartmentId() <<" has been deleted successfully"<<endl;
	 }else{//if not found then return
		 cout<<"Department with  id: "<<department_id<<"  is NOT a MAIN department of the company"<<endl;
	     return;
	 }
}
void Company::getAllEmployeesUsingThreads(Department department, vector<Employee> *employeesOfDepartments){
	allEmployeesOfDepartmentsWithDuplicate.insert(allEmployeesOfDepartmentsWithDuplicate.end(), department.getEmployeesOfDepartment()->begin(),department.getEmployeesOfDepartment()->end() );//inserting the employees of each department---- allowing duplicating) for further use in employees of multiple departments API
     for(auto it =department.getEmployeesOfDepartment()->begin();it !=department.getEmployeesOfDepartment()->end();it++){//looping the employees of department
    	 if(find(employeesOfDepartments->begin(),employeesOfDepartments->end(),(*it))==employeesOfDepartments->end()){//Checking of this employee is already in employeesOfDepartments--if found don't add it-- to avoid repetition
    		 employeesOfDepartments->push_back((*it));//if not found --> add  it to employeesOfDepartments
    	 }
     }
    if(department.isAnySubDepartments()==1){//checking if department has sub department or not ---if it has,it calls getAllEmployeesUsingThreads function on each sub department of that department
    	for(auto f=department.getSubDepartments()->begin();f!=department.getSubDepartments()->end();f++){
    		getAllEmployeesUsingThreads((*f),employeesOfDepartments);
    	}
    }
    else{
       return ;
    }
}
vector<Employee> Company::getAllEmployees(){//an API to find and return a vector of all the employees belong to departments in company
	allEmployeesOfDepartmentsWithDuplicate.clear();// a vector of employees in departments (allowing duplicating) for further use in employees of multiple departments API
    vector<Employee> employeesOfDepartments={};//initializing a vector of employees to store the result(employees of departments) of the function
	int size=(int) mainDepartments.size();//finding the number of main departments in the company
    for(int i=0;i<size;i++){//find the employees of each main department using a a thread (a thread for each main depaartment using the getAllEmployeesUsingThreads function
    	 thread th(getAllEmployeesUsingThreads,mainDepartments.at(i),&employeesOfDepartments);
    	 th.join();//wait the thread to finish
    }
    return employeesOfDepartments;//return the resulted vector of employees
}
int Company::getEmployeesWithSameSalary(){//returns the number of all the employees getting the same salaries all together
	int numberOfEmploeesWithSameSalaries=0;//number of all the employees getting the same salaries all together
	unordered_map<int, int> sameSalaryMap;//unordered_map to store <salary,number of employees getting this salary>
	for(auto i=employeesOfAllCompany.begin();i!=employeesOfAllCompany.end();i++){//loop through the employees in company to fill the unordered_map
		sameSalaryMap[i->getSalary()]++;
	}
    for (auto i = sameSalaryMap.begin(); i != sameSalaryMap.end(); i++){//loop to print the salaries taken by multiple employees and the number of employees getting this salary
    	if(i->second>1){
		 cout << i->first << "   :   " << i->second<< endl;
		 numberOfEmploeesWithSameSalaries+=i->second;
    	}
    }
	return numberOfEmploeesWithSameSalaries;
}
void Company::addEmployeeToCompany(Employee employee){//to add an employee to company without adding him to department(a floating employee)
	auto i=find(this->employeesOfAllCompany.begin(), this->employeesOfAllCompany.end(), employee);//checks if the required employee is already in the company
	if(i != this->employeesOfAllCompany.end()){//if the employee is found then return
		cout<<"employee already exists in Company"<<endl;
	}else{// if the employee is not found then add the required employee to employeesOfAllCompany
		this->employeesOfAllCompany.push_back(employee);
		cout<<"Employee added successfully to the Company!"<<endl;
	}
	return;
}
void Company::removeEmployeeFromCompany(Employee employee){//to remove employee from the employeesOfAllCompany vector
	auto i=find(this->employeesOfAllCompany.begin(), this->employeesOfAllCompany.end(), employee);//checks if the required employee is already in the company
	if(i != this->employeesOfAllCompany.end()){//if the employee is found then delete him from employeesOfAllCompany
		this->employeesOfAllCompany.erase(i);
	}
	else{//if not found don't delete anything
		cout<<"employee with empID number: "<<employee.getEmployeeId()<<" is not part of the company"<<endl;
	}
	return;
}
vector<Employee> Company::getEmployeesOfMultipleDepartments(){ //finding employees of multiple departments
	getAllEmployees();//calling the getAllEmployees API in order to fill the allEmployeesOfDepartmentsWithDuplicate vector
	vector<Employee> employeesOfMultiDepartmentsResults={};//vector to store the employees of multiple departments(the result of this function)
	set<int> SetOfEmployees;//set of employees in department without Repetition
	for(auto i=allEmployeesOfDepartmentsWithDuplicate.begin();i!=allEmployeesOfDepartmentsWithDuplicate.end();i++){//looping in employees of departments (with multiplication)
		if(SetOfEmployees.count((*i).getEmployeeId())==0){//if the employee is not found in SetOfEmployees, then add it in SetOfEmployees
			SetOfEmployees.insert((*i).getEmployeeId());
		}else{//if employee is found in the set ,then this employee belongs to more than one department. so,we add it to employeesOfMultiDepartmentsResults
			employeesOfMultiDepartmentsResults.push_back((*i));
		}
	}
	cout<<"Employees of multi-Departments : "<<endl;//printing Employees of multiple-Departments
	for(auto i=employeesOfMultiDepartmentsResults.begin();i!=employeesOfMultiDepartmentsResults.end();i++){
		cout<<"Employee name & ID : "<<	i->getName()<<"  |  "<<i->getEmployeeId()<<endl;;
	}
	return employeesOfMultiDepartmentsResults;//returning the employees of multiple departments
}
bool Company::isThereAnyLoopsInDepartments(){//returns true if we have a department has more than one parent department
	set<int> childrenOfDepartments={};//set of children of department IDs
	bool result;//to return the result
	for(auto it1=this->getMainDepartments()->begin();it1!=this->getMainDepartments()->end();it1++){//searching (looping)in Main Departments of the company
		for(auto it2=(*it1).getSubDepartments()->begin();it2!=(*it1).getSubDepartments()->end();it2++){//looping in the children of main departments
			if(childrenOfDepartments.count((*it2).getDepartmentId())==0){//if a child department is already in childrenOfDepartments set  then returns true --if not add it to childrenOfDepartments set
				childrenOfDepartments.insert((*it2).getDepartmentId());
			}else{
				return true;
			}
			if((*it2).isAnySubDepartments()==1){ //checking if parent department has subDepartments ---if yes we call isThereAnyLoopsInDepartmentsHand on the parent department
				result=isThereAnyLoopsInDepartmentsHand((*it2),&childrenOfDepartments);
				if(result==1){//if the result after recursion is 1 then true is returned and the function ends
					return true;
				}
			}

		}
	}
	return false;
}
bool Company::isThereAnyLoopsInDepartmentsHand(Department parent_department ,set<int> *childrenOfDepartments){//recursion function to search for loops in subDepartments
	bool result;
	for(auto it1=parent_department.getSubDepartments()->begin();it1!=parent_department.getSubDepartments()->end();it1++){//looping in the subdepartments to see if their is a sub department which a sub department of another parent
		if(childrenOfDepartments->count((*it1).getDepartmentId())==0){//if the sub department id is not in the  childrenOfDepartments set , then add it to childrenOfDepartments set
			childrenOfDepartments->insert((*it1).getDepartmentId());
		}else{//if the sub department id is already in the  childrenOfDepartments set , then there is a loop in the company so it returns true
			return true;
		}
		if((*it1).isAnySubDepartments()==1){//check if the sub department have any sub-deaprtments
			result=isThereAnyLoopsInDepartmentsHand((*it1),childrenOfDepartments);//if yes then call isThereAnyLoopsInDepartmentsHand for the parent department
			if(result==1){
				return true;
			}
		}
	}
	return false;//if the hierarchy of the company ends without any looping ,then return false
}
vector<Employee> Company::getfloatingEmployees(){//returns a vector of employees who belong to the company but not to any department
	vector<Employee> floatingEmployees={};// Initializing vector<Empolyee> floatingEmployees to store the returned result
	vector<Employee> all_employees_of_departments=getAllEmployees();//getting Employees of all departments
	for(auto i=employeesOfAllCompany.begin(); i!=employeesOfAllCompany.end();i++){//loop in employeesOfAllCompany (contains employees of departments and employees with no department)
		if(find(all_employees_of_departments.begin(),all_employees_of_departments.end(),(*i))==all_employees_of_departments.end()){//cheacking if employee in employeesOfAllCompany is also an employee in a department --if no
			if((*i).getRole(this)!="CEO"){//if this employee(with no department) is NOT the CEO then add it to floatingEmployees
				floatingEmployees.push_back((*i));
			}
		}
	}
	if(!floatingEmployees.empty()){//if there is any floating employees then print them
		cout<<"-----------------------------------------------------------------------"<<endl;
		cout<<"Floating employees in company are: "<<endl;
		for(auto i=floatingEmployees.begin();i!=floatingEmployees.end();i++){
			cout<<"Employee name : "<<(*i).getName()<<"  |  Employee ID : "<<(*i).getEmployeeId()<<endl;
		}
		cout<<"-----------------------------------------------------------------------"<<endl;
		return floatingEmployees;//returning the vector of the floating employees
	}
	cout<<"Company doesn't have any floating employees "<<endl;
	return {};//if there is no floating employees in the company then return an empty vector
}

Department * Company::findDepartment(Department *needed_department){//checks if a department is in the company. if found then returns a pointer to that department
	foundDepartment=nullptr;//a variable to store the department if found
	flag=0;//flag to ensure that the department is found (1) or not found (0)
	int size=(int) this->getMainDepartments()->size();//variable to get the number of main departments in company
	    for(int i=0;i<size;i++){//looping between the main departments
	    	Company::findDepartmenthand(needed_department,&(this->getMainDepartments()->at(i)),flag);
	    	if(foundDepartment!=nullptr && flag==1){//if department found then returns a pointer to it and break the loop
	    		return foundDepartment;
	    		break;
	    	}else if(foundDepartment==nullptr && flag==0){ //if not found then continue
	    		continue;
	    	}
	    }
	    return nullptr;
}
Department *Company::findDepartmenthand(Department *needed_department,Department *parent_department,int &flag){//recursion function to find a required department in a sub-department (in company)
	if (flag==1){//if department is already found then return a pointer to it
		return foundDepartment;
	}
	if((*needed_department)==(*parent_department)){//if required department is the parent department then,
		flag=1;//flag will be 1
		foundDepartment = parent_department;//foundDepartment will be parent_department
		return foundDepartment; //returns the found department
	}if((flag==0) && (parent_department->isAnySubDepartments()==1)){//if department not found ,it will search in the sub department of the parent using recursion
	    	for(auto f=parent_department->getSubDepartments()->begin();f!=parent_department->getSubDepartments()->end();f++){
	    		Company::findDepartmenthand(needed_department,&(*f),flag);
	    	}
	return nullptr;
	}
}

Employee * Company::findEmployeeInDepartment(Employee needed_employee,vector<Department>* range_of_departments){//recursion function to check if an employee belongs to a department of the company, then returns a pointer to the found employee
	for( auto it1=range_of_departments->begin();it1!=range_of_departments->end();it1++){//looping in a level of the hierarchy of comopany's department(first-the main department,second is the sup department of the first main department...and so on )
		auto it2=find((*it1).getEmployeesOfDepartment()->begin(),(*it1).getEmployeesOfDepartment()->end(),needed_employee);//trying to find the employee in a specified department of the loop
		if(it2 != (*it1).getEmployeesOfDepartment()->end()){//if found then returns a pointer to the found employees
			return &(*it2);
		}
		return findEmployeeInDepartment(needed_employee,(*it1).getSubDepartments());//if not found in the department , then call findEmployeeInDepartment on the sub-department of this department
	}
}


Employee *Company::findEmployeeInCompany(Employee employee){//to find an employee in employeesOfAllCompany vector
	auto i=find(this->employeesOfAllCompany.begin(),this->employeesOfAllCompany.end(),employee);//search for the employee in employeesOfAllCompany vector
	if(i != this->employeesOfAllCompany.end()){//if found return the pointer to the required employee in employeesOfAllCompany vector
		cout<<"employee found in employeesOfAllCompany"<<endl;
		return &(*i);
	}
	else{//if not found return nullptr
		cout<<"employee not found in company"<<endl;
		return nullptr;
	}
}



