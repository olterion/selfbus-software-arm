################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/SHT2x.cpp 

OBJS += \
./src/SHT2x.o 

CPP_DEPS += \
./src/SHT2x.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_LPCOPEN -D__LPC11XX__ -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\software-arm-olli\SHT21_lib\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\software-arm-olli\CMSIS_CORE_LPC11xx\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\Selfbus\software-arm-lib\sblib\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


