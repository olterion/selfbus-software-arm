################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/app_RGBswitch.cpp \
../src/app_main.cpp \
../src/cr_startup_lpc11xx.cpp \
../src/dimEncoder.cpp \
../src/dimmer.cpp \
../src/jalo.cpp \
../src/leds.cpp \
../src/switch.cpp 

OBJS += \
./src/app_RGBswitch.o \
./src/app_main.o \
./src/cr_startup_lpc11xx.o \
./src/dimEncoder.o \
./src/dimmer.o \
./src/jalo.o \
./src/leds.o \
./src/switch.o 

CPP_DEPS += \
./src/app_RGBswitch.d \
./src/app_main.d \
./src/cr_startup_lpc11xx.d \
./src/dimEncoder.d \
./src/dimmer.d \
./src/jalo.d \
./src/leds.d \
./src/switch.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DBCU_TYPE=10 -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSIS_CORE_LPC11xx -DCPP_USE_HEAP -D__LPC11XX__ -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\software-arm-olli\CMSIS_CORE_LPC11xx\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\Selfbus\software-arm-lib\sblib\inc" -O0 -g3 -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc11xx.o: ../src/cr_startup_lpc11xx.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DBCU_TYPE=10 -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSIS_CORE_LPC11xx -DCPP_USE_HEAP -D__LPC11XX__ -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\software-arm-olli\CMSIS_CORE_LPC11xx\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\Selfbus\software-arm-lib\sblib\inc" -Os -g3 -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc11xx.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


