GITHUB_TASKS 	?= 0
DEBUG 			?= 0

ARCH 		?= x86
PLATFORM 	?= windows
CC 			:= gcc
CXXFLAGS	?= -Wall -std=c99
TARGET_DIR 	:= ${CURDIR}/bin/$(PLATFORM)/$(ARCH)
TARGET 		:= 6502
RM			:= rm

INCLUDE := ${CURDIR}/include

SRC_DIR := ${CURDIR}/src
OBJ_DIR := ${CURDIR}/obj

ifeq ($(DEBUG), 1)
	CXXFLAGS += -O0
	DEFINES += -D _DEBUG
else
	CXXFLAGS += -O3	
endif
ifeq ($(PLATFORM),windows)
	TARGET := $(TARGET).exe
endif
ifeq ($(ARCH), x64)
	CXXFLAGS += -m64
else
	CXXFLAGS += -m32
endif

# https://stackoverflow.com/questions/714100/os-detecting-makefile
ifeq ($(OS),Windows_NT)
	RM := del /Q /S
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
        endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
    endif
endif

CPPFLAGS += -I$(INCLUDE)
LDFLAGS := $(DEFINES)

OBJ_FILES := $(subst $(SRC_DIR),$(OBJ_DIR),$(subst .c,.o,$(wildcard $(SRC_DIR)/*.c)))

.phony: clean
	
$(TARGET): $(OBJ_FILES)
	@echo Building $(@F)
	@$(CC)  $(CXXFLAGS) -o $(TARGET_DIR)/$@ $^
	@echo Build Successful!

$(OBJ_FILES): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	-@mkdir "$(@D)"
	@echo Compiling $(@F)
	@$(CC) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $< 
	@echo Compiled $(@F)

clean:
	@$(RM) "$(OBJ_DIR)\*"
	@$(RM) "$(TARGET_DIR)\*.exe"
	@echo Cleaned!