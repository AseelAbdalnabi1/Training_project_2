/*
 * person.h
 *
 *  Created on: Sep 8, 2022
 *      Author: aseel
 */

#ifndef PERSON_H_
#define PERSON_H_
#include<string>
class Person{
private:
	std::string name;
	float age;
public:
	Person(std::string name,float age);
	std::string getName();
	void setName(std::string name);
	float getAge();
	void setAge(float age);
	~Person();
};




#endif /* PERSON_H_ */
