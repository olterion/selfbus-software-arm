################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: CapacitiveSensor_Touch_test.axf

# Tool invocations
CapacitiveSensor_Touch_test.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"C:\Users\Olli\CloudStation\uC_Stuff\LPC_workspaces\LPC1115_Selfbus\CMSIS_CORE_LPC11xx\Debug" -L"C:\Users\Olli\CloudStation\uC_Stuff\Selfbus\software-arm-lib\sblib\Debug_BCU1" -Xlinker -Map="CapacitiveSensor_Touch_test.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "example-serial_Debug.ld" -o "CapacitiveSensor_Touch_test.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) CapacitiveSensor_Touch_test.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "CapacitiveSensor_Touch_test.axf"; # arm-none-eabi-objcopy -O binary "CapacitiveSensor_Touch_test.axf" "CapacitiveSensor_Touch_test.bin" ; checksum -p LPC1115_303 -d "CapacitiveSensor_Touch_test.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
