cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(Training_project)

add_executable(
	Training_project
	src/Training_Project.cpp
	src/ceo.cpp
	src/company.cpp
	src/department.cpp
	src/developer.cpp
	src/employee.cpp
	src/hr.cpp
	src/manger.cpp
	src/person.cpp
	src/team_lead.cpp
	src/tester.cpp
)
target_link_libraries(Training_project PUBLIC gtest)

target_link_libraries(Training_project PUBLIC httpserver)
