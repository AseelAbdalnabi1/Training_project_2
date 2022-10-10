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
class Employee;
class Department;

class Company {
private:
    Employee *CeoEmp=NULL;
    std::vector<Department> MainDeps;
    static Company *compObject;
    static std::set<std::string> ChildsOfDeps;
    Company();
    ~Company();
public:
    static std::vector<Employee> empsOfDeps;//no duplicate
    static std::vector<Employee> empsOfMultiDeps_Results;
    static std::vector<Employee> listOfFloatingEmps;
    static std::vector<Employee> EmpsOfAllCompany;//all employees in company(regardless if they are in deps or not)
    static std::vector<Employee> allEmpsOfDepartments;//employees in Deps in company
    static Company *getCompObject(){
    	if(!(compObject))
    		compObject=new Company;
    	return compObject;
    }
    Employee getCeoEmp();
    void setCeoEmp(Employee CeoEmp);
    void setMainDeps(std::vector<Department> MainDeps);
    std::vector<Department>* getMainDeps();
    void addMainDepToCompany(Department dep);
    void removeMainDepFromCompany(Department dep);
    void removeMainDepFromCompany(std::string depName);
    void addEmpToCompany(Employee emp);
    void removeEmpFromCompany(Employee emp);
    std::vector<Employee> allEmployees();
    std::vector<Employee> empsWithSameSalary();
    std::vector<Employee> empsOfMultiDeps();
    bool loop_IN_Deps_hand(Department dep);
    bool loop_IN_Deps();
    bool floatingEmps();


};



#endif /* COMPANY_H_ */
