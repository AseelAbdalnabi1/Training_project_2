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
	std::string departmentName;//unique value
	std::vector<Department> subDepartments={};
	std::vector<Employee> employeesOfDepartment={};
	static std::set<std::string> nameOFDepartments;
	bool setDepartmentName(std::string department_name);
public:
	Department(std::string departmentName);//,std::vector<Department> subDepartments={},std::vector<Employee> employeesOfDepartment={});
	std::vector <Employee> *getEmployeesOfDepartment();
	std::vector <Employee> *getEmployeesOfDepartment(Company *company_object);
	bool isAnySubDeps();
	std::vector<Department>* getSubDepartments();
	std::vector<Department>* getSubDepartments(Company *company_object);
	std::string getDepartmentName();
    bool removeEmployeeFromDepartment(Employee employee);
    void removeEmployeeFromDepartment(Employee employee,Company *company_objectect);
    bool addEmployeeToDepartment(Employee employee);
    void addEmployeeToDepartment(Employee employee,Company *company_objectect);
    void RemoveSubDepartment(Department department);
    void RemoveSubDepartment(Department department,Company *company_object);
	void addSubDepartment(Department department);
	void addSubDepartment(Department department,Company *company_object);
	bool operator == (Department department_object);
	bool operator == (std::string name_of_department);
	~Department();
};


#endif /* DEPARTMENT_H_ */
