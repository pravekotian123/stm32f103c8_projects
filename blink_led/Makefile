# Path you your toolchain installation, leave empty if already in system PATH
TOOLCHAIN_ROOT =

# Path to the STM32 codebase, make sure to update the submodule to get the code
VENDOR_ROOT = ../STM32CubeF1/

###############################################################################

# Project specific
TARGET = main.elf
SRC_DIR = src/
INC_DIR = inc/

# Toolchain
CC = $(TOOLCHAIN_ROOT)arm-none-eabi-gcc
OBJCOPY = $(TOOLCHAIN_ROOT)arm-none-eabi-objcopy
DB = $(TOOLCHAIN_ROOT)arm-none-eabi-gdb

# Project sources
SRC_FILES = $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)*/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)*.s) $(wildcard $(SRC_DIR)*/*.s)
LD_SCRIPT = STM32F103C8TX_FLASH.ld

# Project includes
INCLUDES   = -I$(INC_DIR)
INCLUDES  += -I$(INC_DIR)hal/

# Vendor sources: Note that files in "Templates" are normally copied into project for customization,
# but that is not necessary for this simple project.
ASM_FILES += $(VENDOR_ROOT)Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/gcc/startup_stm32f103xb.s
SRC_FILES += $(VENDOR_ROOT)Drivers/CMSIS/Device/ST/STM32F1xx/Source/Templates/system_stm32f1xx.c
SRC_FILES += $(VENDOR_ROOT)Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
SRC_FILES += $(VENDOR_ROOT)Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c

# Vendor includes
INCLUDES += -I$(VENDOR_ROOT)Drivers/CMSIS/Core/Include
INCLUDES += -I$(VENDOR_ROOT)Drivers/CMSIS/Device/ST/STM32F1xx/Include
INCLUDES += -I$(VENDOR_ROOT)Drivers/STM32F1xx_HAL_Driver/Inc

# Compiler Flags
CFLAGS  = -Wall -Wextra -O0 -fno-common -ffunction-sections -fdata-sections -std=c99 -g
CFLAGS += -mcpu=cortex-m3 -mthumb -mlittle-endian -msoft-float -mfix-cortex-m3-ldrd
CFLAGS += -DSTM32F103xB
CFLAGS += $(INCLUDES)

# Linker Flags
LFLAGS = -Wl,--gc-sections -Wl,-T$(LD_SCRIPT) --specs=rdimon.specs

###############################################################################

# This does an in-source build. An out-of-source build that places all object
# files into a build directory would be a better solution, but the goal was to
# keep this file very simple.

CXX_OBJS = $(SRC_FILES:.c=.o)
ASM_OBJS = $(ASM_FILES:.s=.o)
ALL_OBJS = $(ASM_OBJS) $(CXX_OBJS)

.PHONY: clean gdb-server_stlink gdb-server_openocd gdb-client

all: $(TARGET)

# Compile
$(CXX_OBJS): %.o: %.c
$(ASM_OBJS): %.o: %.s
$(ALL_OBJS):
	@echo "[CC] $@"
	@$(CC) $(CFLAGS) -c $< -o $@

# Link
%.elf: $(ALL_OBJS)
	@echo "[LD] $@"
	@$(CC) $(CFLAGS) $(LFLAGS) $(ALL_OBJS) -o $@
	@$(OBJCOPY) -O ihex $(TARGET) $(PROJ_NAME).hex
	@$(OBJCOPY) -O binary $(TARGET) $(PROJ_NAME).bin
	@rm -f $(ALL_OBJS)

# Clean
clean:
	@rm *.bin *.hex -f $(ALL_OBJS) $(TARGET) 


