C_SRCS += \
$(PROJ_ROOT)/FreeRTOS_10/croutine.c \
$(PROJ_ROOT)/FreeRTOS_10/list.c \
$(PROJ_ROOT)/FreeRTOS_10/queue.c \
$(PROJ_ROOT)/FreeRTOS_10/tasks.c \
$(PROJ_ROOT)/FreeRTOS_10/timers.c \
$(PROJ_ROOT)/FreeRTOS_10/portable/GCC/Posix/port.c \
$(PROJ_ROOT)/FreeRTOS_10/portable/MemMang/heap_3.c 

OBJS += \
$(BUILD_TMP)/croutine.o \
$(BUILD_TMP)/list.o \
$(BUILD_TMP)/queue.o \
$(BUILD_TMP)/tasks.o \
$(BUILD_TMP)/timers.o \
$(BUILD_TMP)/port.o \
$(BUILD_TMP)/heap_3.o 

C_DEPS += \
$(BUILD_TMP)/croutine.d \
$(BUILD_TMP)/list.d \
$(BUILD_TMP)/queue.d \
$(BUILD_TMP)/tasks.d \
$(BUILD_TMP)/timers.d \
$(BUILD_TMP)/port.d \
$(BUILD_TMP)/heap_3.d 

$(BUILD_TMP)/%.o: $(PROJ_ROOT)/FreeRTOS_10/%.c
	@echo 'Building file: $<'
	gcc -DUSE_STDIO=1 -D__GCC_POSIX__=1 $(TARGET_INC) -O2 -Wall -c -fmessage-length=0 -pthread -lrt -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(BUILD_TMP)/%.o: $(PROJ_ROOT)/FreeRTOS_10/portable/GCC/Posix/%.c
	@echo 'Building file: $<'
	gcc -DUSE_STDIO=1 -D__GCC_POSIX__=1 $(TARGET_INC) -O2 -Wall -c -fmessage-length=0 -pthread -lrt -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(BUILD_TMP)/%.o: $(PROJ_ROOT)/FreeRTOS_10/portable/MemMang/%.c
	@echo 'Building file: $<'
	gcc -DUSE_STDIO=1 -D__GCC_POSIX__=1 $(TARGET_INC) -O2 -Wall -c -fmessage-length=0 -pthread -lrt -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
