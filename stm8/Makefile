CC = sdcc
AR = sdar

CHIP = STM8S003

BUILD_DIR = ./build
SRC_DIR = ./STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/src
INC_DIR = ./STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/inc
DIST_DIR = ./$(CHIP)_stdlib

CFLAGS = -mstm8 -I$(INC_DIR) -D$(CHIP) -c
ARFLAGS = -rc

STDLIB_ZIP = ./en.stsw-stm8069.zip
OBJLIB = stm8s_stdlib.a

BUILD_ARTIFACTS = $(BUILD_DIR) ./STM8S_StdPeriph_Lib *.patch

SRC_FILES = stm8s_awu.c stm8s_beep.c stm8s_clk.c stm8s_exti.c stm8s_flash.c stm8s_gpio.c stm8s_i2c.c stm8s_itc.c stm8s_iwdg.c stm8s_rst.c stm8s_spi.c stm8s_tim1.c stm8s_wwdg.c

ifeq ($(CHIP), $(filter $(CHIP), STM8S105 STM8S005 STM8S103 STM8S003 STM8S903 STM8AF626x))
	SRC_FILES += stm8s_adc1.c
endif

ifeq ($(CHIP), $(filter $(CHIP), STM8S208 STM8S207 STM8S007 STM8AF52Ax STM8AF62Ax))
	SRC_FILES += stm8s_adc2.c
endif

ifeq ($(CHIP), $(filter $(CHIP), STM8S208 STM8AF52Ax))
	SRC_FILES += stm8s_can.c
endif

ifneq ($(CHIP), STM8S903)
	SRC_FILES += stm8s_tim2.c
endif

ifeq ($(CHIP), $(filter $(CHIP), STM8S208 STM8S207 STM8S007 STM8S105 STM8S005 STM8AF52Ax STM8AF62Ax STM8AF626x))
	SRC_FILES += stm8s_tim3.c
endif

ifneq ($(CHIP), STM8S903)
	SRC_FILES += stm8s_tim4.c
endif

ifeq ($(CHIP), STM8S903)
	SRC_FILES += stm8s_tim5.c stm8s_tim6.c
endif

ifeq ($(CHIP), $(filter $(CHIP), STM8S208 STM8S207 STM8S007 STM8S103 STM8S003 STM8S903 STM8AF52Ax STM8AF62Ax))
	SRC_FILES += stm8s_uart1.c
endif

ifeq ($(CHIP), $(filter $(CHIP), STM8S105 STM8S005 STM8AF626x))
	SRC_FILES += stm8s_uart2.c
endif

ifeq ($(CHIP), $(filter $(CHIP), STM8S208 STM8S207 STM8S007 STM8AF52Ax STM8AF62Ax))
	SRC_FILES += stm8s_uart3.c
endif

OBJ_FILES = $(SRC_FILES:%.c=%.rel)

all: prepare build dist clean 

build: $(OBJLIB)

dist: 
	[ -d ./dist ] || mkdir -p $(DIST_DIR)/lib
	mv -n $(SRC_DIR)/ $(DIST_DIR)/
	mv -n $(INC_DIR)/ $(DIST_DIR)/
	[ -d $(DIST_DIR)/inc ] && mv -n $(DIST_DIR)/inc $(DIST_DIR)/include
	mv -n $(OBJLIB) $(DIST_DIR)/lib/

unzip: $(STDLIB_ZIP)
	unzip $(STDLIB_ZIP)
	find ./STM8S_StdPeriph_Lib/Libraries/STM8S_StdPeriph_Driver/ -type f -exec chmod 664 {} \;

patch:
	wget --quiet https://raw.githubusercontent.com/gicking/STM8-SPL_SDCC_patch/master/STM8S_StdPeriph_Lib_V2.3.1_sdcc.patch
	patch -p0 < STM8S_StdPeriph_Lib_V2.3.1_sdcc.patch
	mv STM8S_StdPeriph_Lib/Project/STM8S_StdPeriph_Template/stm8s_conf.h $(INC_DIR)/stm8s_conf.h
	mv STM8S_StdPeriph_Lib/Project/STM8S_StdPeriph_Template/stm8s_it.h $(INC_DIR)/stm8s_it.h


prepare: unzip patch
	rm -rf $(DIST_DIR)
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_ARTIFACTS)

$(OBJLIB): $(addprefix $(BUILD_DIR)/, $(OBJ_FILES))
	$(AR) $(ARFLAGS) $(OBJLIB) $^

$(BUILD_DIR)/%.rel: $(SRC_DIR)/%.c
	$(CC) -o $@ $(CFLAGS) $^

$(SRC_DIR)/%.c:
	$(CC) -o $@ $(CFLAGS) $^

.PHONY: all unzip patch prepare clean build dist

.PRECIOUS: $(SRC_DIR)/%.c
