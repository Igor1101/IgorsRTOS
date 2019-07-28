TARGET := app
PLATFORM ?= posix 
CC ?= gcc
RTOS_DEFS ?= 
ifeq ($(strip $(PLATFORM)),posix)
	LDFLAGS += -lrt
	RTOS_DEFS += -DPORT_POSIX
endif
# path
RTOS_PATH = $(abspath ./igorsrtos)
APP_PATH = $(abspath ./)
RTOS_SOURCE_PATH = $(RTOS_PATH)/source
RTOS_PORTS_PATH = $(RTOS_PATH)/ports
RTOS_INCLUDES_PATH = $(RTOS_PATH)/include
BUILD_DIR = $(APP_PATH)/build
# app sources
APP_SRC := main.c
# rtos sources to compile with app
APP_SRC += rtos.c
APP_SRC += tasks.c
APP_SRC += thread.c
APP_SRC += mutex.c
APP_SRC += $(strip $(PLATFORM)).c
# app includes
INCFLAGS +=-I$(APP_PATH)
# rtos includes
INCFLAGS += -I$(RTOS_PATH)
INCFLAGS += -I$(RTOS_INCLUDES_PATH)
CFLAGS = -c -g -Wall

# build
COBJS = $(patsubst %.c,%.o,$(APP_SRC))
# deps rules
.PHONY: all clean
# Path to directories containing application source 
vpath %.c $(APP_PATH):$(RTOS_SOURCE_PATH):$(RTOS_PORTS_PATH)


all: $(APP_SRC) $(COBJS) $(TARGET).elf 



%.o: %.c $(BUILD_DIR) 
	$(CC) $(CFLAGS)  $(RTOS_DEFS) $(INCFLAGS) -c $< -o $@
$(TARGET).elf: $(COBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(INCFLAGS)
clean:
	rm -rf *.o
$(BUILD_DIR):
	mkdir -p  $(BUILD_DIR)
