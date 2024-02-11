# Path to stlink folder for uploading code to board
STLINK=~/Embedded/stlink/build/Release/bin

# Put your source files here (*.c)
SRCS=main.c system_stm32f4xx.c

# Libraries source files, add ones that you intent to use
SRCS += stm32f4xx_ll_rcc.c
SRCS += stm32f4xx_ll_gpio.c
# SRCS += stm32f4xx_usart.c

# Binaries will be generated with this name (.elf, .bin, .hex)
PROJ_NAME=template

# Put your STM32F4 library code directory here, change YOURUSERNAME to yours
# STM_COMMON=/home/ibrahim/Embedded/STM32F4-Discovery
STM_COMMON=/home/ibrahim/Embedded/STM32F401RE-Nucleo

# Compiler settings. Only edit CFLAGS to include other header files.
CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

# Compiler flags
CFLAGS  = -g -O2 -Wall -Tstm32_flash.ld
CFLAGS += -DUSE_STDPERIPH_DRIVER
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS += -I.

# Include files from STM libraries
# CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/Include
# CFLAGS += -I$(STM_COMMON)/Libraries/CMSIS/ST/STM32F4xx/Include
# CFLAGS += -I$(STM_COMMON)/Libraries/STM32F4xx_StdPeriph_Driver/inc
# CFLAGS += -I$(STM_COMMON)/Utilities/STM32F4-Discovery
CFLAGS += -I$(STM_COMMON)/STM32F401RE-Nucleo/Drivers/CMSIS/Include
CFLAGS += -I$(STM_COMMON)/STM32F401RE-Nucleo/Drivers/CMSIS/Device/ST/STM32F4xx/Include
CFLAGS += -I$(STM_COMMON)/STM32F401RE-Nucleo/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates
CFLAGS += -I$(STM_COMMON)/STM32F401RE-Nucleo/Drivers/STM32F4xx_HAL_Driver/Inc
CFLAGS += -I$(STM_COMMON)/STM32F401RE-Nucleo/Drivers/BSP

# add startup file to build
SRCS += $(STM_COMMON)/STM32F401RE-Nucleo/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/arm/startup_stm32f401xe.s
OBJS = $(SRCS:.c=.o)

vpath %.c $(STM_COMMON)/STM32F401RE-Nucleo/Drivers/STM32F4xx_HAL_Driver/Src \

.PHONY: proj

# Commands
all: proj

proj: $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F4
burn: proj
	$(STLINK)/st-flash write $(PROJ_NAME).bin 0x8000000
