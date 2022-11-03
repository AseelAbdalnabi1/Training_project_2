//============================================================================
// Name        : Training_Project.cpp
// Author      : Aseel_Abdalnabi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <httpserver.hpp>
#include <iostream>

#include "vector"
#include "../headers/company.h"
#include <thread>
#include <algorithm>
#include "../googleTestLib/gtest/gtest.h"
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
class Company;
class Employee;
class Department;
class Person;

void SetupComany(){
	cout<<"---------------------start of company setup-----------------------"<<endl;
	Company *company=company->getCompanyObject();
		Department *department1= new Department("dep1");
			Department *department2= new Department("dep2");
			Department *department3= new Department("dep3");
			Department *department4= new Department("dep4");
			Department *department5= new Department("dep5");
			Department *department6= new Department("dep6");
			Department *department7= new Department("dep7");
			Department *department8= new Department("dep8");
			Department *department9= new Department("dep9");
			Department *department10= new Department("dep10");
			Employee *employee1=Employee::create("emp1",16,TESTER,1000);
		    Employee *employee2=Employee::create("emp2",25,DEVELOPER,3000);
		    Employee *employee3=Employee::create("emp3",24,MANAGER,2300);
		    Employee *employee4=Employee::create("emp4",24,DEVELOPER,2300);
		    Employee *employee5=Employee::create("emp5",24,TESTER,2350);
		    Employee *employee6=Employee::create("emp6",24,DEVELOPER,2360);
		    Employee *employee7=Employee::create("emp7",24,HR,6500);
		    Employee *employee8=Employee::create("emp8",24,HR,600);
		    Employee *employee9=Employee::create("emp9",29,TEAM_LEAD,600);
			Employee *employee11=Employee::create("emp11", 10, MANAGER, 2000);
			Employee *employee10=Employee::create("emp10",29,DEVELOPER,600);
			company->addEmployeeToCompany(*employee10);
			company->addEmployeeToCompany(*employee11);

			company->addMainDepartmentToCompany(*department1);
			company->addMainDepartmentToCompany(*department2);
			department1->addSubDepartment(*department3,company);
			department1->addSubDepartment(*department4,company);
			department3->addSubDepartment(*department5,company);
			department3->addSubDepartment(*department6,company);
			department2->addSubDepartment(*department7,company);
			department2->addSubDepartment(*department8,company);
			department7->addSubDepartment(*department9,company);
			department7->addSubDepartment(*department10,company);
			department8->addSubDepartment(*department10,company);
			//----------------------------
			department1->addEmployeeToDepartment(*employee1,company);
			department2->addEmployeeToDepartment(*employee2,company);
			department3->addEmployeeToDepartment(*employee3,company);
			department4->addEmployeeToDepartment(*employee4,company);
			department5->addEmployeeToDepartment(*employee5,company);
			department6->addEmployeeToDepartment(*employee6,company);
			department7->addEmployeeToDepartment(*employee7,company);
			department8->addEmployeeToDepartment(*employee8,company);
			department9->addEmployeeToDepartment(*employee9,company);
			department9->addEmployeeToDepartment(*employee5,company);
			department8->addEmployeeToDepartment(*employee1,company);
			cout<<"---------------------end of company setup-----------------------"<<endl;
	}
class GetEmployeesOfDepartments: public httpserver::http_resource {
	public:
	Company *company=company->getCompanyObject();
    string employees;
		shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request&) {
		    employees.clear();
		    vector<Employee> localEmployeesOfDepartments=company->getAllEmployees();
	    	 int size=(int)localEmployeesOfDepartments.size();

	    	for(int i=0;i<size;i++)
	    	{
	    		employees=employees+localEmployeesOfDepartments.at(i).getName()+" , ";
	    	}
			return shared_ptr<httpserver::http_response>(new httpserver::string_response(employees));
		}
};

class AddMainDepartmentToCompany: public httpserver::http_resource {
	public:
		Company *company=company->getCompanyObject();
		shared_ptr<httpserver::http_response> render_PUT(const httpserver::http_request& req){
			Department newDep(req.get_arg("name"));
			company->addMainDepartmentToCompany(newDep);
			return shared_ptr<httpserver::http_response>(new httpserver::string_response("Main department to be added : "+ req.get_arg("name")));
		}
};
class DeleteDepartmentfromCompany: public httpserver::http_resource {
	public:
		Company *company=company->getCompanyObject();
		shared_ptr<httpserver::http_response> render_DELETE(const httpserver::http_request& req) {
			cout<<"----------------------------------------------------"<<endl;
			int department_id=stoi(req.get_arg("id"));
			company->removeMainDepartmentFromCompany(department_id);
			return shared_ptr<httpserver::http_response>(new httpserver::string_response("Main department to be deleted with ID:"+req.get_arg("id")));
		}
};
class companyTest : public ::testing::Test
{	public:
	Company *company=company->getCompanyObject();
};
TEST_F(companyTest, employeesOfDepartmentsTest) {
	EXPECT_EQ( 9,(int)company->getAllEmployees().size());
	}
TEST_F(companyTest, employeesWithSameSalaryTest) {
	EXPECT_EQ( 5, company->getEmployeesWithSameSalary());
}
TEST_F(companyTest, employeesOfMultipleDepartmentsTest) {
	EXPECT_EQ( 2 ,(int) company->getEmployeesOfMultipleDepartments().size());
	}
TEST_F(companyTest, loopInDepartmentsTest) {
	ASSERT_TRUE(company->isThereAnyLoopsInDepartments());
	}
TEST_F(companyTest, floatingEmployeesTest) {
	EXPECT_EQ( 2,(int)company->getfloatingEmployees() .size());
}

int main ()
{
	SetupComany();
	httpserver::webserver ws = httpserver::create_webserver(8090);
	GetEmployeesOfDepartments EmployeesOfDepartments;
	ws.register_resource("/GetEmployeesOfDepartments", &EmployeesOfDepartments);
	AddMainDepartmentToCompany mainDepartmentToCompany;
	ws.register_resource("/AddMainDepartmentToCompany", &mainDepartmentToCompany);
	DeleteDepartmentfromCompany deleteMainDepartment;
	ws.register_resource("/DeleteDepartmentfromCompany", &deleteMainDepartment);
    ws.start(true);
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS( ) ;

}

