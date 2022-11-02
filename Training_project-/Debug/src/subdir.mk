################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Training_Project.cpp \
../src/ceo.cpp \
../src/company.cpp \
../src/department.cpp \
../src/developer.cpp \
../src/employee.cpp \
../src/hr.cpp \
../src/manager.cpp \
../src/person.cpp \
../src/team_lead.cpp \
../src/tester.cpp 

CPP_DEPS += \
./src/Training_Project.d \
./src/ceo.d \
./src/company.d \
./src/department.d \
./src/developer.d \
./src/employee.d \
./src/hr.d \
./src/manager.d \
./src/person.d \
./src/team_lead.d \
./src/tester.d 

OBJS += \
./src/Training_Project.o \
./src/ceo.o \
./src/company.o \
./src/department.o \
./src/developer.o \
./src/employee.o \
./src/hr.o \
./src/manager.o \
./src/person.o \
./src/team_lead.o \
./src/tester.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D_cplusplus=201103L -Isrc -Iheaders -I/usr/local/lib -I../usr/lib -I/usr/local/lib/libhttpserver -I/usr/local/include/httpserver -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Training_Project.d ./src/Training_Project.o ./src/ceo.d ./src/ceo.o ./src/company.d ./src/company.o ./src/department.d ./src/department.o ./src/developer.d ./src/developer.o ./src/employee.d ./src/employee.o ./src/hr.d ./src/hr.o ./src/manager.d ./src/manager.o ./src/person.d ./src/person.o ./src/team_lead.d ./src/team_lead.o ./src/tester.d ./src/tester.o

.PHONY: clean-src

