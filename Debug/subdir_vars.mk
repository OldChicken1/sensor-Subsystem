################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../CC3220SF_LAUNCHXL_FREERTOS.cmd 

SYSCFG_SRCS += \
../common.syscfg 

C_SRCS += \
../client_cbs.c \
./syscfg/ti_drivers_net_wifi_config.c \
./syscfg/Board.c \
../debug.c \
../main_freertos.c \
../mqtt_client_app.c \
../mqtt_queue.c \
../network_if.c \
../pixy_main.c \
../pixy_queue.c \
../process_main.c \
../readFromQueueThread.c \
../sensors_queue.c \
../sensors_state.c \
../statisticsTask.c \
../timer_pixy.c \
../timer_pub.c \
../uart_term.c \
../ultraSonar_main.c 

GEN_FILES += \
./syscfg/ti_drivers_net_wifi_config.c \
./syscfg/Board.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./client_cbs.d \
./syscfg/ti_drivers_net_wifi_config.d \
./syscfg/Board.d \
./debug.d \
./main_freertos.d \
./mqtt_client_app.d \
./mqtt_queue.d \
./network_if.d \
./pixy_main.d \
./pixy_queue.d \
./process_main.d \
./readFromQueueThread.d \
./sensors_queue.d \
./sensors_state.d \
./statisticsTask.d \
./timer_pixy.d \
./timer_pub.d \
./uart_term.d \
./ultraSonar_main.d 

OBJS += \
./client_cbs.obj \
./syscfg/ti_drivers_net_wifi_config.obj \
./syscfg/Board.obj \
./debug.obj \
./main_freertos.obj \
./mqtt_client_app.obj \
./mqtt_queue.obj \
./network_if.obj \
./pixy_main.obj \
./pixy_queue.obj \
./process_main.obj \
./readFromQueueThread.obj \
./sensors_queue.obj \
./sensors_state.obj \
./statisticsTask.obj \
./timer_pixy.obj \
./timer_pub.obj \
./uart_term.obj \
./ultraSonar_main.obj 

GEN_MISC_FILES += \
./syscfg/Board.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"client_cbs.obj" \
"syscfg\ti_drivers_net_wifi_config.obj" \
"syscfg\Board.obj" \
"debug.obj" \
"main_freertos.obj" \
"mqtt_client_app.obj" \
"mqtt_queue.obj" \
"network_if.obj" \
"pixy_main.obj" \
"pixy_queue.obj" \
"process_main.obj" \
"readFromQueueThread.obj" \
"sensors_queue.obj" \
"sensors_state.obj" \
"statisticsTask.obj" \
"timer_pixy.obj" \
"timer_pub.obj" \
"uart_term.obj" \
"ultraSonar_main.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\Board.h" 

C_DEPS__QUOTED += \
"client_cbs.d" \
"syscfg\ti_drivers_net_wifi_config.d" \
"syscfg\Board.d" \
"debug.d" \
"main_freertos.d" \
"mqtt_client_app.d" \
"mqtt_queue.d" \
"network_if.d" \
"pixy_main.d" \
"pixy_queue.d" \
"process_main.d" \
"readFromQueueThread.d" \
"sensors_queue.d" \
"sensors_state.d" \
"statisticsTask.d" \
"timer_pixy.d" \
"timer_pub.d" \
"uart_term.d" \
"ultraSonar_main.d" 

GEN_FILES__QUOTED += \
"syscfg\ti_drivers_net_wifi_config.c" \
"syscfg\Board.c" 

C_SRCS__QUOTED += \
"../client_cbs.c" \
"./syscfg/ti_drivers_net_wifi_config.c" \
"./syscfg/Board.c" \
"../debug.c" \
"../main_freertos.c" \
"../mqtt_client_app.c" \
"../mqtt_queue.c" \
"../network_if.c" \
"../pixy_main.c" \
"../pixy_queue.c" \
"../process_main.c" \
"../readFromQueueThread.c" \
"../sensors_queue.c" \
"../sensors_state.c" \
"../statisticsTask.c" \
"../timer_pixy.c" \
"../timer_pub.c" \
"../uart_term.c" \
"../ultraSonar_main.c" 

SYSCFG_SRCS__QUOTED += \
"../common.syscfg" 


