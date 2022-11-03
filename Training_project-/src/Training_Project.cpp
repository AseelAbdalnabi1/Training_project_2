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
	Company *comp=comp->getCompanyObject();
		Department *dep1= new Department("dep1");
			Department *dep2= new Department("dep2");
			Department *dep3= new Department("dep3");
			Department *dep4= new Department("dep4");
			Department *dep5= new Department("dep5");
			Department *dep6= new Department("dep6");
			Department *dep7= new Department("dep7");
			Department *dep8= new Department("dep8");
			Department *dep9= new Department("dep9");
			Department *dep10= new Department("dep10");
			Employee *emp1=Employee::create("emp1",16,TESTER,1000);
		    Employee *emp2=Employee::create("emp2",25,DEVELOPER,3000);
		    Employee *emp3=Employee::create("emp3",24,MANAGER,2300);
		    Employee *emp4=Employee::create("emp4",24,DEVELOPER,2300);
		    Employee *emp5=Employee::create("emp5",24,TESTER,2350);
		    Employee *emp6=Employee::create("emp6",24,DEVELOPER,2360);
		    Employee *emp7=Employee::create("emp7",24,HR,6500);
		    Employee *emp8=Employee::create("emp8",24,HR,600);
		    Employee *emp9=Employee::create("emp9",29,TEAM_LEAD,600);
			Employee *emp11=Employee::create("emp11", 10, MANAGER, 2000);
			Employee *emp10=Employee::create("emp10",29,DEVELOPER,600);
			comp->addEmployeeToCompany(*emp10);
			comp->addEmployeeToCompany(*emp11);

			comp->addMainDepartmentToCompany(*dep1);
			comp->addMainDepartmentToCompany(*dep2);
			dep1->addSubDepartment(*dep3,comp);
			dep1->addSubDepartment(*dep4,comp);
			dep3->addSubDepartment(*dep5,comp);
			dep3->addSubDepartment(*dep6,comp);
			dep2->addSubDepartment(*dep7,comp);
			dep2->addSubDepartment(*dep8,comp);
			dep7->addSubDepartment(*dep9,comp);
			dep7->addSubDepartment(*dep10,comp);
			dep8->addSubDepartment(*dep10,comp);
			//----------------------------
			dep1->addEmployeeToDepartment(*emp1,comp);
			dep2->addEmployeeToDepartment(*emp2,comp);
			dep3->addEmployeeToDepartment(*emp3,comp);
			dep4->addEmployeeToDepartment(*emp4,comp);
			dep5->addEmployeeToDepartment(*emp5,comp);
			dep6->addEmployeeToDepartment(*emp6,comp);
			dep7->addEmployeeToDepartment(*emp7,comp);
			dep8->addEmployeeToDepartment(*emp8,comp);
			dep9->addEmployeeToDepartment(*emp9,comp);
			dep9->addEmployeeToDepartment(*emp5,comp);
			dep8->addEmployeeToDepartment(*emp1,comp);
			cout<<"---------------------end of company setup-----------------------"<<endl;
	}
class GetEmployeesOfDepartments: public httpserver::http_resource {
	public:
	Company *comp=comp->getCompanyObject();
    string employees;
		shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request&) {
		    employees.clear();
		    vector<Employee> localEmployeesOfDepartments=comp->getAllEmployees();
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
		Company *comp=comp->getCompanyObject();
		shared_ptr<httpserver::http_response> render_PUT(const httpserver::http_request& req){//
			Department newDep(req.get_arg("name"));
			comp->addMainDepartmentToCompany(newDep);//??
			return shared_ptr<httpserver::http_response>(new httpserver::string_response("Main department to be added : "+ req.get_arg("name")));
		}
};
class DeleteDepartmentfromCompany: public httpserver::http_resource {
	public:
		Company *comp=comp->getCompanyObject();
		shared_ptr<httpserver::http_response> render_DELETE(const httpserver::http_request& req) {
			cout<<"----------------------------------------------------"<<endl;
			comp->removeMainDepartmentFromCompany(req.get_arg("name"));
			return shared_ptr<httpserver::http_response>(new httpserver::string_response("Main department to be deleted :"+req.get_arg("name")));
		}
};
class companyTest : public ::testing::Test
{	public:
	Company *comp=comp->getCompanyObject();
};
TEST_F(companyTest, employeesOfDepartmentsTest) {
	EXPECT_EQ( 9,(int)comp->getAllEmployees().size());
	}
TEST_F(companyTest, employeesWithSameSalaryTest) {
	EXPECT_EQ( 5, comp->getEmployeesWithSameSalary());
}
TEST_F(companyTest, employeesOfMultipleDepartmentsTest) {
	EXPECT_EQ( 2 ,(int) comp->getEmployeesOfMultipleDepartments().size());
	}
TEST_F(companyTest, loopInDepartmentsTest) {
	ASSERT_TRUE(comp->isThereAnyLoopsInDepartments());
	}
TEST_F(companyTest, floatingEmployeesTest) {
	EXPECT_EQ( 2,(int)comp->getfloatingEmployees() .size());
}

int main ()
{
	SetupComany();
	httpserver::webserver ws = httpserver::create_webserver(8095);
	GetEmployeesOfDepartments EmployeesOfDepartments;
	ws.register_resource("/GetEmployeesOfDepartments", &EmployeesOfDepartments);
	AddMainDepartmentToCompany mainDepartmentToCompany;
	ws.register_resource("/AddMainDepartmentToCompany", &mainDepartmentToCompany);
	DeleteDepartmentfromCompany deleteMainDepartment;
	ws.register_resource("/DeleteDepartmentfromCompany", &deleteMainDepartment);
    //ws.start(true);
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS( ) ;

}

