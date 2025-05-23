################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/stm32f411e/Src/stm32f411e_discovery.c \
../Drivers/stm32f411e/Src/stm32f411e_discovery_accelerometer.c \
../Drivers/stm32f411e/Src/stm32f411e_discovery_audio.c \
../Drivers/stm32f411e/Src/stm32f411e_discovery_gyroscope.c 

OBJS += \
./Drivers/stm32f411e/Src/stm32f411e_discovery.o \
./Drivers/stm32f411e/Src/stm32f411e_discovery_accelerometer.o \
./Drivers/stm32f411e/Src/stm32f411e_discovery_audio.o \
./Drivers/stm32f411e/Src/stm32f411e_discovery_gyroscope.o 

C_DEPS += \
./Drivers/stm32f411e/Src/stm32f411e_discovery.d \
./Drivers/stm32f411e/Src/stm32f411e_discovery_accelerometer.d \
./Drivers/stm32f411e/Src/stm32f411e_discovery_audio.d \
./Drivers/stm32f411e/Src/stm32f411e_discovery_gyroscope.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/stm32f411e/Src/%.o Drivers/stm32f411e/Src/%.su Drivers/stm32f411e/Src/%.cyclo: ../Drivers/stm32f411e/Src/%.c Drivers/stm32f411e/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"C:/Users/julie/school/3rd/encm515/lab_materials_2025/final_proj/ENCM-515-Project/part1/Drivers/stm32f411e/Inc" -I"C:/Users/julie/school/3rd/encm515/lab_materials_2025/final_proj/ENCM-515-Project/part1/Drivers/CMSIS/DSP/Include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../PDM2PCM/App -I../Middlewares/ST/STM32_Audio/Addons/PDM/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-stm32f411e-2f-Src

clean-Drivers-2f-stm32f411e-2f-Src:
	-$(RM) ./Drivers/stm32f411e/Src/stm32f411e_discovery.cyclo ./Drivers/stm32f411e/Src/stm32f411e_discovery.d ./Drivers/stm32f411e/Src/stm32f411e_discovery.o ./Drivers/stm32f411e/Src/stm32f411e_discovery.su ./Drivers/stm32f411e/Src/stm32f411e_discovery_accelerometer.cyclo ./Drivers/stm32f411e/Src/stm32f411e_discovery_accelerometer.d ./Drivers/stm32f411e/Src/stm32f411e_discovery_accelerometer.o ./Drivers/stm32f411e/Src/stm32f411e_discovery_accelerometer.su ./Drivers/stm32f411e/Src/stm32f411e_discovery_audio.cyclo ./Drivers/stm32f411e/Src/stm32f411e_discovery_audio.d ./Drivers/stm32f411e/Src/stm32f411e_discovery_audio.o ./Drivers/stm32f411e/Src/stm32f411e_discovery_audio.su ./Drivers/stm32f411e/Src/stm32f411e_discovery_gyroscope.cyclo ./Drivers/stm32f411e/Src/stm32f411e_discovery_gyroscope.d ./Drivers/stm32f411e/Src/stm32f411e_discovery_gyroscope.o ./Drivers/stm32f411e/Src/stm32f411e_discovery_gyroscope.su

.PHONY: clean-Drivers-2f-stm32f411e-2f-Src

