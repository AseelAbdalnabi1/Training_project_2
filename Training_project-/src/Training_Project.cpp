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
static vector<Department> test={};
static int flag;
static Department *foundDep=nullptr;
void TestFunctionToSeeAllTheCompanyDepsHand(Department dep,Company *compObj);
Department *findDepartmenthand(Department *neededDep,Company *compObj,Department *parent,int &flag);

Department * findDepartment(Department *neededDep,Company *compObj){
	foundDep=nullptr;
	flag=0;//department not found
	int size=(int) compObj->getMainDeps()->size();
	    for(int i=0;i<size;i++){
	    	findDepartmenthand(neededDep,compObj,&(compObj->getMainDeps()->at(i)),flag);
	    	if(foundDep!=nullptr && flag==1){
	    		return foundDep;
	    		break;
	    	}else if(foundDep==nullptr && flag==0){
	    		continue;
	    	}
	    }
	    return nullptr;
}
Department *findDepartmenthand(Department *neededDep,Company *compObj,Department *parent,int &flag){
	if (flag==1){
		return foundDep;
	}
	if((*neededDep)==(*parent)){
		flag=1;
        foundDep = parent;
		return foundDep;
	}if(flag==0){
	if(parent->isAnySubDeps()==1){
	    	for(auto f=parent->getSubDeps()->begin();f!=parent->getSubDeps()->end();f++){
	    		findDepartmenthand(neededDep,compObj,&(*f),flag);
	    	}
	  }
	return nullptr;
	}


}
Employee * findEmployeeInDep(Employee NeededEmp,Company *compObj,vector<Department>* RangeOfDeps){//for hirarichy
	for( auto it1=RangeOfDeps->begin();it1!=RangeOfDeps->end();it1++){
		auto it2=find((*it1).getEmpsOfDep()->begin(),(*it1).getEmpsOfDep()->end(),NeededEmp);
		if(it2 != (*it1).getEmpsOfDep()->end()){
			return &(*it2);
		}
		return findEmployeeInDep(NeededEmp,compObj,(*it1).getSubDeps());//for hirarichy
	}
}


Employee *findEmployeeInCompany(Employee emp,Company *compObj){
	auto i=find(compObj->EmpsOfAllCompany.begin(),compObj->EmpsOfAllCompany.end(),emp);
	if(i != compObj->EmpsOfAllCompany.end()){
		cout<<"employee found in EmpsOfAllCompany"<<endl;
		return &(*i);
	}
	else{
		cout<<"employee not found in company"<<endl;
		return nullptr;
	}
}
void TestFunctionToSeeAllTheCompanyDeps(Company *compObj){//all department regardless if they are repeated or not
	test.clear();
	for(auto i=compObj->getMainDeps()->begin();i!=compObj->getMainDeps()->end();i++){
		       test.push_back((*i));
		       if((*i).isAnySubDeps()==1){
		    	   TestFunctionToSeeAllTheCompanyDepsHand((*i),compObj);
		       }
		}
	cout<<"--------------------------------------------------------------------------"<<endl;
	 for(auto it=test.begin();it!=test.end();it++){
		 cout<<"department name :"<<(*it).getDepName()<<endl;
	 }
	 cout<<"--------------------------------------------------------------------------"<<endl;
}
void TestFunctionToSeeAllTheCompanyDepsHand(Department dep,Company *compObj){
	for( auto j=dep.getSubDeps()->begin();j!=dep.getSubDeps()->end();j++){
		 test.push_back((*j));
		 if((*j).isAnySubDeps()==1){
			 TestFunctionToSeeAllTheCompanyDepsHand((*j),compObj);
		 }
	}
}
/*int main() {
	Company *comp=comp->getCompObject();
	/*Department dep1("backend");
	Department dep5("dep5");
	Department dep6("dep6");
	Department dep2("dep2");
	dep5.addSubDep(dep6);
	dep1.addSubDep(dep5);*/
	/*Department dep1("dep1");
	Department dep5("dep5");
	Department dep55("dep55");
	Department dep6("dep6");

	Department dep2("dep2");
	Department dep3("dep3");
	Department dep4("dep4");
	Department dep7("dep7");
	Department dep8("dep8");
	Department dep9("dep9");
	Department dep10("dep10");
	Department dep11("dep11");
	Department dep12("dep12");

  /*  comp->addMainDepToCompany(dep1);
    comp->addMainDepToCompany(dep2);
    cout<<comp->getMainDeps()->size()<<endl;
    cout<<comp->getMainDeps()->at(0).getSubDeps()->size()<<endl;
    TestFunctionToSeeAllTheCompanyDeps(comp);
    Employee emp1("emp1",16,MANAGER,6000);
    Employee emp2("emp2",25,HR,4000);
    Employee emp3("emp3",24,MANAGER,2300);
    Employee emp4("emp4",24,MANAGER,2300);
    Employee emp5("emp5",24,MANAGER,2350);
    Employee emp6("emp6",24,MANAGER,2350);
    Employee emp7("emp7",24,HR,6000);
    Employee emp8("emp8",24,HR,600);
    Employee emp9("emp9",29,HR,600);
    Employee emp10("emp10",29,HR,600);
    Employee *emp11=Employee::Create("emp11", 10, MANAGER, 2000);
    Employee *emp12=Employee::Create("emp12", 10, HR, 2000);
    Employee *emp13=Employee::Create("emp13", 10, TEAM_LEAD, 2000);
    Employee *emp14=Employee::Create("emp14", 10, DEVELOPER, 2000);
    Employee *emp15=Employee::Create("emp15", 10, TESTER, 2000);*/

	 /*Employee emp1("emp1",16,MANAGER,6000);
	    Employee emp2("emp2",25,HR,4000);
	    Employee emp3("emp3",24,MANAGER,2300);
	    Employee emp4("emp4",24,MANAGER,2300);
	    Employee emp5("emp5",24,MANAGER,2350);
	    Employee emp6("emp6",24,MANAGER,2350);
	    Employee emp7("emp7",24,HR,6000);
	    Employee emp8("emp8",24,HR,600);
	    Employee emp9("emp9",29,HR,600);
	    Employee emp10("emp10",29,HR,600);
	    Employee *emp11=Employee::Create("emp11", 10, MANAGER, 9500);
	    Employee *emp12=Employee::Create("emp12", 10, HR, 10000);
	    Employee *emp13=Employee::Create("emp13", 10, HR, 10000);

		dep5.addSubDep(dep6);
		dep5.addSubDep(dep10);
		dep1.addSubDep(dep5);
		dep55.addSubDep(dep8);
		dep1.addSubDep(dep55);
		dep7.addSubDep(dep11);
		dep2.addSubDep(dep7);
		dep4.addSubDep(dep12);
		dep3.addSubDep(dep4);

	    comp->addMainDepToCompany(dep1);
	    comp->addMainDepToCompany(dep2);
	    comp->addMainDepToCompany(dep3);

	    cout<<"---------------------testing----------------------"<<endl;
	    //cout<<"finding the dep7 department ,name of department : "<<findDepartment(&dep7,comp,comp->getMainDeps())->getDepName()<<endl;
	        //cout<<"finding the dep7 department ,number of employees : "<<findDepartment(dep7,comp,comp->getMainDeps())->getEmpsOfDep(comp)->size()<<endl;
	      //  cout<<"finding the dep7 department ,number of subdep  : "<<findDepartment(&dep7,comp,comp->getMainDeps())->getSubDeps(comp)->size()<<endl;
	     //dep8.addSubDep(dep9, comp);
       // dep10.addSubDep(dep9, comp);
        //cout<<dep10.getSubDeps(comp)->size()<<endl;
       // cout<<dep10.getSubDeps()->size()<<endl;
//cout<<comp->getMainDeps()->at(0).getSubDeps()->at(0).getDepName()<<endl;
//cout<<comp->getMainDeps()->at(1).getSubDeps()->at(0).getSubDeps()->size()<<endl;
TestFunctionToSeeAllTheCompanyDeps(comp);
        cout<<"----------------end---of--testing----------------------"<<endl;
        cout<<"-------------------------------------------------------start-testing---------------------------------------------------------"<<endl;
        dep1.addEmpToDep(emp1,comp);
    	dep2.addEmpToDep(emp2,comp);
    	dep3.addEmpToDep(emp3,comp);
    	dep4.addEmpToDep(emp4,comp);
    	dep5.addEmpToDep(emp5,comp);
    	dep6.addEmpToDep(emp6,comp);
    	dep7.addEmpToDep(emp7,comp);
    	dep8.addEmpToDep(emp8,comp);
    	dep10.addEmpToDep(emp10,comp);
    	dep11.addEmpToDep(emp10,comp);
    	dep55.addEmpToDep(emp9,comp);
    	dep11.addEmpToDep(*emp11,comp);
    	dep6.addEmpToDep(*emp11,comp);
    	dep12.addEmpToDep(*emp12,comp);
    	   cout<<"-----------------------------------------------------------------------------------------"<<endl;
    	     comp->allEmployees();
    	     cout<<"-----------------------------------------------------------------------------------------"<<endl;

    	     cout<<"Employees of Departments : "<<endl;
    	            for(auto i=comp->allEmpsOfDepartments.begin();i!=comp->allEmpsOfDepartments.end();i++){
    	            	 cout<<"Employee name & Employee ID : "<<i->getName()<<"  |  "<<i->getEmpId()<<endl;
    	            }
    	cout<<"------------------------------------------------end of add emp testing----------------------------------------"<<endl;

	     cout<<"Employees of all Company : "<<endl;
	            for(auto i=comp->EmpsOfAllCompany.begin();i!=comp->EmpsOfAllCompany.end();i++){
	            	 cout<<"Employee name & Employee ID : "<<i->getName()<<"  |  "<<i->getEmpId()<<endl;
	            }
    	comp->empsWithSameSalary();
    	    cout<<"---------------------------------hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh--------------------------------------------------------"<<endl;
    	    comp->empsOfMultiDeps();
    	    dep6.removeEmpFromDep(*emp11, comp);
    	    dep11.removeEmpFromDep(emp10, comp);
    	    comp->empsOfMultiDeps();
    	    cout<<"------------------------------------hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh-----------------------------------------------------"<<endl;
    	    cout<<comp->loop_IN_Deps()<<endl;
    	    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    	    dep8.addSubDep(dep9, comp);
    	    dep10.addSubDep(dep9, comp);
    	    cout<<comp->loop_IN_Deps()<<endl;
    	    dep8.RemoveSubDep(dep9, comp);
    	    dep10.RemoveSubDep(dep9, comp);
    	    cout<<"-----------------------------------------------------------------------------------------"<<endl;

    	    cout<<comp->loop_IN_Deps()<<endl;
    	    cout<<"----------------------------floating testing   -------------------------------------------------------------"<<endl;
cout<<comp->floatingEmps()<<endl;
comp->addEmpToCompany(*emp13);
cout<<comp->floatingEmps()<<endl;//1
cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
comp->removeEmpFromCompany(*emp13);
cout<<comp->floatingEmps()<<endl;
    /*dep1.addEmpToDep(emp1, comp);
    dep1.addEmpToDep(*emp11,comp);
    dep1.addEmpToDep(*emp12,comp);
    dep1.addEmpToDep(*emp13,comp);
    dep1.addEmpToDep(*emp14,comp);
    dep1.addEmpToDep(*emp15,comp);
    dep1.addEmpToDep(emp4, comp);
    dep1.addEmpToDep(emp5, comp);
    dep5.addEmpToDep(emp2, comp);
    dep5.addEmpToDep(emp6, comp);
    dep5.addEmpToDep(emp7, comp);
    dep6.addEmpToDep(emp3, comp);
    dep6.addEmpToDep(emp8, comp);
    dep6.addEmpToDep(emp9, comp);
    dep2.addEmpToDep(emp7, comp);
    dep2.addEmpToDep(emp9, comp);
    dep2.addEmpToDep(emp5, comp);
    dep2.addSubDep(dep6, comp);
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<"the name of emp1 in company : "<<findEmployeeInDep(emp1,comp,comp->getMainDeps())->getName(comp)<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<"the name of emp2 in company : "<<findEmployeeInDep(emp2,comp,comp->getMainDeps())->getName(comp)<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<"the name of emp3 in company : "<<findEmployeeInDep(emp3,comp,comp->getMainDeps())->getName(comp)<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<"finding the dep1(backend) department ,name of department : "<<findDepartment(dep1,comp,comp->getMainDeps())->getDepName()<<endl;
    cout<<"finding the dep1(backend) department ,number of employees : "<<findDepartment(dep1,comp,comp->getMainDeps())->getEmpsOfDep(comp)->size()<<endl;
    cout<<"finding the dep1(backend) department ,number of subdep  : "<<findDepartment(dep1,comp,comp->getMainDeps())->getSubDeps(comp)->size()<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<"finding the dep5(dep5) department ,name of department : "<<findDepartment(dep5,comp,comp->getMainDeps())->getDepName()<<endl;
    cout<<"finding the dep5(dep5) department ,number of employees : "<<findDepartment(dep5,comp,comp->getMainDeps())->getEmpsOfDep(comp)->size()<<endl;
    cout<<"finding the dep5(dep5) department ,number of subdep  : "<<findDepartment(dep5,comp,comp->getMainDeps())->getSubDeps(comp)->size()<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<"finding the dep6 department ,name of department : "<<findDepartment(dep6,comp,comp->getMainDeps())->getDepName()<<endl;
    cout<<"finding the dep6 department ,number of employees : "<<findDepartment(dep6,comp,comp->getMainDeps())->getEmpsOfDep(comp)->size()<<endl;
    cout<<"finding the dep6 department ,number of subdep  : "<<findDepartment(dep6,comp,comp->getMainDeps())->getSubDeps(comp)->size()<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    comp->empsWithSameSalary(comp);
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    comp->empsOfMultiDeps();
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    comp->allEmployees();
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<comp->loop_IN_Deps()<<endl;
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    cout<<"Employees of Departments : "<<endl;
        for(auto i=comp->allEmpsOfDepartments.begin();i!=comp->allEmpsOfDepartments.end();i++){
        	 cout<<"Employee name & Employee ID : "<<i->getName()<<"  |  "<<i->getEmpId()<<endl;
        }
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    comp->floatingEmps();
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    comp->addEmpToCompany(emp10);
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    comp->floatingEmps();
    TestFunctionToSeeAllTheCompanyDeps(comp);
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    /*comp->removeEmpFromCompany(emp10);
    cout<<"-----------------------------------------------------------------------------------------"<<endl;
    comp->floatingEmps();


    cout << "started"<<endl;;
	Company *comp=comp->getCompObject();
	cout << "company created"<<endl;;
	//
	//comp->setCeoEmp(CEOemp);
	cout << "CEO created"<<endl;
//	cout<<"hello"<<endl;
	cout<<comp->getCeoEmp().getAge(comp)<<"   "<<comp->getCeoEmp().getName(comp)<<"   "<<comp->getCeoEmp().getEmpId()<<"   "<<comp->getCeoEmp().getRole(comp)<<"   "<<comp->getCeoEmp().getSalary(comp)<<endl;
	Employee CEOemp("Aseel",24,CEO,500500);
	//cout<<comp->getCeoEmp().getAge(comp)<<"   "<<comp->getCeoEmp().getName(comp)<<"   "<<comp->getCeoEmp().getEmpId()<<"   "<<comp->getCeoEmp().getRole(comp)<<"   "<<comp->getCeoEmp().getSalary(comp)<<endl;
	cout<<"*************************************************************************************"<<endl;
	comp->setCeoEmp(CEOemp);///set aseel as the CEO
	cout<<comp->getCeoEmp().getAge(comp)<<"   "<<comp->getCeoEmp().getName(comp)<<"   "<<comp->getCeoEmp().getEmpId()<<"   "<<comp->getCeoEmp().getRole(comp)<<"   "<<comp->getCeoEmp().getSalary(comp)<<endl;
		//comp->getCeoEmp().
	comp->getCeoEmp().setSalary(53120,comp);
	//comp->getCeoEmp().setRole(HR,comp);
	comp->getCeoEmp().setName("aseeooool",comp);
	CEOemp.setName("ASEEEEEOLLLL");
	cout<<CEOemp.getName()<<endl;
	CEOemp.setAge(50);
	cout<<CEOemp.getAge()<<endl;
	//comp->getCeoEmp().setEmpId(2, comp);
	cout<<"*************************************************************************************"<<endl;

	cout<<comp->getCeoEmp().getAge(comp)<<"   "<<comp->getCeoEmp().getName(comp)<<"   "<<comp->getCeoEmp().getEmpId()<<"   "<<comp->getCeoEmp().getRole(comp)<<"   "<<comp->getCeoEmp().getSalary(comp)<<endl;
	cout<<"*************************************************************************************"<<endl;
Department dep1("backend");
Department dep2("frontend");
Department dep3("HR");
Department dep4("UI/UX");
Department dep45("backend");

cout<<"*******************************------------------------------******************************************************"<<endl;
cout<<"size :"<<comp->getMainDeps()->size()<<endl;
comp->addMainDepToCompany(dep1);
cout<<"size :"<<comp->getMainDeps()->size()<<endl;
comp->addMainDepToCompany(dep2);
cout<<"size :"<<comp->getMainDeps()->size()<<endl;
comp->addMainDepToCompany(dep3);
cout<<"size :"<<comp->getMainDeps()->size()<<endl;
comp->addMainDepToCompany(dep4);
cout<<"size : hehhe "<<comp->getMainDeps()->size()<<endl;
cout<<comp->getMainDeps()->front().getDepName()<<endl;
	//	at[0].getDepName()<<endl;

cout<<comp->getMainDeps()->size()<<endl;
cout<<"******************************"<<endl;
//cout<<comp->getMainDeps()->front().getDepName()<<endl;
vector<Department> vd=*comp->getMainDeps();
for(auto j=vd.begin();j!=vd.end();j++){
	cout<<(*j).getDepName()<<endl;
}
cout<<"******************************"<<endl;
comp->removeMainDepFromCompany(dep1);
cout<<"size :"<<comp->getMainDeps()->size()<<endl;
comp->removeMainDepFromCompany(dep2);
cout<<"size :"<<comp->getMainDeps()->size()<<endl;
comp->removeMainDepFromCompany(dep3);
cout<<"size :"<<comp->getMainDeps()->size()<<endl;
comp->removeMainDepFromCompany(dep4);
cout<<"size :"<<comp->getMainDeps()->size()<<endl;
cout<<"***************************************************************************************"<<endl;
cout<<"size of vd "<<vd.size()<<endl;
comp->setMainDeps(vd);
cout<<"size :"<<comp->getMainDeps()->size()<<endl;
cout<<comp->getMainDeps()->at(1).getDepName()<<endl;
//Employee(std::string Name,float Age ,ROLE Role,int Salary);
cout<<"******************************"<<endl;
Employee emp1("ahmad",21.5,HR,20123);
Employee emp2("SAMI",25.5,HR,20100);
Employee emp3("faris",30,MANAGER,50000);
Employee emp4("	MALAK",24,MANAGER,50050);
cout<<emp1.getAge()<<" "<<emp1.getEmpId()<<" "<<emp1.getName()<<" "<<emp1.getRole()<<" "<<emp1.getSalary()<<endl;
emp1.setAge(20);emp1.setName("ADAM");emp1.setRole(NO_ROLE);emp1.setSalary(54444);
cout<<emp1.getAge()<<" "<<emp1.getEmpId()<<" "<<emp1.getName()<<" "<<emp1.getRole()<<" "<<emp1.getSalary()<<endl;
cout<<"******************************"<<endl;
comp->addEmpToCompany(emp1);
comp->addEmpToCompany(emp2);
comp->addEmpToCompany(emp3);
comp->addEmpToCompany(emp4);
cout<<comp->EmpsOfAllCompany.size()<<endl;
cout<<"******************************"<<endl;
comp->removeEmpFromCompany(emp1);
comp->removeEmpFromCompany(emp2);
cout<<comp->EmpsOfAllCompany.size()<<endl;//3
cout<<"******************************"<<endl;
Department dep9("dep9");
Department dep8("dep8");
Department dep6("dep6");
Department dep7("dep7");
vector<Department> departs;
departs.push_back(dep6);
departs.push_back(dep7);
Department dep5("dep5");
//cout<<departs.size()<<endl;
dep5.setSubDeps(departs);
//cout<<dep5.getSubDeps().at(0).getDepNum()<<endl;
//cout<<dep5.isAnySubDeps()<<endl;
cout<<"******************************************************"<<endl;
cout<<dep5.getSubDeps()->size()<<endl;

cout<<dep5.isAnySubDeps()<<endl;
cout<<"******************************************************"<<endl;
for(auto i=dep5.getSubDeps()->begin();i!=dep5.getSubDeps()->end();i++){
	cout<<"name of dep: "<<(*i).getDepName()<<endl;
}
comp->getMainDeps()->at(0).addSubDep(dep5);
comp->getMainDeps()->at(1).addSubDep(dep8);
comp->getMainDeps()->at(2).addSubDep(dep9);
cout<<comp->getMainDeps()->at(0).isAnySubDeps()<<endl;
cout<<comp->getMainDeps()->at(1).isAnySubDeps()<<endl;
cout<<comp->getMainDeps()->at(2).isAnySubDeps()<<endl;
cout<<"*****************************************************"<<endl;
cout<<" the getSubDeps(comp) use "<<comp->getMainDeps()->at(0).getSubDeps(comp)->at(0).getSubDeps(comp)->size()<<endl;
cout<<" the getSubDeps(comp) required use "<<comp->getMainDeps()->at(0).getSubDeps(comp)->at(0).getDepName()<<endl;
cout<<comp->getMainDeps()->at(1).getDepName()<<endl;
cout<<comp->getMainDeps()->at(2).getDepName()<<endl;
cout<<comp->getMainDeps()->at(1).getSubDeps(comp)->at(0).getDepName()<<endl;
//cout<<comp->getMainDeps()->at(1).getSubDeps(comp)->at(1).getDepName()<<endl;
cout<<comp->getMainDeps()->at(2).getSubDeps(comp)->at(0).getDepName()<<endl;
//cout<<comp->getMainDeps()->at(2).getSubDeps(comp)->at(1).getDepName()<<endl;
cout<<"******************************************************"<<endl;
Department dep10("dep10");
Department dep11("dep11");
vector<Department> dept;
dept.push_back(dep10);
dept.push_back(dep11);
cout<<"******************************************************"<<endl;
//comp->getMainDeps()->at(3).addSubDep(dep9,comp);
dep4.addSubDep(dep10,comp);
cout<<comp->getMainDeps()->at(3).isAnySubDeps()<<endl;
cout<<comp->getMainDeps()->at(3).getDepName()<<endl;
cout<<"...............................................here..............................................."<<endl;
cout<<comp->getMainDeps()->at(3).getSubDeps()->size()<<endl;//1
cout<<comp->getMainDeps()->at(3).getSubDeps(comp)->size()<<endl;//1
cout<<dep4.isAnySubDeps()<<endl;//1
cout<<dep4.getSubDeps(comp)->size()<<endl;//1
cout<<dep4.getSubDeps()->size()<<endl;//1
cout<<"******************************************************"<<endl;
dep4.RemoveSubDep(dep10, comp);
cout<<"...............................................here..............................................."<<endl;
cout<<comp->getMainDeps()->at(3).getSubDeps()->size()<<endl;//0
cout<<comp->getMainDeps()->at(3).getSubDeps(comp)->size()<<endl;//0
cout<<dep4.isAnySubDeps()<<endl;//0
cout<<dep4.getSubDeps(comp)->size()<<endl;//0
cout<<dep4.getSubDeps()->size()<<endl;//0

cout<<"...............................................here..............................................."<<endl;



cout<<dep4.isAnySubDeps()<<endl;//0
cout<<comp->getMainDeps()->at(3).isAnySubDeps()<<endl;//0
cout<<"******************************************************"<<endl;
//dep4.setSubDeps(dept, comp);
comp->getMainDeps()->at(3).setSubDeps(dept);
cout<<dep4.isAnySubDeps()<<endl;//0
cout<<comp->getMainDeps()->at(3).isAnySubDeps()<<endl;//1
cout<<comp->getMainDeps()->at(3).getSubDeps(comp)->size()<<endl;//2
//Employee(std::string Name,float Age ,ROLE Role,int Salary);
Employee emp10("emp10",60.0,HR,100);
Employee emp11("emp11",60.0,MANAGER,100);
Employee emp12("emp12",60.0,HR,200);
Employee emp13("emp13",60.0,HR,200);
Employee emp14("emp14",60.0,HR,300);
Employee emp15("emp15",60.0,HR,300);
Employee emp16("emp16",60.0,HR,51511);
Employee emp17("emp17",60.0,HR,51511);
cout<<comp->getMainDeps()->at(3).getSubDeps(comp)->at(0).getDepName()<<endl;
cout<<comp->getMainDeps()->at(3).getSubDeps(comp)->at(1).getDepName()<<endl;
cout<<"******************************//////////////////////////////////****************************"<<endl;
//cout<<comp->getMainDeps()->at(3).getSubDeps(comp)->at(0).getDepName()<<endl;
//cout<<comp->getMainDeps()->at(3).getSubDeps(comp)->at(1).getDepName(comp)<<endl;
/*cout<<findEmployeeInCompany(emp4,comp)->getName()<<endl;
//cout<<findEmployeeInCompany(emp4,comp)->getName(comp)<<endl;
cout<<"******************************//////////////////////////////////****************************"<<endl;
//emp4.setName("malooka",comp);
/*cout<<findEmployeeInCompany(emp4,comp)->getName()<<endl;
cout<<emp4.getName()<<endl;
cout<<emp4.getName(comp)<<endl;
cout<<"******************************//////////////////////////////////****************************"<<endl;
/*vector<Employee> emp18;
emp18.push_back(emp10);
emp18.push_back(emp11);
comp->getMainDeps()->at(0).setEmpsOfDep(emp18);
cout<<comp->getMainDeps()->at(0).getEmpsOfDep()->size()<<endl;//2
for(auto i=comp->getMainDeps()->at(0).getEmpsOfDep()->begin();i!=comp->getMainDeps()->at(0).getEmpsOfDep()->end();i++){

	cout<<(*i).getName()<<endl;

}
cout<<"...............................................here..............................................."<<endl;


comp->getMainDeps()->at(0).removeEmpFromDep(emp10);
comp->getMainDeps()->at(0).removeEmpFromDep(emp11);
for(auto i=comp->getMainDeps()->at(0).getEmpsOfDep()->begin();i!=comp->getMainDeps()->at(0).getEmpsOfDep()->end();i++){

	cout<<(*i).getName()<<endl;

}
cout<<"............................emp...................here..............emp................................."<<endl;

dep1.addEmpToDep(emp10, comp);
dep1.addEmpToDep(emp11, comp);
//comp->getMainDeps()->at(0).addEmpToDep(emp10);
//comp->getMainDeps()->at(0).addEmpToDep(emp11);
for(auto i=comp->getMainDeps()->at(0).getEmpsOfDep()->begin();i!=comp->getMainDeps()->at(0).getEmpsOfDep()->end();i++){

	cout<<(*i).getName()<<endl;

}
cout<<"...............................................here..............................................."<<endl;

cout<<dep1.getEmpsOfDep(comp)->size()<<endl;//2
cout<<comp->getMainDeps()->at(0).getEmpsOfDep()->size()<<endl;//2

cout<<"...............................................there..............................................."<<endl;
cout<<comp->getMainDeps()->at(1).getEmpsOfDep()->size()<<endl;//0
comp->getMainDeps()->at(1).addEmpToDep(emp12,comp);//frontend
comp->getMainDeps()->at(0).getSubDeps()->at(0).addEmpToDep(emp13,comp);//dep5
comp->getMainDeps()->at(0).getSubDeps()->at(0).getSubDeps()->at(0).addEmpToDep(emp14,comp);
comp->getMainDeps()->at(0).getSubDeps()->at(0).getSubDeps()->at(1).addEmpToDep(emp15,comp);
cout<<"...............................................there..............................................."<<endl;
cout<<comp->getMainDeps()->at(1).getEmpsOfDep()->size()<<endl;//1
cout<<comp->getMainDeps()->at(0).getSubDeps()->at(0).getEmpsOfDep()->size()<<endl;//1
cout<<comp->getMainDeps()->at(0).getSubDeps()->at(0).getSubDeps()->at(0).getEmpsOfDep()->size()<<endl;//1
cout<<comp->getMainDeps()->at(0).getSubDeps()->at(0).getSubDeps()->at(1).getEmpsOfDep()->size()<<endl;//1
cout<<"...............................................started..............................................."<<endl;
vector<Employee> vecEmp=comp->allEmployees();
for(auto i=vecEmp.begin();i!=vecEmp.end();i++){
	cout<<"name of employee : "<<(*i).getName()<<" , "<<"id of employee : "<<(*i).getEmpId()<<endl;
}

cout<<"size of allEmployees : "<<vecEmp.size()<<endl;
cout<<"...............................................ended..............................................."<<endl<<endl;


cout<<"...............................................started..............................................."<<endl;
cout<<comp->getMainDeps()->at(2).getEmpsOfDep()->size()<<endl;//0
cout<<comp->getMainDeps()->at(3).getEmpsOfDep()->size()<<endl;//0
comp->getMainDeps()->at(2).addEmpToDep(emp14);
comp->getMainDeps()->at(2).addEmpToDep(emp15);
comp->getMainDeps()->at(3).addEmpToDep(emp12);
cout<<comp->getMainDeps()->at(2).getEmpsOfDep()->size()<<endl;//2
cout<<comp->getMainDeps()->at(3).getEmpsOfDep()->size()<<endl;//1
cout<<"...............................................testing emps of multi_deps APIs.............................................."<<endl;
vector<Employee> EmpMul=comp->empsOfMultiDeps();
for(auto i=EmpMul.begin();i!=EmpMul.end();i++){
	cout<<"name of employee : "<<(*i).getName()<<" , "<<"empId: "<<(*i).getEmpId()<<endl;
}
cout<<"size is:"<<EmpMul.size()<<endl;
cout<<"...............................................testing emps of multi_deps APIs---ending.............................................."<<endl;
cout<<"...............................................testing emps of sameSalary APIs.............................................."<<endl;
comp->empsWithSameSalary(comp);
cout<<endl;
cout<<endl;
cout<<"...............................................testing emps of loopInDeps API strarting.............................................."<<endl;
cout<<"do we have loops in deps?    "<<comp->loop_IN_Deps()<<endl;//0
//dep9.addSubDep(dep6, comp);
TestFunctionToSeeAllTheCompanyDeps(comp);
cout<<"hello"<<endl;
cout<<dep6.getSubDeps(comp)->size();
//cout<<dep9.getSubDeps()->size()<<endl;
//cout<<dep9.getSubDeps()->size()<<endl;
cout<<"................................................................hi........................................................."<<endl;
/*Department *dep=findDepartment(dep9,comp);
cout<<dep->getDepName()<<endl;//dep9

cout<<dep->getSubDeps(comp)->size()<<endl;*/
//cout<<"..................................................................there......................................................."<<endl;
/*dep9.addSubDep(dep6, comp);
cout<<"does dep9 have any sub deps  :"<<dep9.isAnySubDeps()<<endl;
dep10.addSubDep(dep8, comp);
cout<<"does dep10 have any sub deps  :"<<dep10.isAnySubDeps()<<endl;
dep1.addSubDep(dep8, comp);
dep3.addSubDep(dep8,comp);
cout<<"does dep3(HR) have any sub deps , how many? :"<<dep3.isAnySubDeps()<<" | "<<dep3.getSubDeps(comp)->size()<<endl;
//dep9.addSubDep(dep6, comp);//ما بعلق بس م بضيفها على الcompany
//dep5.addSubDep(dep8,comp);//بعلق
dep7.addSubDep(dep11,comp);
cout<<"does dep7 have any sub deps , how many? :"<<dep7.isAnySubDeps()<<" | "<<dep7.getSubDeps()->size()<<endl;
dep8.addSubDep(dep11,comp);
cout<<"does dep8 have any sub deps , how many? :"<<dep8.isAnySubDeps()<<" | "<<dep8.getSubDeps(comp)->size()<<endl;
//dep5.RemoveSubDep(dep6, comp);//علق
//dep5.RemoveSubDep(dep7, comp);//علr
cout<<dep4.getDepName()<<endl;
dep2.RemoveSubDep(dep8, comp);
dep4.RemoveSubDep(dep10, comp);
dep4.RemoveSubDep(dep11, comp);*/
/*dep10.addEmpToDep(emp16, comp);
dep10.addEmpToDep(emp16);
cout<<"employeees of dep10 : "<<dep10.getEmpsOfDep(comp)->size()<<endl;
cout<<"employeees of dep10 : "<<dep10.getEmpsOfDep()->size()<<endl;
*/
//dep10.setSubDeps(departs, comp);
//cout<<".................................................................testing....................................................."<<endl;

//TestFunctionToSeeAllTheCompanyDeps(comp);
/*cout<<"finding the dep1(backend) department ,name of department : "<<findDepartment(dep1,comp)->getDepName()<<endl;
cout<<"finding the dep1(backend) department ,number of employees : "<<findDepartment(dep1,comp)->getEmpsOfDep(comp)->size()<<endl;
cout<<"finding the dep1(backend) department ,number of subdep  : "<<findDepartment(dep1,comp)->getSubDeps(comp)->size()<<endl;
cout<<".................................................................testing....................................................."<<endl;
//cout<<"finding the dep5(dep5)department ,name of department : "<<findDepartment(dep5,comp)->getDepName()<<"in Training project "<<endl;
//cout<<"finding the dep5(dep5) department ,number of employees : "<<findDepartment(dep5,comp)->getEmpsOfDep(comp)->size()<<endl;
//cout<<"finding the dep5(dep5) department ,number of subdep  : "<<findDepartment(dep5,comp)->getSubDeps(comp)->size()<<endl;
cout<<".......................................................................here.................................................."<<endl;
//cout<<"before"<<endl;
//dep=findDepartment(dep6,comp);
//cout<<"after"<<endl;

//cout<<dep->getDepName()<<"  "<<dep->getSubDeps()->size()<<endl;
cout<<"..................................................hhhhhhhhhhhhhhhhhhhh......................................................................."<<endl;
cout<<comp->getMainDeps()->at(2).getSubDeps()->at(0).getDepName()<<endl;
cout<<comp->getMainDeps()->at(2).getSubDeps()->at(0).getSubDeps()->size()<<endl;
cout<<comp->getMainDeps()->at(2).getSubDeps(comp)->at(0).getSubDeps(comp)->size()<<endl;
//comp->getMainDeps()->at(2).getSubDeps()->at(0).addSubDep(dep6,comp);
TestFunctionToSeeAllTheCompanyDeps(comp);
cout<<"do we have loops in deps?    "<<comp->loop_IN_Deps()<<endl;//1
//comp->getMainDeps()->at(2).getSubDeps()->at(0).RemoveSubDep(dep6);
//dep9.RemoveSubDep(dep6, comp);
//comp->getMainDeps()->at(2).getSubDeps()->at(0).setSubDeps(departs);
//dep9.setSubDeps(departs,comp);

cout<<dep9.getSubDeps()->size()<<"   "<<dep9.getSubDeps(comp)->size()<<"   "<<comp->getMainDeps()->at(2).getSubDeps(comp)->at(0).getSubDeps(comp)->size()<<endl;
cout<<"do we have loops in deps?    "<<comp->loop_IN_Deps()<<endl;//0
cout<<"................................TTTTTTTTTTTOODAAAAAAAAAAAAAAAAAY...................................................................."<<endl;
for(auto i=comp->EmpsOfAllCompany.begin();i!=comp->EmpsOfAllCompany.end();i++){
	cout<<"employee name "<<(*i).getName(comp)<<" | "<<(*i).getEmpId()<<endl;
}
cout<<".......----------------------------------------------------------------------------....................................................."<<endl;
comp->getMainDeps()->at(0).getSubDeps()->at(0).addEmpToDep(emp13);
cout << "****************************" <<comp->getMainDeps()->at(0).getSubDeps()->at(0).getEmpsOfDep(comp)->size()<< endl;
cout<<comp->getMainDeps()->at(0).getSubDeps()->at(0).getEmpsOfDep()->size()<<endl;
if(auto i=findEmployeeInDep(emp12,comp))
{
	cout<<(*i).getName(comp)<<endl;
}
if(auto i=findEmployeeInDep(emp13,comp))
{
	cout<<(*i).getName(comp)<<endl;
}
if(auto i=findEmployeeInDep(emp14,comp))
{
	cout<<(*i).getName(comp)<<endl;
}
if(auto i=findEmployeeInDep(emp15,comp))
{
	cout<<(*i).getName(comp)<<endl;
}
cout<<findEmployeeInCompany(emp13,comp)->getName()<<endl;
cout<<"......................................................................."<<endl;
cout<<comp->getMainDeps()->at(1).getDepName()<<endl;//emp12
cout<<comp->getMainDeps()->at(0).getSubDeps()->at(0).getDepName()<<endl;;//emp13
cout<<comp->getMainDeps()->at(0).getSubDeps()->at(0).getSubDeps()->at(0).getDepName()<<endl;//emp14
cout<<comp->getMainDeps()->at(0).getSubDeps()->at(0).getSubDeps()->at(1).getDepName()<<endl;//emp15
cout<<"...........................floating employees testing............................................"<<endl;

cout<<comp->floatingEmps()<<endl;
cout<<"................................26__9__2022..................................................................."<<endl;
for(auto i=comp->EmpsOfAllCompany.begin();i!=comp->EmpsOfAllCompany.end();i++){
	cout<<"employee name "<<(*i).getName(comp)<<" | "<<(*i).getEmpId()<<endl;
}
cout<<".......----------------------------------------------------------------------------....................................................."<<endl;
vector<Employee> emps=comp->allEmployees();
cout<<"Employees of deps are:"<<endl;
for(auto i=emps.begin();i!=emps.end();i++){
	cout<<"employee name "<<(*i).getName(comp)<<" | "<<(*i).getEmpId()<<endl;
}
cout<<".......----------------------------------------------------------------------------....................................................."<<endl;
TestFunctionToSeeAllTheCompanyDeps(comp);
// hereeeeeeeeeeeee         cout<<"size of sub deps  : "<<dep->getSubDeps()->size()<<endl;
			//cout<<"name of sub deps  : "<<dep->getSubDeps()->at(0).getDepName()<<endl;

cout<<"size of dep9 supDeps in company  : "<<comp->getMainDeps()->at(2).getSubDeps()->at(0).getSubDeps()->size()<<endl;
cout<<"do we have loops in deps?    "<<comp->loop_IN_Deps()<<endl;//1
//dep9.RemoveSubDep(dep6, comp);
cout<<"do we have loops in deps?    "<<comp->loop_IN_Deps()<<endl;//0
//dep1.removeEmpFromDep(emp10, comp);
//dep1.removeEmpFromDep(emp11, comp);
//cout<<"...............................................here..............................................."<<endl;
//cout<<dep1.getEmpsOfDep(comp)->size()<<endl;//0
//cout<<comp->getMainDeps()->at(0).getEmpsOfDep(comp)->size()<<endl;//0
//cout<<"...............................................here..............................................."<<endl;



//for(auto i=comp->getMainDeps()->at(0).getEmpsOfDep()->begin();i!=comp->getMainDeps()->at(0).getEmpsOfDep()->end();i++){
//
//	cout<<(*i).getName()<<endl;
//
//}
//cout<<comp->getMainDeps()->at(0).getEmpsOfDep().at(0).getName()<<endl;//emp10
//cout<<comp->getMainDeps()->at(0).getEmpsOfDep().at(1).getName()<<endl;//emp11

//.getDepName()<<endl;

	Company *comp=comp->getCompObject();
	Department dep1("backend dev",1);
	cout<<dep1.getDepName()<<"  "<<dep1.getDepNum()<<endl;
	Employee emp1("aseel",24,DEVELOPER,200000.0,12);
	Employee emp2("ahmad",24,DEVELOPER,2004.0,50);
	Employee emp3("ali",25,DEVELOPER,200004.0,500);
	Employee emp4("alosh",30,DEVELOPER,50000.0,1);
	Employee emp5("nore",28,HR,5010,111);
	Department dep2("backend dev sup1",50);
	Department dep3("backend dev sup2",51);
	Department dep4("frontend dev ",2);
	Department dep5("frontend dev sup",60);


	dep1.addEmpToDep(emp1);
	dep2.addEmpToDep(emp2);
	dep3.addEmpToDep(emp3);
	dep4.addEmpToDep(emp4);
	dep5.addEmpToDep(emp5);
	dep1.addSubDep(dep2);
	dep1.addSubDep(dep3);
	dep4.addSubDep(dep5);
	cout<<dep1.isAnySubDeps()<<endl;
	cout<<dep4.isAnySubDeps()<<endl;
	comp->addDepToCompany(dep1);
	comp->addDepToCompany(dep4);
	cout<<"------------------------------------------------------------------"<<endl;
	cout<<comp->allEmps.size()<<"  before allEmployees function callig "<<endl;
	vector<Employee> ALL=comp->allEmployees();
	cout<<ALL.size()<<endl;
    //int size=(int) comp->allEmps.size();
    cout<<comp->allEmps.size()<<"  after allEmployees function callig "<<endl;
    cout<<"------------------------------------------------------------------"<<endl;
    cout<<comp->getDeps().size()<<endl;
    for(auto i=comp->getDeps().begin();i!=comp->getDeps().end();i++){
       	cout<<"  "<<(*i).getDepName()<<"  "<<(*i).getDepNum()<<endl;
       }

    for(auto i=comp->getDeps().begin();i!=comp->getDeps().end();i++){
    	int j=0;
    	cout<<"  "<<comp->getDeps().at(j).getDepName()<<"  "<<(*i).getDepNum()<<endl;
    	//cout<<j<<endl
        j++;
    	cout<<j<<endl;
    }
	cout<<emp1.getAge()<<" "<<emp1.getEmpId()<<" "<<emp1.getSalary()<<" "<<emp1.getName()<<" "<<emp1.getRole()<<endl;
	cout << "Training project" << endl; // prints Training project
	*/
	//return 0;
//}
// inserting into a vector
/*
#include <iostream>
#include <vector>

int main ()
{
  std::vector<Employee> myvector ;
  std::vector<Employee>::iterator it;
  Employee emp1("aseel",24,DEVELOPER,200000.0,12);
  it = myvector.begin();
  it = myvector.insert ( it , emp1 );
  cout<<myvector.size()<<endl;
  //myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  //it = myvector.begin();
  Employee emp2("ahmad",24,DEVELOPER,2004.0,50);
  Employee emp3("ali",25,DEVELOPER,200004.0,500);
  std::vector<Employee> anothervector;
  cout<<anothervector.size()<<endl;
  anothervector.insert(anothervector.begin(),emp2);
  cout<<anothervector.size()<<endl;
  anothervector.insert(anothervector.begin(),emp3);
  cout<<anothervector.size()<<endl;//2
  //myvector.insert (myvector.end(),anothervector.begin(),anothervector.end());
  cout<<myvector.size()<<endl;
  cout<<anothervector.size()<<endl;
  vector<Department> emptySubdep={};
  Department dep1("first dep",1,emptySubdep,myvector);
  Department dep2("second dep",2,emptySubdep,anothervector);
  cout<<"department 1 supDeps size: "<<dep1.getSubDeps().size()<<endl;
  cout<<"department 1 empolyees size: "<<dep1.getEmpsOfDep().size()<<endl;
  cout<<"************************************************************"<<endl;
  cout<<"department 2 supDeps size: "<<dep2.getSubDeps().size()<<endl;
    cout<<"department 2 empolyees size: "<<dep2.getEmpsOfDep().size()<<endl;
    Company *EXALT=EXALT->getCompObject();
    cout<<"Exalt deps size: (before)   "<<EXALT->getDeps().size()<<endl;
    EXALT->addDepToCompany(dep1);
    EXALT->addDepToCompany(dep2);
    cout<<"************************************************************"<<endl;
    cout<<"Exalt deps size: (after)   "<<EXALT->getDeps().size()<<endl;
    cout<<"************************************************************"<<endl;
    cout<<"Exalt emps size of first dep: (after)   "<<EXALT->getDeps().at(0).getEmpsOfDep().size()<<endl;
    cout<<"Exalt emps size of second dep: (after)   "<<EXALT->getDeps().at(1).getEmpsOfDep().size()<<endl;
    cout<<EXALT->allEmps.size()<<endl;
   // EXALT->allEmps.insert(EXALT->allEmps.end(), anothervector.begin(),anothervector.end());//,EXALT->getDeps().at(0).getEmpsOfDep().end() );
    //cout<<dep2.getEmpsOfDep().at(0).getName()<<endl;
  //  cout<<myvector.begin();
    //vector<Employee> e1=dep2.getEmpsOfDep();
    //cout<<e1.at(0).getName()<<endl;
  //  EXALT->allEmps.insert(EXALT->allEmps.end(), e1.begin(),e1.end());
    //EXALT->allEmps.insert(EXALT->allEmps.end(), dep2.getEmpsOfDep().begin(),dep2.getEmpsOfDep().end());
    cout<<"size of EXALT->allEmps : "<<EXALT->allEmps.size()<<endl;
    Employee emp4("alosh",30,DEVELOPER,50000.0,1);
    Employee emp5("nore",28,HR,5010,111);
    Department dep3("first_sub1 dep",3);
    //Department dep4("first_sub2 dep",4);
    dep3.addEmpToDep(emp4);
    dep3.addEmpToDep(emp5);
    dep1.addSubDep(dep3);
    cout<<"************************************************************"<<endl;
    cout<<"dep1.subdep.size: "<<dep1.getSubDeps().size()<<endl;
    cout<<"dep1.subdep.emps.size: "<<dep1.getSubDeps().at(0).getEmpsOfDep().size()<<endl;
    cout<<"************************************************************  according to EXALT **************************************"<<endl;
    EXALT->getDeps().at(0).addSubDep(dep3);
    cout<<EXALT->getDeps().at(0).getSubDeps().at(0).getDepName()<<endl;
    //cout<<EXALT->getDeps().at(1).isAnySubDeps()<<endl;
   // EXALT->allEmployees();

    return 0;
}*/

void SetupComany(){
	cout<<"---------------------start of company setup-----------------------"<<endl;
	Company *comp=comp->getCompObject();
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
			Employee *emp1=Employee::Create("emp1",16,TESTER,1000);
		    Employee *emp2=Employee::Create("emp2",25,DEVELOPER,3000);
		    Employee *emp3=Employee::Create("emp3",24,MANAGER,2300);
		    Employee *emp4=Employee::Create("emp4",24,DEVELOPER,2300);
		    Employee *emp5=Employee::Create("emp5",24,TESTER,2350);
		    Employee *emp6=Employee::Create("emp6",24,DEVELOPER,2360);
		    Employee *emp7=Employee::Create("emp7",24,HR,6500);
		    Employee *emp8=Employee::Create("emp8",24,HR,600);
		    Employee *emp9=Employee::Create("emp9",29,TEAM_LEAD,600);
			Employee *emp11=Employee::Create("emp11", 10, MANAGER, 2000);
			Employee *emp10=Employee::Create("emp10",29,DEVELOPER,600);
			comp->addEmpToCompany(*emp10);
			comp->addEmpToCompany(*emp11);

			comp->addMainDepToCompany(*dep1);
			comp->addMainDepToCompany(*dep2);
			dep1->addSubDep(*dep3,comp);
			dep1->addSubDep(*dep4,comp);
			dep3->addSubDep(*dep5,comp);
			dep3->addSubDep(*dep6,comp);
			dep2->addSubDep(*dep7,comp);
			dep2->addSubDep(*dep8,comp);
			dep7->addSubDep(*dep9,comp);
			dep7->addSubDep(*dep10,comp);
			dep8->addSubDep(*dep10,comp);
			//----------------------------
			dep1->addEmpToDep(*emp1,comp);
			dep2->addEmpToDep(*emp2,comp);
			dep3->addEmpToDep(*emp3,comp);
			dep4->addEmpToDep(*emp4,comp);
			dep5->addEmpToDep(*emp5,comp);
			dep6->addEmpToDep(*emp6,comp);
			dep7->addEmpToDep(*emp7,comp);
			dep8->addEmpToDep(*emp8,comp);
			dep9->addEmpToDep(*emp9,comp);
			dep9->addEmpToDep(*emp5,comp);
			dep8->addEmpToDep(*emp1,comp);
			cout<<"---------------------end of company setup-----------------------"<<endl;
	}
class GetEmployeesOfDepartments: public httpserver::http_resource {
	public:
	Company *comp=comp->getCompObject();
    string employees;
		shared_ptr<httpserver::http_response> render_GET(const httpserver::http_request&) {
		    employees.clear();
	    	comp->allEmployees();

	    	for(int i=0;i<(int)comp->empsOfDeps.size();i++)
	    	{
	    		employees=employees+comp->empsOfDeps.at(i).getName()+" , ";
	    	}
			return shared_ptr<httpserver::http_response>(new httpserver::string_response(employees));
		}
};

class AddMainDepartmentToCompany: public httpserver::http_resource {
	public:
		Company *comp=comp->getCompObject();
		shared_ptr<httpserver::http_response> render_PUT(const httpserver::http_request& req){//
			Department newDep(req.get_arg("name"));
			comp->addMainDepToCompany(newDep);
			return shared_ptr<httpserver::http_response>(new httpserver::string_response("Department added to company : "+ req.get_arg("name")));
		}
};
class DeleteDepartmentfromCompany: public httpserver::http_resource {
	public:
		Company *comp=comp->getCompObject();
		shared_ptr<httpserver::http_response> render_DELETE(const httpserver::http_request& req) {
			cout<<"----------------------------------------------------"<<endl;
			comp->removeMainDepFromCompany(req.get_arg("name"));
			return shared_ptr<httpserver::http_response>(new httpserver::string_response("Main Department removed from company! :"+req.get_arg("name")));
		}
};
class companyTest : public ::testing::Test
{	public:
	Company *comp=comp->getCompObject();
};
TEST_F(companyTest, empsOfDeps_Test) {
	comp->allEmployees();
	EXPECT_EQ( 9,(int)comp->empsOfDeps.size());
	}
TEST_F(companyTest, empsWithSameSalaryTest) {
	EXPECT_EQ( 5,(int) comp->empsWithSameSalary().size());
}
TEST_F(companyTest, empsOfMultiDepsTest) {
	comp->empsOfMultiDeps();
	EXPECT_EQ( 2 ,(int)comp->empsOfMultiDeps_Results.size());
	}
TEST_F(companyTest, loop_IN_Deps_Test) {
	ASSERT_TRUE(comp->loop_IN_Deps());
	}
TEST_F(companyTest, floatingEmpsTest) {
	comp->floatingEmps();
	EXPECT_EQ( 2,(int)comp->listOfFloatingEmps.size());
}

int main ()
{
	SetupComany();
	httpserver::webserver ws = httpserver::create_webserver(8094);
	GetEmployeesOfDepartments EmpOfDeps;
	ws.register_resource("/GetEmployeesOfDepartments", &EmpOfDeps);
	AddMainDepartmentToCompany depTocomp;
	ws.register_resource("/AddMainDepartmentToCompany", &depTocomp);
	DeleteDepartmentfromCompany deletedep;
	ws.register_resource("/DeleteDepartmentfromCompany", &deletedep);
	// ws.start(true);
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS( ) ;

}

