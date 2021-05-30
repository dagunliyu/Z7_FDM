################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/module/motion/planner.cpp \
../src/module/motion/stepper.cpp 

OBJS += \
./src/module/motion/planner.o \
./src/module/motion/stepper.o 

CPP_DEPS += \
./src/module/motion/planner.d \
./src/module/motion/stepper.d 


# Each subdirectory must supply rules for building sources it contributes
src/module/motion/%.o: ../src/module/motion/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../fdm_peek_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


