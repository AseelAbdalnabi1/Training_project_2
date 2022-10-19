#include "../headers/hash.h"
#include <vector>
using namespace std;
class Employee;
class Company;
Hash::Hash(int BUCKET)
{
 this->BUCKET = BUCKET;
 table = new list<Employee>[this->BUCKET];
}

void Hash::insertItem(Employee Emp)
{
	int index = hashFunction(Emp.getSalary());//get the index to insert the employee in the hash table

	if(table[index].empty() || table[index].front().getSalary()==Emp.getSalary()){//if the cell of this index is empty -->insert the employee in it ,or if the cell has an inserted employee with the same salary-->inserted the employee
		table[index].push_back(Emp);
	}else{//else we search for a cell that is has employees with same salary if not found --> insert the cell in first encountered empty cell
		while(table[index].front().getSalary()!=Emp.getSalary()&& (!table[index].empty()) ){
			index+=1;
			if(index==(int)Company::EmpsOfAllCompany.size()){//while loop reaches the end of the hash
				index=0;//go to begining of hash
			}
		}
		table[index].push_back(Emp);
	}
	return;
 }
int Hash::hashFunction(int empSalary){
		return (empSalary%BUCKET);
}
vector<Employee> Hash::displayEmployeesWithSameSalary() {
	vector<Employee> EmployeesWithSameSalary_vector={};//this vector will contain employees with same salaries in company
	for (int i = 0; i < BUCKET; i++) {
		if(table[i].size()>1){//if there is a collision handling in this cell-->then it contains employees with same salary-->we add those employees to EmployeesWithSameSalary_vector and display them
			cout<<"Employees with same salary  are:-"<<endl;
			for(auto j=table[i].begin();j!=table[i].end();j++)
			{
				EmployeesWithSameSalary_vector.push_back((*j));//added for unit testing
				cout<<"Employee name , salary & ID: "<<(*j).getName()<<" | "<<	j->getSalary() <<" | "<<(*j).getEmpId()<<endl;
			}
		cout<<"-------------------------------------------------"<<endl;
		}
	}
	return EmployeesWithSameSalary_vector;
}






