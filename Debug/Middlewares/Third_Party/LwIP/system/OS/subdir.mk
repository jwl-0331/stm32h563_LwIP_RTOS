################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/system/OS/sys_arch.c 

OBJS += \
./Middlewares/Third_Party/LwIP/system/OS/sys_arch.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/system/OS/sys_arch.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/system/OS/%.o Middlewares/Third_Party/LwIP/system/OS/%.su Middlewares/Third_Party/LwIP/system/OS/%.cyclo: ../Middlewares/Third_Party/LwIP/system/OS/%.c Middlewares/Third_Party/LwIP/system/OS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/system" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/system/arch" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/src/include" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/src/netif/ppp" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/src/include/compat/posix/net" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/src/include/compat/posix/sys" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/src/include/compat/posix" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/src/include/compat/stdc" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/system/arch" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-system-2f-OS

clean-Middlewares-2f-Third_Party-2f-LwIP-2f-system-2f-OS:
	-$(RM) ./Middlewares/Third_Party/LwIP/system/OS/sys_arch.cyclo ./Middlewares/Third_Party/LwIP/system/OS/sys_arch.d ./Middlewares/Third_Party/LwIP/system/OS/sys_arch.o ./Middlewares/Third_Party/LwIP/system/OS/sys_arch.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-LwIP-2f-system-2f-OS

