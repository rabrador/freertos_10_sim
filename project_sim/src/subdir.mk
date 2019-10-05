C_SRCS += $(PROJ_ROOT)/src/main.c 
C_SRCS += $(PROJ_ROOT)/src/cli_task.c
C_SRCS += $(PROJ_ROOT)/src/cmd_parser.c
C_SRCS += $(PROJ_ROOT)/src/cli_sys.c

OBJS += $(BUILD_TMP)/main.o 
OBJS += $(BUILD_TMP)/cli_task.o 
OBJS += $(BUILD_TMP)/cmd_parser.o 
OBJS += $(BUILD_TMP)/cli_sys.o 

C_DEPS += $(BUILD_TMP)/main.d 
C_DEPS += $(BUILD_TMP)/cli_task.d 
C_DEPS += $(BUILD_TMP)/cmd_parser.d 
C_DEPS += $(BUILD_TMP)/cli_sys.d 

# Each subdirectory must supply rules for building sources it contributes
$(BUILD_TMP)/%.o: $(PROJ_ROOT)/src/%.c
	@echo 'Building file: $<'
	$(CC) -DUSE_STDIO=1 -D__GCC_POSIX__=1 $(TARGET_INC) -O2 -Wall -c -fmessage-length=0 -pthread -lrt -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
