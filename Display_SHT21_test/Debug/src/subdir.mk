################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/air.cpp \
../src/app_main.cpp \
../src/app_temp_control.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc11xx.cpp \
../src/lcd.cpp \
../src/pwm.cpp \
../src/temperature.cpp 

C_SRCS += \
../src/crp.c \
../src/timer32.c 

OBJS += \
./src/air.o \
./src/app_main.o \
./src/app_temp_control.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc11xx.o \
./src/crp.o \
./src/lcd.o \
./src/pwm.o \
./src/temperature.o \
./src/timer32.o 

C_DEPS += \
./src/crp.d \
./src/timer32.d 

CPP_DEPS += \
./src/air.d \
./src/app_main.d \
./src/app_temp_control.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc11xx.d \
./src/lcd.d \
./src/pwm.d \
./src/temperature.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DBCU_TYPE=10 -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSIS_CORE_LPC11xx -DCPP_USE_HEAP -D__LPC11XX__ -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\neuneu_software-arm-olli\Display_SHT21_test\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\neuneu_software-arm-olli\CMSIS_CORE_LPC11xx\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\neuneu_software-arm-olli\u8g_lib\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\Selfbus\software-arm-lib\sblib\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/cr_startup_lpc11xx.o: ../src/cr_startup_lpc11xx.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DBCU_TYPE=10 -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSIS_CORE_LPC11xx -DCPP_USE_HEAP -D__LPC11XX__ -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\neuneu_software-arm-olli\Display_SHT21_test\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\neuneu_software-arm-olli\CMSIS_CORE_LPC11xx\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\neuneu_software-arm-olli\u8g_lib\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\Selfbus\software-arm-lib\sblib\inc" -Os -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc11xx.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSIS_CORE_LPC11xx -DCPP_USE_HEAP -D__LPC11XX__ -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\neuneu_software-arm-olli\Display_SHT21_test\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\neuneu_software-arm-olli\CMSIS_CORE_LPC11xx\inc" -I"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\neuneu_software-arm-olli\u8g_lib\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


