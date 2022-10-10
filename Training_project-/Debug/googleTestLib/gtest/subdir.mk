################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../googleTestLib/gtest/gtest-all.cc 

CC_DEPS += \
./googleTestLib/gtest/gtest-all.d 

OBJS += \
./googleTestLib/gtest/gtest-all.o 


# Each subdirectory must supply rules for building sources it contributes
googleTestLib/gtest/%.o: ../googleTestLib/gtest/%.cc googleTestLib/gtest/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D_cplusplus=201103L -Isrc -I"/home/aseel/Downloads/file of training project/Training_project-/googleTestLib" -Iheaders -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-googleTestLib-2f-gtest

clean-googleTestLib-2f-gtest:
	-$(RM) ./googleTestLib/gtest/gtest-all.d ./googleTestLib/gtest/gtest-all.o

.PHONY: clean-googleTestLib-2f-gtest

