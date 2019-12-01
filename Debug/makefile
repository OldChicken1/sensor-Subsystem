################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./client_cbs.obj" \
"./syscfg/ti_drivers_net_wifi_config.obj" \
"./syscfg/Board.obj" \
"./debug.obj" \
"./main_freertos.obj" \
"./mqtt_client_app.obj" \
"./mqtt_queue.obj" \
"./network_if.obj" \
"./pixy_main.obj" \
"./pixy_queue.obj" \
"./process_main.obj" \
"./readFromQueueThread.obj" \
"./sensors_queue.obj" \
"./sensors_state.obj" \
"./statisticsTask.obj" \
"./timer_pixy.obj" \
"./timer_pub.obj" \
"./uart_term.obj" \
"./ultraSonar_main.obj" \
"../CC3220SF_LAUNCHXL_FREERTOS.cmd" \
$(GEN_CMDS__FLAG) \
-l"ccs/m4/mqtt_release.a" \
-l"ccs/m4/slnetsock_release.a" \
-l"ccs/Release/slnetifwifi.a" \
-l"ti/display/lib/display.aem4" \
-l"ti/grlib/lib/ccs/m4/grlib.a" \
-l"third_party/spiffs/lib/ccs/m4/spiffs.a" \
-l"ti/drivers/lib/drivers_cc32xx.aem4" \
-l"third_party/fatfs/lib/ccs/m4/fatfs.a" \
-l"ccs/rtos/simplelink.a" \
-lfreertos_builds_CC3220SF_LAUNCHXL_release_ccs.lib \
-l"ti/devices/cc32xx/driverlib/ccs/Release/driverlib.a" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.out \

EXE_OUTPUTS__QUOTED += \
"mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.out" \

BIN_OUTPUTS += \
mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.bin \

BIN_OUTPUTS__QUOTED += \
"mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.bin" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.out"

dependents:
	-cd C:/Users/jiez/workspace_v9_2/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug && $(MAKE) all

# Tool invocations
mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) C:/Users/jiez/workspace_v9_2/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/freertos_builds_CC3220SF_LAUNCHXL_release_ccs.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=vfplib -me -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.map" -i"C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/net/mqtt/lib" -i"C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/net/lib" -i"C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/drivers/net/wifi/slnetif" -i"C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source" -i"C:/ti/simplelink_cc32xx_sdk_3_20_00_06/source/ti/drivers/net/wifi" -i"C:/Users/jiez/workspace_v9_2/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug" -i"C:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/lib" --diag_suppress=10063 --diag_wrap=off --display_error_number --warn_sections --xml_link_info="mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg_linkInfo.xml" --rom_model -o "mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.bin: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armhex"  -o "mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.bin" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(GEN_MISC_FILES__QUOTED)$(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "client_cbs.obj" "syscfg\ti_drivers_net_wifi_config.obj" "syscfg\Board.obj" "debug.obj" "main_freertos.obj" "mqtt_client_app.obj" "mqtt_queue.obj" "network_if.obj" "pixy_main.obj" "pixy_queue.obj" "process_main.obj" "readFromQueueThread.obj" "sensors_queue.obj" "sensors_state.obj" "statisticsTask.obj" "timer_pixy.obj" "timer_pub.obj" "uart_term.obj" "ultraSonar_main.obj" 
	-$(RM) "client_cbs.d" "syscfg\ti_drivers_net_wifi_config.d" "syscfg\Board.d" "debug.d" "main_freertos.d" "mqtt_client_app.d" "mqtt_queue.d" "network_if.d" "pixy_main.d" "pixy_queue.d" "process_main.d" "readFromQueueThread.d" "sensors_queue.d" "sensors_state.d" "statisticsTask.d" "timer_pixy.d" "timer_pub.d" "uart_term.d" "ultraSonar_main.d" 
	-$(RMDIR) $(GEN_MISC_DIRS__QUOTED)
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-C:/ti/ccs920/ccs/utils/tiobj2bin/tiobj2bin mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.out mqtt_client_CC3220SF_LAUNCHXL_freertos_ccs_syscfg.bin C:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armofd C:/ti/ccs920/ccs/tools/compiler/ti-cgt-arm_18.12.3.LTS/bin/armhex C:/ti/ccs920/ccs/utils/tiobj2bin/mkhex4bin
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
C:/Users/jiez/workspace_v9_2/freertos_builds_CC3220SF_LAUNCHXL_release_ccs/Debug/freertos_builds_CC3220SF_LAUNCHXL_release_ccs.lib:

-include ../makefile.targets

