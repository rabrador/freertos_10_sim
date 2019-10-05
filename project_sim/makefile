PROJ_ROOT  := .
BUILD_TMP  := $(PROJ_ROOT)/tmp
TARGET_INC += -I$(PROJ_ROOT)/inc
TARGET_INC += -I$(PROJ_ROOT)/FreeRTOS_10/include
TARGET_INC += -I$(PROJ_ROOT)/FreeRTOS_10/portable/GCC/Posix 

CC         = gcc
RM         = rm -rf
OUTPUT     = freertos_sim

-include src/subdir.mk
-include FreeRTOS_10/subdir.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

all:freertos_sim.bin

freertos_sim.bin: $(OBJS)
	@echo 'Building target: $@'
	$(CC) -pthread -lrt -o"freertos_sim.bin" $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) $(OUTPUT).bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
