TARGET = stm32f446xx

### Build Variables ###
# 0 = no debug, 1 = debug
DEBUG := 1

# path to directory for build files
BUILD_DIR = build

### C Sources, Defines, and Includes ###
C_INCLUDES := -Iinclude \
              -Istm32f446xx/include

C_SOURCES := src/*.c \
             stm32f446xx/src/*.c

C_DEFS := 

### Binaries ###
PREFIX = ./arm-none-eabi-toolchain/bin/arm-none-eabi-

CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

### MCU Options ###
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
ABI = -mfloat-abi=hard

MCU = $(CPU) $(FPU) $(ABI) -mthumb

### Compiler Flags ###
# optimization flags
OPT := -Os

# Notes:
# -Os: optimize for size

EXTRA_C_FLAGS := -fdata-sections \
			     -ffunction-sections \
				 -fno-common \
                 -W \
				 -Wall \
				 -Wextra \
				 -Werror \
				 -Wundef \
				 -Wshadow \
				 -Wdouble-promotion \
				 -Wformat-truncation \
				 -Wconversion

# Notes:
# -fdata-sections: places each global variable in its own linker section
# -ffunction-sections: places each function in its own linker section
# -fno-common: places uninitialized variables in .bss section
# These options allow the --gc-sections linker option to be used to reduce executable size

# generate debugger symbols and optimize for debugging if debug build
ifeq ($(DEBUG), 1)
    EXTRA_C_FLAGS += -g
    OPT += -Og
endif

C_FLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) $(EXTRA_C_FLAGS)

### Linker ###
LDSCRIPT = STM32F446XX_FLASH.ld

LIBS := -lc \
        -lgcc

EXTRA_LD_FLAGS := -nostartfiles \
                  -nostdlib \
				  --specs nano.specs \
				  -Wl,--gc-sections \
				  -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

# Notes:
# --specs nano.specs: use libc_nano (c standard library optimized for size) instead of libc
# --gc-sections: garbage collect unused sections

LD_FLAGS = -T $(LDSCRIPT) $(LIBS) $(EXTRA_LD_FLAGS)

### Get correct command for cleaning ###
ifeq ($(OS), Windows_NT)
    RM = del /f
else
    RM = rm -f
endif

### Build Targets ###
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin
	$(SZ) --format=GNU $<

# build .elf executable
$(BUILD_DIR)/$(TARGET).elf: $(C_SOURCES) $(BUILD_DIR)
	$(CC) $(C_SOURCES) $(C_FLAGS) $(LD_FLAGS) -o $@

# generate .hex file from .elf file
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(HEX) $< $@

# generate .bin file from .elf file
$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(BIN) $< $@

# make build directory if it doesn't already exist
$(BUILD_DIR):
	mkdir $@

clean:
	$(RM) $(BUILD_DIR)/$(TARGET).*
