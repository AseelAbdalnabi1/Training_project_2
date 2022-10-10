/*
 * employee.h
 *
 *  Created on: Sep 8, 2022
 *      Author: aseel
 */

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_
#include "person.h"
#include "company.h"
class Person;
class Company;
enum ROLE {CEO, MANAGER, TEAM_LEAD, DEVELOPER, TESTER, HR};

class Employee : public Person{
private:
	ROLE Role;
	int Salary;
	static int ID;
	int empID;
	void setEmpId(int empID);
public:
	Employee(std::string Name,float Age ,ROLE Role,int Salary);
	static Employee* Create(std::string Name,float Age ,ROLE RoleType,int Salary);
	std::string getNameFromComp(Company *compObj);
	void setNameInCompany(std::string Name,Company *compObj);
	void setAgeInComapny(float Age,Company *compObj);
	float getAgeFromCompany(Company *compObj);

	void setRole(ROLE Role);
	void setRole(ROLE Role,Company *compObj);
	std::string getRole();
	std::string getRole(Company *compObj);
	void setSalary(int salary);
	void setSalary(int salary,Company *compObj);
	int getSalary();
	int getSalary(Company *compObj);
	int getEmpId();
	bool operator == (Employee Emp);
	bool operator == (int const &empID);
	~Employee();

};



#endif /* EMPLOYEE_H_ */

