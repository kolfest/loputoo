################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main_lnk.obj: ../main_lnk.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/bin/cl430" -vmsp --use_hw_mpy=none --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/Karl/workspace_v6_2/AJU/LNK/Drivers" --include_path="C:/Users/Karl/workspace_v6_2/AJU/LNK" --include_path="C:/Users/Karl/workspace_v6_2/AJU/LNK/LNK" --include_path="C:/Users/Karl/workspace_v6_2/AJU/LNK/Drivers/Communication" --include_path="C:/Users/Karl/workspace_v6_2/AJU/LNK/Config" --include_path="C:/ti/ccsv6/tools/compiler/msp430_15.12.3.LTS/include" --advice:power=all -g --define=__MSP430G2553__ --diag_warning=225 --diag_wrap=off --display_error_number --printf_support=minimal --preproc_with_compile --preproc_dependency="main_lnk.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


