################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libs/nozzle.cpp \
../src/libs/stopwatch.cpp 

OBJS += \
./src/libs/nozzle.o \
./src/libs/stopwatch.o 

CPP_DEPS += \
./src/libs/nozzle.d \
./src/libs/stopwatch.d 


# Each subdirectory must supply rules for building sources it contributes
src/libs/%.o: ../src/libs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../fdm_peek_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


