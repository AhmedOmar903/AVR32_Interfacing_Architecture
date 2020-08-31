################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../DIO_program.c \
../GIE_program.c \
../HOME_PAGE.c \
../ISR.c \
../LCD_program.c \
../TIMER1_program.c \
../UART_program.c \
../intialization.c \
../main.c 

OBJS += \
./ADC_program.o \
./DIO_program.o \
./GIE_program.o \
./HOME_PAGE.o \
./ISR.o \
./LCD_program.o \
./TIMER1_program.o \
./UART_program.o \
./intialization.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./DIO_program.d \
./GIE_program.d \
./HOME_PAGE.d \
./ISR.d \
./LCD_program.d \
./TIMER1_program.d \
./UART_program.d \
./intialization.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


