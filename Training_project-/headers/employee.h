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
	ROLE role;
	int salary;
	static int id;
	int employee_id;
	void setEmployeeId(int employee_id);
public:
	Employee(std::string name,float age ,ROLE role,int salary);
	static Employee* create(std::string name,float age ,ROLE roleType,int salary);
	void setRole(ROLE role);
	void setRole(ROLE role,Company *company_object);
	std::string getRole();
	std::string getRole(Company *company_object);
	void setSalary(int salary);
	void setSalary(int salary,Company *company_object);
	int getSalary();
	int getSalary(Company *company_object);
	int getEmployeeId();
	bool operator == (Employee Employee);
	bool operator == (int const &employee_id);
	~Employee();

};



#endif /* EMPLOYEE_H_ */

