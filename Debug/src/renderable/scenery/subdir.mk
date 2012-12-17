################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/renderable/scenery/LightSystem.cpp 

OBJS += \
./src/renderable/scenery/LightSystem.o 

CPP_DEPS += \
./src/renderable/scenery/LightSystem.d 


# Each subdirectory must supply rules for building sources it contributes
src/renderable/scenery/%.o: ../src/renderable/scenery/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/bullet -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


