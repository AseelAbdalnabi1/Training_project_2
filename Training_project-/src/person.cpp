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

Person::Person(string Name,float Age){
this->Name= Name;
this->Age=Age;
}
string Person::getName(){
return this->Name;
}
void Person::setName(string Name){
this->Name=Name;
}
float Person::getAge(){
return this->Age;
}
void Person::setAge(float Age){
this->Age=Age;
}
Person::~Person(){
}


