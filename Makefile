VERSION = v1.0.0
PROJECT	= arisr_firmware.$(VERSION)

## Cross-compilation commands 
CC      = arm-none-eabi-gcc
CXX		= arm-none-eabi-g++
LD      = arm-none-eabi-ld
AR      = arm-none-eabi-ar
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE    = arm-none-eabi-size

# Project target
CPU	 = cortex-m3
MCU	 = stm32f103xb
DMCU =  $(shell echo $(MCU) | sed 's/x/PLACEHOLDER/g' | tr '[:lower:]' '[:upper:]' | sed 's/PLACEHOLDER/x/g')
FLASH = uart
USB   = /dev/ttyUSB0

# Lower to prevent errors
RATE  = 9600

# Project structure
SRCDIR			= source
INCDIR			= include
BINDIR			= bin
OBJDIR			= obj
CMSIS_DIR		= cmsis
HALDIR			= hal
CMSIS_DEV_SRC	= $(CMSIS_DIR)/device/source
CMSIS_DEV_INC	= $(CMSIS_DIR)/device/include
CMSIS_INC		= $(CMSIS_DIR)/include
HAL_DIR			= hal
HAL_SRC			= $(HAL_DIR)/source
HAL_INC			= $(HAL_DIR)/include

# Linker script
LDDIR		= $(CMSIS_DIR)/linker
LDSCRIPT	= $(LDDIR)/$(MCU)_flash.ld

# Core sources
HAL_OBJ_SRC			= $(wildcard $(HAL_SRC)/*.c)
HAL_LIB_OBJS		= $(HAL_OBJ_SRC:.c=.o)
HAL_LOCAL_LIB_OBJS	= $(notdir $(HAL_LIB_OBJS))

# Program sources
OBJ_SRC		 	= $(wildcard $(SRCDIR)/*.c) 
OBJ_ASM		 	= $(wildcard $(SRCDIR)/*.s)
LOCAL_LIB_OBJS	= $(notdir $(OBJ_SRC:.c=.o)) 
LOCAL_LIB_ASM	= $(notdir $(OBJ_ASM:.s=.o))
LIB_OBJS	 	= $(addprefix $(OBJDIR)/,$(LOCAL_LIB_OBJS))
LIB_OBJS		+= $(addprefix $(OBJDIR)/,$(LOCAL_LIB_ASM))

# Include paths
INC		= -I$(CMSIS_INC) -I$(HAL_INC) -I$(CMSIS_DEV_INC) -I$(INCDIR)

# Build Arguments
CFLAGS		 = -std=c99 -Wall -fno-common -mthumb -mcpu=$(CPU) -D$(DMCU) --specs=nosys.specs -g -Wa,-ahlms=$(addprefix $(OBJDIR)/,$(notdir $(<:.c=.lst)))
CFLAGS		 += $(INC)
ASFLAGS		 = -mcpu=$(CPU)
LFLAGS		 = -T$(LDSCRIPT) -mthumb -mcpu=$(CPU) --specs=nano.specs --specs=nosys.specs -Wl,--gc-sections

RM	= rm -rf

# Targets

all:: $(SRCDIR)/startup_$(MCU).s $(BINDIR)/$(PROJECT).bin $(BINDIR)/$(PROJECT).hex 

$(BINDIR)/$(PROJECT).bin: $(BINDIR)/$(PROJECT).elf
	$(OBJCOPY) -R .stack --strip-unneeded -O binary $< $@

$(BINDIR)/$(PROJECT).hex: $(BINDIR)/$(PROJECT).elf
	$(OBJCOPY) -O ihex $< $@

$(BINDIR)/$(PROJECT).elf: $(LIB_OBJS) $(OBJDIR)/hal.a 
	@echo "Creating $(PROJECT).elf"
	@mkdir -p $(dir $@)
	$(CC)  $^ $(LFLAGS) -o $(BINDIR)/$(PROJECT).elf
	$(OBJDUMP) -D $(BINDIR)/$(PROJECT).elf > $(BINDIR)/$(PROJECT).lst
	$(SIZE) $(BINDIR)/$(PROJECT).elf

$(OBJDIR)/hal.a: $(HAL_OBJ_SRC)
	@echo "Creating core lib (hal.a)"
	@mkdir -p $(dir $@)
	$(CC) $(HAL_OBJ_SRC) $(CFLAGS) -c 
	$(AR) rcs $@ $(HAL_LOCAL_LIB_OBJS)
	@rm -f $(HAL_LOCAL_LIB_OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling c source files in src"
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.s
	@echo "Compiling asm files in src"
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

# Move target MCU startup to project directory
$(SRCDIR)/startup_$(MCU).s:
	@echo "Getting asm source for MCU $(MCU)"
	@cp $(CMSIS_DEV_SRC)/startup_$(MCU).s $@


clean:
	@rm -rf $(OBJDIR)/*.o
	@rm -f  $(HAL_LOCAL_LIB_OBJS)

cleanall:
	@rm -rf $(OBJDIR)/*
	@rm -f  $(BINDIR)/*
	@rm -rf $(OBJDIR) $(BINDIR)
	@rm -f  $(HAL_LOCAL_LIB_OBJS)
	@rm -f  $(SRCDIR)/startup_$(MCU).s

# If $(FLASH) is set to uart, use st32flash to flash the target
flash: $(BINDIR)/$(PROJECT).bin
ifeq ($(FLASH), uart)
	@echo "UART Bootloader protocol selected. Using stm32flash."
	@stm32flash -b $(RATE) -w $(BINDIR)/$(PROJECT).bin -v -g 0x08000000 $(USB)

# else if $(FLASH) is set to swd, use st-flash to flash the target
else ifeq ($(FLASH), swd)
	@echo "SWD Bootloader protocol selected. Using st-flash."
	@st-flash --reset write $(BINDIR)/$(PROJECT).bin 0x08000000

else ifeq ($(FLASH), usb)
	@echo "USB Bootloader protocol selected. Using dfu-util."
	@dfu-util -d 0483:df11 -a 0 -s 0x08000000:leave -D $(BINDIR)/$(PROJECT).bin

# else use STM32CubeProgrammer to flash the target
else
	@echo "Using generic flasher STM32CubeProgrammer"
	@echo "Please make sure STM32CubeProgrammer is installed and in PATH"
	@STM32_Programmer_CLI -c port=$(USB) --serial_baudrate=$(RATE) --serial_parity=even -w $(BINDIR)/$(PROJECT).bin 0x08000000 --verify -g 0x08000000

endif
