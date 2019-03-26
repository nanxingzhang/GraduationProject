################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./src/ADC12_INIT.obj" \
"./src/ADS1118.obj" \
"./src/DAC8571.obj" \
"./src/DS18B20.obj" \
"./src/KEY_SIG.obj" \
"./src/LCD12864.obj" \
"./src/LCD1602.obj" \
"./src/Lcd12864spi.obj" \
"./src/TA0_PWM.obj" \
"./src/TA1_PWM1.obj" \
"./src/TA2_PWM.obj" \
"./src/TB0_PWM2.obj" \
"./src/TIMER_INIT.obj" \
"./src/UCS_INIT.obj" \
"../lnk_msp430f5529.cmd" \
$(GEN_CMDS__FLAG) \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include src/subdir_vars.mk
-include subdir_rules.mk
-include src/subdir_rules.mk
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
testproject5529.out \

EXE_OUTPUTS__QUOTED += \
"testproject5529.out" \

BIN_OUTPUTS += \
testproject5529.hex \

BIN_OUTPUTS__QUOTED += \
"testproject5529.hex" \


# All Target
all: testproject5529.out

# Tool invocations
testproject5529.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --advice:power="all" -g --define=__MSP430F5529__ --display_error_number --diag_warning=225 --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full -z -m"testproject5529.map" --stack_size=160 --heap_size=160 --cinit_hold_wdt=on -i"C:/ti/ccsv7/ccs_base/msp430/include" -i"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/lib" -i"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/include" -i"C:/ti/ccsv7/ccs_base/msp430/lib/5xx_6xx_FRxx" --reread_libs --warn_sections --diag_wrap=off --display_error_number --xml_link_info="testproject5529_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "testproject5529.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

testproject5529.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_16.9.6.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "testproject5529.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "src\ADC12_INIT.obj" "src\ADS1118.obj" "src\DAC8571.obj" "src\DS18B20.obj" "src\KEY_SIG.obj" "src\LCD12864.obj" "src\LCD1602.obj" "src\Lcd12864spi.obj" "src\TA0_PWM.obj" "src\TA1_PWM1.obj" "src\TA2_PWM.obj" "src\TB0_PWM2.obj" "src\TIMER_INIT.obj" "src\UCS_INIT.obj" 
	-$(RM) "main.d" "src\ADC12_INIT.d" "src\ADS1118.d" "src\DAC8571.d" "src\DS18B20.d" "src\KEY_SIG.d" "src\LCD12864.d" "src\LCD1602.d" "src\Lcd12864spi.d" "src\TA0_PWM.d" "src\TA1_PWM1.d" "src\TA2_PWM.d" "src\TB0_PWM2.d" "src\TIMER_INIT.d" "src\UCS_INIT.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

