/*
 * person.cpp
 *
 *  Created on: Sep 8, 2022
 *      Author: aseel
 */
#include "../headers/person.h"
#include <iostream>
#include <string>
using namespace std;

Person::Person(string name,float age){
this->name= name;
this->age=age;
}
string Person::getName(){
return this->name;
}
void Person::setName(string name){
this->name=name;
}
float Person::getAge(){
return this->age;
}
void Person::setAge(float age){
this->age=age;
}
Person::~Person(){
}


