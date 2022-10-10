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
	std::string Name;
	float Age;
public:
	Person(std::string Name,float Age);
	std::string getName();
	void setName(std::string Name);
	float getAge();
	void setAge(float Age);
	~Person();
};




#endif /* PERSON_H_ */
