################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/module/temperature/temperature.cpp 

OBJS += \
./src/module/temperature/temperature.o 

CPP_DEPS += \
./src/module/temperature/temperature.d 


# Each subdirectory must supply rules for building sources it contributes
src/module/temperature/%.o: ../src/module/temperature/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../fdm_peek_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


