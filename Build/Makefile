# ******************************************************************************************
#   Filename    : Makefile
#
#   Author      : Chalandi Amine
#
#   Owner       : Chalandi Amine
#
#   Date        : 22.11.2022
#
#   Description : Build system
#
# ******************************************************************************************

############################################################################################
# Defines
############################################################################################
CORE_FAMILY_LOWER_CASE = $(shell echo $(CORE_FAMILY) | tr '[:upper:]' '[:lower:]' | sed 's/[^a-z]//g')
PRJ_NAME    = $(CORE_FAMILY_LOWER_CASE)_baremetal_pico2_dual_core_nosdk
OUTPUT_DIR  = ../Output
OBJ_DIR     = $(OUTPUT_DIR)/$(CORE_FAMILY_LOWER_CASE)_obj
LD_SCRIPT   = $(SRC_DIR)/Memory_Map.ld
PIO_OUT_DIR = $(SRC_DIR)/pio
SRC_DIR     = ../Code
RTOS        = osek

ifeq ($(OS),Windows_NT)
    PYTHON     = python
    PICOTOOL   = ../Tools/picotool/picotool
    PIOASM     = ../Tools/pioasm/pioasm
else
    PYTHON     = python3
    PICOTOOL   = ../Tools/picotool/picotool_linux
    PIOASM     = ../Tools/pioasm/pioasm
endif

ERR_MSG_FORMATER_SCRIPT = ../Tools/scripts/CompilerErrorFormater.py

############################################################################################
# Toolchain
############################################################################################

ifeq ($(CORE_FAMILY), RISC-V)
    TOOLCHAIN          = riscv32-unknown-elf
    ARCH               = -march=rv32imac_zicsr_zifencei_zba_zbb_zbs_zbkb -mabi=ilp32
    DEFS               = -DCORE_FAMILY_RISC_V -msmall-data-limit=0 -falign-functions=4
    PICOTOOL_FAMILY_ID = rp2350-riscv
else ifeq ($(CORE_FAMILY), ARM)
    TOOLCHAIN          = arm-none-eabi
    ARCH               = -mcpu=cortex-m33 -mthumb -march=armv8-m.main+fp+dsp -mfloat-abi=softfp
    DEFS               = -DCORE_FAMILY_ARM
    PICOTOOL_FAMILY_ID = rp2350-arm-s
else
    TOOLCHAIN          =
    ARCH               =
    ARCH               =
    PICOTOOL_FAMILY_ID = 
endif

AS      = $(TOOLCHAIN)-gcc
CC      = $(TOOLCHAIN)-gcc
CPP     = $(TOOLCHAIN)-g++
LD      = $(TOOLCHAIN)-gcc
OBJDUMP = $(TOOLCHAIN)-objdump
OBJCOPY = $(TOOLCHAIN)-objcopy
READELF = $(TOOLCHAIN)-readelf

############################################################################################
# Optimization Compiler flags
############################################################################################

OPT_MODIFIED_O2 = -O2                               \
                  -fno-reorder-blocks-and-partition \
                  -fno-reorder-functions

NO_OPT = -O0

OPT = $(NO_OPT)

############################################################################################
# GCC Compiler verbose flags
############################################################################################

VERBOSE_GCC = -frecord-gcc-switches -fverbose-asm

############################################################################################
# C Compiler flags
############################################################################################

COPS  = $(OPT)                                        \
        $(ARCH)                                       \
        $(DEFS)                                       \
        -MD                                           \
        -Wa,-adhln=$(OBJ_DIR)/$(basename $(@F)).lst   \
        -g3                                           \
        -Wconversion                                  \
        -Wsign-conversion                             \
        -Wunused-parameter                            \
        -Wuninitialized                               \
        -Wmissing-declarations                        \
        -Wshadow                                      \
        -Wunreachable-code                            \
        -Wmissing-include-dirs                        \
        -x c                                          \
        -std=c11                                      \
        -Wall                                         \
        -Wextra                                       \
        -fomit-frame-pointer                          \
        -gdwarf-2                                     \
        -fno-exceptions

############################################################################################
# C++ Compiler flags
############################################################################################

CPPOPS  = $(OPT)                                        \
          $(ARCH)                                       \
          $(DEFS)                                       \
          -Wa,-adhln=$(OBJ_DIR)/$(basename $(@F)).lst   \
          -g3                                           \
          -Wconversion                                  \
          -Wsign-conversion                             \
          -Wunused-parameter                            \
          -Wuninitialized                               \
          -Wmissing-declarations                        \
          -Wshadow                                      \
          -Wunreachable-code                            \
          -Wmissing-include-dirs                        \
          -Wall                                         \
          -Wextra                                       \
          -fomit-frame-pointer                          \
          -gdwarf-2                                     \
          -fno-exceptions                               \
          -x c++                                        \
          -fno-rtti                                     \
          -fno-use-cxa-atexit                           \
          -fno-nonansi-builtins                         \
          -fno-threadsafe-statics                       \
          -fno-enforce-eh-specs                         \
          -ftemplate-depth=128                          \
          -Wzero-as-null-pointer-constant

############################################################################################
# Assembler flags
############################################################################################
ifeq ($(AS), $(TOOLCHAIN)-as)
  ASOPS =  $(ARCH)       \
           -alh          \
           -g
else
  ASOPS = $(OPT)                                        \
          $(ARCH)                                       \
          $(DEFS)                                       \
          -MD                                           \
          -Wa,-adhln=$(OBJ_DIR)/$(basename $(@F)).lst   \
          -g3                                           \
          -Wconversion                                  \
          -Wsign-conversion                             \
          -Wunused-parameter                            \
          -Wuninitialized                               \
          -Wmissing-declarations                        \
          -Wshadow                                      \
          -Wunreachable-code                            \
          -Wmissing-include-dirs                        \
          -x assembler                                  \
          -std=c11                                      \
          -Wall                                         \
          -Wextra                                       \
          -fomit-frame-pointer                          \
          -gdwarf-2                                     \
          -fno-exceptions
endif

############################################################################################
# Linker flags
############################################################################################

ifeq ($(LD), $(TOOLCHAIN)-ld)
  LOPS = -nostartfiles                          \
         -nostdlib                              \
         $(ARCH)                                \
         $(DEFS)                                \
         -e Startup_Init                        \
         --print-memory-usage                   \
         --print-map                            \
         -dT $(LD_SCRIPT)                       \
         -Map=$(OUTPUT_DIR)/$(PRJ_NAME).map     \
         --no-warn-rwx-segments                 \
         -z,max-page-size=4096                  \
         --specs=nano.specs                     \
         --specs=nosys.specs
else
  LOPS = -nostartfiles                          \
         -nostdlib                              \
         $(ARCH)                                \
         $(DEFS)                                \
         -e Startup_Init                        \
         -Wl,--print-memory-usage               \
         -Wl,--print-map                        \
         -Wl,-dT $(LD_SCRIPT)                   \
         -Wl,-Map=$(OUTPUT_DIR)/$(PRJ_NAME).map \
         -Wl,--no-warn-rwx-segments             \
         -Wl,-z,max-page-size=4096              \
         --specs=nano.specs                     \
         --specs=nosys.specs
endif

############################################################################################
# Source Files
############################################################################################

SRC_FILES := $(SRC_DIR)/Appli/main.c                                         \
             $(SRC_DIR)/Mcal/Clock/Clock.c                                   \
             $(SRC_DIR)/Mcal/Cpu/Cpu.c                                       \
             $(SRC_DIR)/Mcal/SysTickTimer/SysTickTimer.c                     \
             $(SRC_DIR)/Startup/Startup.c                                    \
             $(SRC_DIR)/Startup/Core/$(CORE_FAMILY)/image_definition_block.c \
             $(SRC_DIR)/Startup/Core/$(CORE_FAMILY)/boot.s                   \
             $(SRC_DIR)/Startup/Core/$(CORE_FAMILY)/IntVect.c                \
             $(SRC_DIR)/Startup/Core/$(CORE_FAMILY)/util.s


PIO_SRC_FILES :=

############################################################################################
# Include Paths
############################################################################################
INC_FILES := $(SRC_DIR)                             \
             $(SRC_DIR)/Appli                       \
             $(SRC_DIR)/Mcal                        \
             $(SRC_DIR)/Mcal/Clock                  \
             $(SRC_DIR)/Mcal/Cmsis                  \
             $(SRC_DIR)/Mcal/Cmsis/m-profile        \
             $(SRC_DIR)/Mcal/Cpu                    \
             $(SRC_DIR)/Mcal/Gpio                   \
             $(SRC_DIR)/Mcal/SysTickTimer           \
             $(SRC_DIR)/Mcal/USB                    \
             $(SRC_DIR)/Startup                     \
             $(SRC_DIR)/Startup/Core/$(CORE_FAMILY) \
             $(SRC_DIR)/Std


############################################################################################
# RTOS Files
############################################################################################
ifeq ($(RTOS),osek)
 include $(SRC_DIR)/OSEK/Os.makefile
 SRC_FILES += $(SRC_DIR)/Appli/tasks.c
endif

############################################################################################
# Rules
############################################################################################

VPATH := $(subst \,/,$(sort $(dir $(SRC_FILES)) $(OBJ_DIR) $(PIO_OUT_DIR) $(sort $(dir $(PIO_SRC_FILES)))))

FILES_O := $(addprefix $(OBJ_DIR)/, $(notdir $(addsuffix .o, $(basename $(SRC_FILES)))))

PIO_OUTPUT_FILES = $(addprefix $(PIO_OUT_DIR)/, $(notdir $(addsuffix .h, $(basename $(PIO_SRC_FILES)))))

ifeq ($(MAKECMDGOALS), BUILD_STAGE_2)
-include $(subst .o,.d,$(FILES_O))
endif

REBUILD_STAGE_1 : CLEAN PRE_BUILD PIO_SRC_GEN
REBUILD_STAGE_2 : link
REBUILD_STAGE_3 : GENERATE POST_BUILD

BUILD_STAGE_1   : PRE_BUILD PIO_SRC_GEN
BUILD_STAGE_2   : link
BUILD_STAGE_3   : GENERATE POST_BUILD

############################################################################################
# Recipes
############################################################################################
.PHONY : link
link : $(OUTPUT_DIR)/$(PRJ_NAME).elf
	@-echo "" > /dev/null


.PHONY : PRE_BUILD
PRE_BUILD:
	@$(if $(strip $(PICOTOOL_FAMILY_ID)), ,$(error Error: the Entered CORE_FAMILY is not supported!))
	@-echo +++ Building RP2350 baremetal image for $(CORE_FAMILY) core
	@git log -n 1 --decorate-refs=refs/heads/ --pretty=format:"+++ Git branch: %D (%h)" 2>/dev/null || true
	@git log -n 1 --clear-decorations 2> /dev/null > /dev/null || true
	@echo +++ info: "$(shell $(CC) -v 2>&1 | tail -n 1)"
	@echo +++ info: "$(shell make -v 2>&1 | head -n 1)"
	@$(if $(shell test -d $(OBJ_DIR) && echo yes),,mkdir -p $(subst \,/,$(OBJ_DIR)))

.PHONY : POST_BUILD
POST_BUILD:
	@-echo +++ End

.PHONY : PIO_SRC_GEN
PIO_SRC_GEN: $(PIO_OUTPUT_FILES)

$(PIO_OUT_DIR)/%.h : %.pio
	@-echo +++ compile pio assembly: $(subst \,/, $<) to $(subst \,/, $@)
	@$(PIOASM) -v 1  $<  $@

.PHONY : CLEAN
CLEAN :
	@-rm -rf $(OUTPUT_DIR) *.o    2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR) *.hex  2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR) *.elf  2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR) *.list 2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR) *.map  2>/dev/null || true
	@-rm -rf $(OUTPUT_DIR) *.txt  2>/dev/null || true
	@-mkdir -p $(subst \,/,$(OUTPUT_DIR))

$(OBJ_DIR)/%.o : %.c
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@-$(CC) $(COPS) $(addprefix -I, $(INC_FILES)) -c $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err
	@-$(PYTHON) $(ERR_MSG_FORMATER_SCRIPT) $(OBJ_DIR)/$(basename $(@F)).err -COLOR

ifeq ($(AS), $(TOOLCHAIN)-as)
$(OBJ_DIR)/%.o : %.s
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@$(AS) $(ASOPS) $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err >$(OBJ_DIR)/$(basename $(@F)).lst
	@-$(PYTHON) $(ERR_MSG_FORMATER_SCRIPT) $(OBJ_DIR)/$(basename $(@F)).err -COLOR
else
$(OBJ_DIR)/%.o : %.s
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@-$(AS) $(ASOPS) $(addprefix -I, $(INC_FILES)) -c $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err
	@-$(PYTHON) $(ERR_MSG_FORMATER_SCRIPT) $(OBJ_DIR)/$(basename $(@F)).err -COLOR
endif

$(OBJ_DIR)/%.o : %.cpp
	@-echo +++ compile: $(subst \,/,$<) to $(subst \,/,$@)
	@$(CPP) $(CPPOPS) $(addprefix -I, $(INC_FILES)) -c $< -o $(OBJ_DIR)/$(basename $(@F)).o 2> $(OBJ_DIR)/$(basename $(@F)).err
	@-$(PYTHON) $(ERR_MSG_FORMATER_SCRIPT) $(OBJ_DIR)/$(basename $(@F)).err -COLOR

$(OUTPUT_DIR)/$(PRJ_NAME).elf : $(FILES_O) $(LD_SCRIPT)
	@-echo +++ link: $(subst \,/,$@)
	@$(LD) $(LOPS) $(FILES_O) -o $(OUTPUT_DIR)/$(PRJ_NAME).elf


.PHONY : GENERATE
GENERATE:
	@$(if $(wildcard $(OUTPUT_DIR)/$(PRJ_NAME).elf), ,$(error Error: Link not succeeded !))
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).readelf
	@$(READELF) -WhS $(OUTPUT_DIR)/$(PRJ_NAME).elf > $(OUTPUT_DIR)/$(PRJ_NAME).readelf
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).sym
	@$(READELF) -Ws $(OUTPUT_DIR)/$(PRJ_NAME).elf > $(OUTPUT_DIR)/$(PRJ_NAME).sym
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).dis
	@$(OBJDUMP) -d --visualize-jumps --wide $(OUTPUT_DIR)/$(PRJ_NAME).elf > $(OUTPUT_DIR)/$(PRJ_NAME).dis
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).hex
	@$(OBJCOPY) $(OUTPUT_DIR)/$(PRJ_NAME).elf -O ihex $(OUTPUT_DIR)/$(PRJ_NAME).hex
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).bin
	@$(OBJCOPY) $(OUTPUT_DIR)/$(PRJ_NAME).elf -O binary $(OUTPUT_DIR)/$(PRJ_NAME).bin
	@-echo +++ generate: $(OUTPUT_DIR)/$(PRJ_NAME).uf2
	@$(PICOTOOL) uf2 convert --quiet $(OUTPUT_DIR)/$(PRJ_NAME).elf $(OUTPUT_DIR)/$(PRJ_NAME).uf2 --family $(PICOTOOL_FAMILY_ID) --abs-block
