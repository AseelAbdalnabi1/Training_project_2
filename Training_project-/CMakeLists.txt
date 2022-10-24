cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(Training_project)

add_executable(
	Training_project
	src/Training_Project.cpp
	src/CEO.cpp
	src/company.cpp
	src/department.cpp
	src/DEVELOPER.cpp
	src/employee.cpp
	src/hash.cpp
	src/HR.cpp
	src/MANAGER.cpp
	src/person.cpp
	src/TEAM_LEAD.cpp
	src/TESTER.cpp
)
target_link_libraries(Training_project PUBLIC gtest)

target_link_libraries(Training_project PUBLIC httpserver)
