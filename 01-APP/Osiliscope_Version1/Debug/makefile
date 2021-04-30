################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
OSILISCOPE.lss \

FLASH_IMAGE += \
OSILISCOPE.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: OSILISCOPE.elf secondary-outputs

# Tool invocations
OSILISCOPE.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,OSILISCOPE.map -mmcu=atmega32 -o "OSILISCOPE.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

OSILISCOPE.lss: OSILISCOPE.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S OSILISCOPE.elf  >"OSILISCOPE.lss"
	@echo 'Finished building: $@'
	@echo ' '

OSILISCOPE.hex: OSILISCOPE.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex OSILISCOPE.elf  "OSILISCOPE.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: OSILISCOPE.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 OSILISCOPE.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: OSILISCOPE.elf
	@echo 'Invoking: AVRDude'
	D:\ARM_EMBEDED\IMT_ARM_Course\02- Tools\03- IMT SDK\IMT_SDK_Win_64\WinAVR\bin\avrdude -pm32 -cusbasp -Uflash:w:OSILISCOPE.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) OSILISCOPE.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
