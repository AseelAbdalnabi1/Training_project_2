/*
 * department.h
 *
 *  Created on: Sep 8, 2022
 *      Author: aseel
 */

#ifndef DEPARTMENT_H_
#define DEPARTMENT_H_

#include "stdbool.h"
#include "employee.h"
#include "company.h"
#include <vector>
#include <set>
class Employee;
class Company;
class Department{
private:
	std::string DepName;//unique value
	std::vector<Department> SubDeps={};
	std::vector<Employee> EmpsOfDep={};
	bool setDepName(std::string DepName);
	static std::set<std::string> NameOFDepartments;
public:
	Department(std::string DepName,std::vector<Department> SubDeps={},std::vector<Employee> EmpsOfDep={});
	std::vector <Employee> *getEmpsOfDep();
	std::vector <Employee> *getEmpsOfDep(Company *compObj);
	void setEmpsOfDep(std::vector <Employee> EmpsOfDep);
	void setEmpsOfDep(std::vector <Employee> EmpsOfDep,Company *compObj);
	bool isAnySubDeps();
	std::vector<Department>* getSubDeps();
	std::vector<Department>* getSubDeps(Company *compObj);
	void setSubDeps(std::vector<Department> SubDeps);
	void setSubDeps(std::vector<Department> SubDeps,Company *compObj);
	std::string getDepName();
    bool removeEmpFromDep(Employee emp);
    void removeEmpFromDep(Employee emp,Company *compObject);
    bool addEmpToDep(Employee emp);
    void addEmpToDep(Employee emp,Company *compObject);
    void RemoveSubDep(Department department);
    void RemoveSubDep(Department department,Company *compObj);
	void addSubDep(Department department);
	void addSubDep(Department department,Company *compObj);
	bool operator == (Department depObj);
	bool operator == (std::string nameOfDep);
	~Department();
};


#endif /* DEPARTMENT_H_ */
