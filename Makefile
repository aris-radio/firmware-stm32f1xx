###############################################################################
# Project Version and Name
###############################################################################
VERSION          = v1.0.0
PROJECT          = arisr_firmware.$(VERSION)

###############################################################################
# Cross-Compilation Toolchain
###############################################################################
CC               = arm-none-eabi-gcc
CXX              = arm-none-eabi-g++
LD               = arm-none-eabi-ld
AR               = arm-none-eabi-ar
AS               = arm-none-eabi-as
OBJCOPY          = arm-none-eabi-objcopy
OBJDUMP          = arm-none-eabi-objdump
SIZE             = arm-none-eabi-size

###############################################################################
# Target and MCU Configuration
###############################################################################
CPU              = cortex-m3
MCU              = stm32f103xb
# Transform MCU to uppercase with placeholders, e.g., STM32F103XB
DMCU             = $(shell echo $(MCU) | sed 's/x/PLACEHOLDER/g' | tr '[:lower:]' '[:upper:]' | sed 's/PLACEHOLDER/x/g')

# Flash methods (uart, swd, usb, etc.)
FLASH            = uart
USB              = /dev/ttyUSB0
RATE             = 9600  # Lower baud rate to prevent errors

###############################################################################
# Directory Structure
###############################################################################
SRCDIR           = source
INCDIR           = include
BINDIR           = bin
OBJDIR           = obj
CMSIS_DIR        = cmsis
HAL_DIR          = hal

CMSIS_DEV_SRC    = $(CMSIS_DIR)/device/source
CMSIS_DEV_INC    = $(CMSIS_DIR)/device/include
CMSIS_INC        = $(CMSIS_DIR)/include
HAL_SRC          = $(HAL_DIR)/source
HAL_INC          = $(HAL_DIR)/include

###############################################################################
# Linker Script
###############################################################################
LDDIR            = $(CMSIS_DIR)/linker
LDSCRIPT         = $(LDDIR)/$(MCU)_flash.ld

###############################################################################
# Source Files: HAL and Main Project
###############################################################################
# HAL Sources
HAL_C_SOURCES    = $(wildcard $(HAL_SRC)/*.c)
HAL_OBJECTS      = $(patsubst $(HAL_SRC)/%.c, $(OBJDIR)/%.o, $(HAL_C_SOURCES))

# Main C and ASM Sources
APP_C_SOURCES    = $(wildcard $(SRCDIR)/*.c)
APP_S_SOURCES    = $(wildcard $(SRCDIR)/*.s)
APP_C_OBJECTS    = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(APP_C_SOURCES))
APP_S_OBJECTS    = $(patsubst $(SRCDIR)/%.s, $(OBJDIR)/%.o, $(APP_S_SOURCES))

# Combine all objects (except HAL library archive)
ALL_APP_OBJECTS  = $(APP_C_OBJECTS) $(APP_S_OBJECTS)

###############################################################################
# Include Paths
###############################################################################
INC              = -I$(CMSIS_INC) -I$(HAL_INC) -I$(CMSIS_DEV_INC) -I$(INCDIR)

###############################################################################
# Compiler/Assembler/Linker Flags
###############################################################################
CFLAGS           = -std=c99 -Wall -fno-common -mthumb -mcpu=$(CPU) -D$(DMCU) \
                   --specs=nosys.specs -g \
                   -Wa,-ahlms=$(OBJDIR)/$(notdir $(<:.c=.lst))
CFLAGS          += $(INC)

ASFLAGS          = -mcpu=$(CPU)

LFLAGS           = -T$(LDSCRIPT) -mthumb -mcpu=$(CPU) \
                   --specs=nano.specs --specs=nosys.specs -Wl,--gc-sections

RM               = rm -rf

###############################################################################
# Phony Targets
###############################################################################
.PHONY: all clean cleanall flash

###############################################################################
# Build Targets
###############################################################################
# "all" builds the startup file, .bin, and .hex
all: $(SRCDIR)/startup_$(MCU).s $(BINDIR)/$(PROJECT).bin $(BINDIR)/$(PROJECT).hex

# 1) .bin from .elf (removing unused sections)
$(BINDIR)/$(PROJECT).bin: $(BINDIR)/$(PROJECT).elf
	@echo "Generating binary: $@"
	@mkdir -p $(dir $@)
	$(OBJCOPY) -R .stack --strip-unneeded -O binary $< $@

# 2) .hex from .elf
$(BINDIR)/$(PROJECT).hex: $(BINDIR)/$(PROJECT).elf
	@echo "Generating hex: $@"
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O ihex $< $@

# 3) Final .elf linking objects + HAL static library
$(BINDIR)/$(PROJECT).elf: $(ALL_APP_OBJECTS) $(OBJDIR)/hal.a
	@echo "Linking: $@"
	@mkdir -p $(dir $@)
	$(CC) $^ $(LFLAGS) -o $@
	@$(OBJDUMP) -D $@ > $(BINDIR)/$(PROJECT).lst
	@$(SIZE) $@

# 4) Create the HAL static library (hal.a)
$(OBJDIR)/hal.a: $(HAL_OBJECTS)
	@echo "Creating HAL static library: $@"
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

###############################################################################
# Pattern Rules to Compile Sources into obj/
###############################################################################
# Compile HAL .c -> obj/.o
$(OBJDIR)/%.o: $(HAL_SRC)/%.c
	@echo "Compiling HAL C source: $< -> $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile App .c -> obj/.o
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling App C source: $< -> $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble .s -> obj/.o
$(OBJDIR)/%.o: $(SRCDIR)/%.s
	@echo "Assembling ASM source: $< -> $@"
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

###############################################################################
# Retrieve the Correct Startup File for the MCU
###############################################################################
$(SRCDIR)/startup_$(MCU).s:
	@echo "Fetching startup file for MCU: $(MCU)"
	@cp $(CMSIS_DEV_SRC)/startup_$(MCU).s $@

###############################################################################
# Cleaning Targets
###############################################################################
clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJDIR)/*.o
	@$(RM) $(OBJDIR)/*.a
	@$(RM) $(OBJDIR)/*.lst

cleanall:
	@echo "Cleaning all build artifacts..."
	@$(RM) $(OBJDIR)
	@$(RM) $(BINDIR)
	@rm -f $(SRCDIR)/startup_$(MCU).s

###############################################################################
# Flash Target
###############################################################################
flash: $(BINDIR)/$(PROJECT).bin
ifeq ($(FLASH), uart)
	@echo "UART Bootloader protocol selected. Using stm32flash..."
	stm32flash -b $(RATE) -w $(BINDIR)/$(PROJECT).bin -v -g 0x08000000 $(USB)
else ifeq ($(FLASH), swd)
	@echo "SWD protocol selected. Using st-flash..."
	st-flash --reset write $(BINDIR)/$(PROJECT).bin 0x08000000
else ifeq ($(FLASH), usb)
	@echo "USB DFU protocol selected. Using dfu-util..."
	dfu-util -d 0483:df11 -a 0 -s 0x08000000:leave -D $(BINDIR)/$(PROJECT).bin
else
	@echo "Using generic STM32CubeProgrammer..."
	@echo "Please ensure STM32CubeProgrammer is in your PATH."
	STM32_Programmer_CLI -c port=$(USB) --serial_baudrate=$(RATE) --serial_parity=even \
	                     -w $(BINDIR)/$(PROJECT).bin 0x08000000 --verify -g 0x08000000
endif
