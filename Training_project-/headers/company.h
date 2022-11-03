/*
 * company.h
 *
 *  Created on: Sep 8, 2022
 *      Author: aseel
 */

#ifndef COMPANY_H_
#define COMPANY_H_
#include "department.h"
#include "employee.h"
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
class Employee;
class Department;

class Company {
private:
    Employee *ceoEmployee=NULL;
    std::vector<Department> mainDepartments;
    static Company *companyObject;
    //static std::set<std::string> childrenOfDepartments;
    Company();
    ~Company();
public:
    static int flag;
    static Department *foundDepartment;
    static std::vector<Employee> employeesOfAllCompany;//all employees in company(regardless if they are in deps or not)
    static std::vector<Employee> allEmployeesOfDepartmentsWithDuplicate;//employees in Deps in company
    static Company *getCompanyObject(){
    	if(!(companyObject))
    		companyObject=new Company;
    	return companyObject;
    }
    Employee getCeoEmployee();
    void setCeoEmployee(Employee ceo_employee);
    std::vector<Department>* getMainDepartments();
    Department* addMainDepartmentToCompany(Department department);
    void removeMainDepartmentFromCompany(Department department);
    void removeMainDepartmentFromCompany(std::string department_name);
    void addEmployeeToCompany(Employee employee);
    void removeEmployeeFromCompany(Employee employee);
    static void getAllEmployeesUsingThreads(Department department, std::vector<Employee> *employeesOfDepartments);
    std::vector<Employee> getAllEmployees();
    int getEmployeesWithSameSalary();
    std::vector<Employee> getEmployeesOfMultipleDepartments();
    bool isThereAnyLoopsInDepartmentsHand(Department parent_department,std::set<std::string> *childrenOfDepartments);
    bool isThereAnyLoopsInDepartments();
    std::vector<Employee> getfloatingEmployees();
    Department * findDepartment(Department *needed_department);
    Department *findDepartmenthand(Department *needed_department,Department *parent_department,int &flag);
    Employee * findEmployeeInDepartment(Employee needed_employee,std::vector<Department>* range_of_departments);
    Employee *findEmployeeInCompany(Employee employee);


};



#endif /* COMPANY_H_ */
