################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/lan8742/lan8742.c 

OBJS += \
./Drivers/BSP/lan8742/lan8742.o 

C_DEPS += \
./Drivers/BSP/lan8742/lan8742.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/lan8742/%.o Drivers/BSP/lan8742/%.su Drivers/BSP/lan8742/%.cyclo: ../Drivers/BSP/lan8742/%.c Drivers/BSP/lan8742/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g -DDEBUG -DUSE_HAL_DRIVER -DSTM32H563xx -c -I../Core/Inc -I"C:/CubeWorspace/LwIP_RTOS/Drivers/BSP/lan8742" -I"C:/CubeWorspace/LwIP_RTOS/Drivers/BSP" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/system" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP/src/include" -I"C:/CubeWorspace/LwIP_RTOS/Middlewares/Third_Party/LwIP" -I../Drivers/STM32H5xx_HAL_Driver/Inc -I../Drivers/STM32H5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H5xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-lan8742

clean-Drivers-2f-BSP-2f-lan8742:
	-$(RM) ./Drivers/BSP/lan8742/lan8742.cyclo ./Drivers/BSP/lan8742/lan8742.d ./Drivers/BSP/lan8742/lan8742.o ./Drivers/BSP/lan8742/lan8742.su

.PHONY: clean-Drivers-2f-BSP-2f-lan8742

