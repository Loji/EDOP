################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/renderable/scenery/map/Level.cpp \
../src/renderable/scenery/map/Terrain.cpp 

OBJS += \
./src/renderable/scenery/map/Level.o \
./src/renderable/scenery/map/Terrain.o 

CPP_DEPS += \
./src/renderable/scenery/map/Level.d \
./src/renderable/scenery/map/Terrain.d 


# Each subdirectory must supply rules for building sources it contributes
src/renderable/scenery/map/%.o: ../src/renderable/scenery/map/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/include/bullet -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


