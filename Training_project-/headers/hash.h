#include "company.h"
#include <list>
#include<bits/stdc++.h>
using namespace std;
#include <iostream>

class Hash
{
private:
 int BUCKET;//number of cells
 list<Employee> *table;//for collision handling -chaining
public:
 Hash(int BUCKET);
 void insertItem(Employee Emp);
 int hashFunction(int empSalary);
 vector<Employee> displayEmployeesWithSameSalary();
};
