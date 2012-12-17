################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/renderable/Entity.cpp \
../src/renderable/ModelSystem.cpp 

OBJS += \
./src/renderable/Entity.o \
./src/renderable/ModelSystem.o 

CPP_DEPS += \
./src/renderable/Entity.d \
./src/renderable/ModelSystem.d 


# Each subdirectory must supply rules for building sources it contributes
src/renderable/%.o: ../src/renderable/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/bullet -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


