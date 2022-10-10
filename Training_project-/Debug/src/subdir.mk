################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CEO.cpp \
../src/DEVELOPER.cpp \
../src/HR.cpp \
../src/MANAGER.cpp \
../src/TEAM_LEAD.cpp \
../src/TESTER.cpp \
../src/Training_Project.cpp \
../src/company.cpp \
../src/department.cpp \
../src/employee.cpp \
../src/hash.cpp \
../src/person.cpp 

CPP_DEPS += \
./src/CEO.d \
./src/DEVELOPER.d \
./src/HR.d \
./src/MANAGER.d \
./src/TEAM_LEAD.d \
./src/TESTER.d \
./src/Training_Project.d \
./src/company.d \
./src/department.d \
./src/employee.d \
./src/hash.d \
./src/person.d 

OBJS += \
./src/CEO.o \
./src/DEVELOPER.o \
./src/HR.o \
./src/MANAGER.o \
./src/TEAM_LEAD.o \
./src/TESTER.o \
./src/Training_Project.o \
./src/company.o \
./src/department.o \
./src/employee.o \
./src/hash.o \
./src/person.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D_cplusplus=201103L -Isrc -Iheaders -I/usr/local/lib -I../usr/lib -I/usr/local/lib/libhttpserver -I/usr/local/include/httpserver -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/CEO.d ./src/CEO.o ./src/DEVELOPER.d ./src/DEVELOPER.o ./src/HR.d ./src/HR.o ./src/MANAGER.d ./src/MANAGER.o ./src/TEAM_LEAD.d ./src/TEAM_LEAD.o ./src/TESTER.d ./src/TESTER.o ./src/Training_Project.d ./src/Training_Project.o ./src/company.d ./src/company.o ./src/department.d ./src/department.o ./src/employee.d ./src/employee.o ./src/hash.d ./src/hash.o ./src/person.d ./src/person.o

.PHONY: clean-src

