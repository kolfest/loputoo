################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
MCU/ADC.obj: ../MCU/ADC.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Config" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/LNK" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/LOGIC" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/MCU" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --diag_wrap=off --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="MCU/ADC.d" --obj_directory="MCU" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MCU/clock.obj: ../MCU/clock.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Config" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/LNK" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/LOGIC" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/MCU" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --diag_wrap=off --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="MCU/clock.d" --obj_directory="MCU" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MCU/misc.obj: ../MCU/misc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Config" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/LNK" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/LOGIC" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/MCU" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --diag_wrap=off --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="MCU/misc.d" --obj_directory="MCU" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MCU/timer.obj: ../MCU/timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Config" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/LNK" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/LOGIC" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/MCU" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --diag_wrap=off --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="MCU/timer.d" --obj_directory="MCU" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MCU/wdt.obj: ../MCU/wdt.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Config" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/LNK" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/LOGIC" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/MCU" --include_path="C:/Users/Karl/workspace_v6_2/LILLEPOTT/HW" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --diag_wrap=off --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="MCU/wdt.d" --obj_directory="MCU" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


