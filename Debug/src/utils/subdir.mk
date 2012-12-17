################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/utils/Collision.cpp \
../src/utils/controls.cpp \
../src/utils/shader.cpp 

OBJS += \
./src/utils/Collision.o \
./src/utils/controls.o \
./src/utils/shader.o 

CPP_DEPS += \
./src/utils/Collision.d \
./src/utils/controls.d \
./src/utils/shader.d 


# Each subdirectory must supply rules for building sources it contributes
src/utils/%.o: ../src/utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/bullet -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


