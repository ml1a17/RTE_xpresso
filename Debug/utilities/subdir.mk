################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

OBJS += \
./utilities/fsl_debug_console.o 

C_DEPS += \
./utilities/fsl_debug_console.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCR_INTEGER_PRINTF -DSDK_DEBUGCONSOLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSDK_OS_FREE_RTOS -DFSL_RTOS_FREE_RTOS -DCPU_MKW41Z512VHT4 -DCPU_MKW41Z512VHT4_cm0plus -D__REDLIB__ -I"C:\Users\lmkqwe\Documents\MCUXpressoIDE_10.0.2_411\workspace\flash\source" -I"C:\Users\lmkqwe\Documents\MCUXpressoIDE_10.0.2_411\workspace\flash" -I"C:\Users\lmkqwe\Documents\MCUXpressoIDE_10.0.2_411\workspace\flash\CMSIS" -I"C:\Users\lmkqwe\Documents\MCUXpressoIDE_10.0.2_411\workspace\flash\freertos" -I"C:\Users\lmkqwe\Documents\MCUXpressoIDE_10.0.2_411\workspace\flash\drivers" -I"C:\Users\lmkqwe\Documents\MCUXpressoIDE_10.0.2_411\workspace\flash\utilities" -I"C:\Users\lmkqwe\Documents\MCUXpressoIDE_10.0.2_411\workspace\flash\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


