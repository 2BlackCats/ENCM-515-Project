################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/stm32f411e/Components/lsm303agr/lsm303agr.c 

OBJS += \
./Drivers/stm32f411e/Components/lsm303agr/lsm303agr.o 

C_DEPS += \
./Drivers/stm32f411e/Components/lsm303agr/lsm303agr.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/stm32f411e/Components/lsm303agr/%.o Drivers/stm32f411e/Components/lsm303agr/%.su Drivers/stm32f411e/Components/lsm303agr/%.cyclo: ../Drivers/stm32f411e/Components/lsm303agr/%.c Drivers/stm32f411e/Components/lsm303agr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"C:/Users/julie/school/3rd/encm515/lab_materials_2025/final_proj/ENCM-515-Project/part1/Drivers/stm32f411e/Inc" -I"C:/Users/julie/school/3rd/encm515/lab_materials_2025/final_proj/ENCM-515-Project/part1/Drivers/CMSIS/DSP/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../PDM2PCM/App -I../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-stm32f411e-2f-Components-2f-lsm303agr

clean-Drivers-2f-stm32f411e-2f-Components-2f-lsm303agr:
	-$(RM) ./Drivers/stm32f411e/Components/lsm303agr/lsm303agr.cyclo ./Drivers/stm32f411e/Components/lsm303agr/lsm303agr.d ./Drivers/stm32f411e/Components/lsm303agr/lsm303agr.o ./Drivers/stm32f411e/Components/lsm303agr/lsm303agr.su

.PHONY: clean-Drivers-2f-stm32f411e-2f-Components-2f-lsm303agr

